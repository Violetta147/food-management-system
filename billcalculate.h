#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "structs/order.h"
#include "constant.h"
#include "menufunction.h"


#define INVOICE_FILE_PATH "/data/invoices/"
#define MAX_LENGTH 256

float payment(float total)
{
    float change = 0;  // tien thua thoi lai
    float owe = total; // tien quy khach no, owe is temp
    float paid = 0;    // tien quy khach tra

    printf("Vui long nhap so tien quy khach can tra: ");

    do
    {
        scanf("%f", &paid);
        if (paid >= owe)
        {
            change = floor(paid - owe);
            printf("Tien thoi cua quy khach la: %.0f\n", change);
            break;
        }
        else
        {
            owe -= paid;
            printf("Quy khach tra tien con thieu, vui long tra them %.0f: ", owe);
        }
    } while (owe > 0);
 
    return change;
}

void calculateBill(Order *order, float *sum, float *sale, float *total)
{
    printf("Tinh tien hoa don: \n");
    *sum = 0;
    *sale = 0;
    *total = 0;

    for (int i = 0; i < order->total; i++)
    {
        *sum += order->items[i].dish.price * order->items[i].quantity;
    }

    if (*sum >= SALE)
    {
        *sale = *sum * 25 / 100;     // 25% discount
        *total = floor(*sum - *sale); // thanh tien = tong tien - khuyen mai
    }
    //generate order ID(doesn't need because created in makeOrder) and date here
    char date[11];
    strcpy(date,createDate());
    printf("__________________________________________________________________________________________  \n");
    printf("\nMa hoa don: %03d\n", order->orderID);
    printf("%17s %17s %17s %17s %17s\n", "Ma so", "Mon an", "Don gia", "So luong", "Thanh tien");

    for (int i = 0; i < order->total; i++)
    {
        printf("%17d %17s %17.0f %17d %17.0f\n",
                order->items[i].dish.PIN,
                order->items[i].dish.name,
                order->items[i].dish.price,
                order->items[i].quantity,
                order->items[i].dish.price * order->items[i].quantity);
    }

    printf("\033[0;33m");
    printf("%51s%38.0f\n", "Tong:", *sum);
    printf("%57s%32.0f\n", "Khuyen mai:", *sale);
    printf("%57s%32.0f\n", "Thanh tien:", *total);
    printf("\033[m");

    while (true)
    {
        printf("\033[1;34m");
        printf("Ban co muon thanh toan ngay khong? [Y/N]:");
        printf("\033[m"); 
        char tmp[1000];
        scanf("%s", tmp);
        clstd();
        if (isYes(tmp))
        {
            payment(*total);
            printf("__________________________________");
            printf("\nBan da thanh toan don hang ma so %d\n", order->orderID);
            order->status = ORDER_PAID;
            //how to assign order ID to order
            writeOrder(createInvoiceFilePath(date), order, false);
            printf("Cam on quy khach da su dung dich vu cua chung toi.\n");
            break;
        }
        else
        {
            printf("Don hang cua quy khach da duoc luu lai.\n");
            order->status = ORDER_PROCESSING;
            writeOrder(createInvoiceFilePath(date), order, false);
            break;
        }
    }
}
// Function to print unpaid bills and ask user to pay
bool UnpaidBill()
{
    int i;
    int j;
    char tmpDate[12];
    int numOrder = 0;
    float OweNeedToPay = 0;

    //input date to search for unpaid bills in a specific date
    strcpy(tmpDate,createDate());
    createInvoiceFilePath(tmpDate);
    //scan through the file to know how many orders are there 
    numOrder = countOrders(tmpDate);
    int counterOrder = 0;
    //to create an array of orders  
    Order TempOrders[1000]; 
    //read all orders from file to check for unpaid bills
    //tempOrders pointer acts as an array to store orders from readOrder function
    while(counterOrder < numOrder)
    {   
        //to prevent reading the last line twice (EOF is not detected by feof() until after the first read that encounters the EOF
        TempOrders[counterOrder] = readOrder(tmpDate);
        counterOrder++;
    }
    printf("Danh sach don hang chua thanh toan: \n");
    printf("%17s %17s %17s %17s %17s\n", "Ma so", "Mon an", "Don gia", "So luong", "Thanh tien");
    for (i = 1; i <= numOrder; i++)
    {
        if (strcasecmp(TempOrders[i].status, ORDER_PROCESSING) == 0)
        {
            printf("__________________________________________________________________________________________  \n");
            printf("\nMa hoa don: %03d\n", i);
            for (j = 0; j < TempOrders[i].total; j++)
            {
                printf("%17d %17s %17.0f %17d %17.0f\n",
                        TempOrders[i].items[j].dish.PIN,
                            TempOrders[i].items[j].dish.name,
                                TempOrders[i].items[j].dish.price,
                                    TempOrders[i].items[j].quantity,
                                        TempOrders[i].items[j].dish.price * TempOrders[i].items[j].quantity);
                OweNeedToPay += TempOrders[i].items[j].dish.price * TempOrders[i].items[j].quantity;
            }
        }
    }
    while (true)
    {
        
        if (ynQuestion("Ban co muon thanh toan don hang nao khong?"))
        {
            printf("Vui long nhap ma hoa don can thanh toan: ");
            int orderIndex;
            while (scanf("%d", &orderIndex) != 1)
            {
                while (getchar() != '\n')
                    ; // clear input buffer
                printf("\nVui long nhap dung ma hoa don: ");
            }
            if (orderIndex <= 0) //i made changes here to numOrder -> countOrder
            {
                printf("Khong tim thay don hang.\n");
            }
            else
            {
                
                printf("__________________________________");
                payment(OweNeedToPay);
                printf("\nBan da thanh toan don hang ma so %d\n", orderIndex);
                // update status
                for(i = 1; i <= numOrder; i++)
                {
                    if(TempOrders[i].orderID == orderIndex)
                    {
                        TempOrders[i].status = ORDER_PAID;
                        break;
                    }
                }
                //write all orders back to file
                //using writeOrder function to write all orders back to file
                for(i = 1; i <= numOrder; i++)
                {   
                    bool isNotAppend = isTimeToWriteBack();
                    writeOrder(tmpDate, &TempOrders[i], isNotAppend);
                }
                printf("Cam on quy khach da su dung dich vu cua chung toi.\n");
                return true;
            }
        }
        else
        {
            printf("Don hang cua quy khach da duoc luu lai.\n");
            return false;
        }
    }
    return false;
}