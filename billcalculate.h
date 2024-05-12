#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "structs/order.h"
#include "constant.h"
#include "menufunction.h"

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
        *sale = *sum * 25 / 100;      // 25% discount
        *total = floor(*sum - *sale); // thanh tien = tong tien - khuyen mai
    }
    // generate order ID(doesn't need because created in makeOrder) and date here
    char *date = (char *)malloc(11 * sizeof(char));
    if (date == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(date, createDate());
    // assign date to order
    strcpy(order->date, date);
    int orderFilesTotal = 0;
    char listOrderFiles[MAX][MAX];
    // get all the order files headerName sorted by date and the number of orders
    getListOrders(listOrderFiles, &orderFilesTotal);
    if (orderFilesTotal != 0)
    {
        Order TempOrders[100];
        int totalOrders = 0;
        // for loop to read each file, each file includes "orders"
        for (int i = 0; i < orderFilesTotal; i++)
        {
            int numOrder = countOrders(listOrderFiles[i]);
            char filePath[MAX_PATH_LENGTH];
            strcpy(filePath, BASE_DATA_PATH);
            strcat(filePath, INVOICES_PATH);
            strcat(filePath, listOrderFiles[i]);
            printf("Reading file %s\n", filePath);
            FILE *orderP = fopen(filePath, "r");
            if (orderP == NULL)
            {
                printf("Unable to read file\n.");
                exit(-1);
            }
            for (int j = 0; j < numOrder; j++)
            {   

                TempOrders[j + totalOrders] = readOrder(orderP);
            }
            fclose(orderP);
            totalOrders += numOrder;
        }
        for(int i = totalOrders; i < 100; i++)
        {
            TempOrders[i].orderID = 0;
        }
    do // loop until order ID is unique
    {
        createOrderID(order);
    }while(isRepeatOrderID(TempOrders, order->orderID) == true || isValidOrderID(order->orderID) == false);
    }
    else
    {
        createOrderID(order);
    }

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
            printf("\nBan da thanh toan don hang ma so %d\n", order->orderID);
            strcpy(order->status, ORDER_PAID);
            // how to assign order ID to order
            writeOrder(createInvoiceFilePath(date), order, true);
            strcat(date, ".txt");
            createOrderIndex(date);
            printf("Cam on quy khach da su dung dich vu cua chung toi.\n");
            printf("^_^\n");
            break;
        }
        else
        {
            printf("Don hang cua quy khach da duoc luu lai.\n");
            strcpy(order->status, ORDER_PROCESSING);
            writeOrder(createInvoiceFilePath(date), order, true);
            strcat(date, ".txt");
            createOrderIndex(date);
            break;
        }
    }

    free(date);
    // printf("adavas");
    // free(order); // potentially memory leak
    // printf("xx"); //it prevents the first isLoop
    // free(sum);
    // free(sale);
    // free(total);
}

// Function to print unpaid bills and ask user to pay
bool UnpaidBill()
{   
    int i;
    int j;
    char *tmpDate = (char *)malloc(11 * sizeof(char));
    if (tmpDate == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(tmpDate, createDate());
    strcat(tmpDate, ".txt");
    int orderFilesTotal = 0;
    char listOrderFiles[MAX][MAX];
    int numOrder = 0;
    int OrderIndex = 0;
    float OweNeedToPay[100]; //tam thoi de 100, sau nay se thay doi
    int flag = 0;
    getListOrders(listOrderFiles, &orderFilesTotal);
    for(OrderIndex = 0; OrderIndex < orderFilesTotal; OrderIndex++)
    {
        if(strcmp(listOrderFiles[OrderIndex],tmpDate) == 0)
        {   
            flag = 1;
            break;
        }
    }
    if(flag == 0)
    {
        printf("Khong ton tai ngay %.*s.\n", strlen(tmpDate)-4, tmpDate);
        return false;
    }
    Order TempOrders[100];
    int totalOrders = 0;
        numOrder = countOrders(listOrderFiles[OrderIndex]);
        char filePath[MAX_PATH_LENGTH];
        strcpy(filePath, BASE_DATA_PATH);
        strcat(filePath, INVOICES_PATH);
        strcat(filePath, listOrderFiles[OrderIndex]);
        printf("Reading file %s\n", filePath);
        FILE *orderP = fopen(filePath, "r");
        if (orderP == NULL)
        {
            printf("Unable to read file\n.");
            exit(-1);
        }
        for (int j = 0; j < numOrder; j++)
        {
            TempOrders[j + totalOrders] = readOrder(orderP);
        }
        fclose(orderP);
        totalOrders += numOrder; //de nhu v cung dc
        int length_to_keep = strlen(tmpDate) - 4;
        tmpDate[length_to_keep] = '\0';
        int isExistUnpaidOrder = 0; //chi can at least 1 order chua thanh toan
        for(i = 0; i < totalOrders; i++)
        {
            if(strcmp(TempOrders[i].status, ORDER_PROCESSING) == 0)
            {
                isExistUnpaidOrder = 1;
            }
        }
        if(isExistUnpaidOrder == 0)
        {
            printf("Khong co don hang nao chua thanh toan trong ngay %s.\n", tmpDate);
            return false;
        }
            printf("Danh sach don hang chua thanh toan trong ngay %s: \n", tmpDate);
            printf("%17s %17s %17s %17s %17s\n", "Ma so", "Mon an", "Don gia", "So luong", "Thanh tien");
    //access one order
    for (i = 0; i < totalOrders; i++)
    {
        if (strcasecmp(TempOrders[i].status, ORDER_PROCESSING) == 0)
        {
            printf("__________________________________________________________________________________________  \n");
            printf("\nMa hoa don: %03d\n", TempOrders[i].orderID);
            //access one order's items
            for (j = 0; j < TempOrders[i].total; j++)
            {
                printf("%17d %17s %17.0f %17d %17.0f\n",
                       TempOrders[i].items[j].dish.PIN,
                       TempOrders[i].items[j].dish.name,
                       TempOrders[i].items[j].dish.price,
                       TempOrders[i].items[j].quantity,
                       TempOrders[i].items[j].dish.price * TempOrders[i].items[j].quantity);
                OweNeedToPay[i] += TempOrders[i].items[j].dish.price * TempOrders[i].items[j].quantity;
            }
                printf("\033[0;33m");
                printf("%51s%38.0f\n", "Tong:", OweNeedToPay[i]);
                if(OweNeedToPay[i] >= SALE)
                {
                    printf("%57s%32.0f\n", "Khuyen mai:", OweNeedToPay[i] * 25 / 100);
                    printf("%57s%32.0f\n", "Thanh tien:", OweNeedToPay[i] - OweNeedToPay[i] * 25 / 100);
                }
                else
                printf("%57s%32.0f\n", "Thanh tien:", OweNeedToPay[i]);
                printf("\033[m");
        }
    }
    while (true)
    {
        if (ynQuestion("Ban co muon thanh toan don hang nao khong?"))
        {
            printf("Vui long nhap ma hoa don can thanh toan: ");
            int orderIndex;
            while (scanf("%d", &orderIndex) != 1 || isNotExistOrderID(TempOrders, orderIndex))
            {
                clstd();
                printf("\nVui long nhap dung ma hoa don: ");
            }
            if (orderIndex <= 0) // i made changes here to numOrder -> countOrder
            {
                printf("Khong tim thay don hang.\n");
            }
            else
            {   
                for(i = 0; i < totalOrders; i++)
                {
                    if(TempOrders[i].orderID == orderIndex)
                    {
                        break;
                    }
                }
                if(OweNeedToPay[i] >= SALE)
                {
                    payment(OweNeedToPay[i] - OweNeedToPay[i] * 25 / 100);
                }
                else
                {
                    payment(OweNeedToPay[i]);
                }
                printf("\nBan da thanh toan don hang ma so %d\n", orderIndex);
                // update status
                for (i = 0; i < totalOrders; i++)
                {
                    if (TempOrders[i].orderID == orderIndex)
                    {
                        strcpy(TempOrders[i].status, ORDER_PAID);
                        break;
                    }
                }
                // reset file to empty
                resetOrders(createInvoiceFilePath(tmpDate));
                for (i = 0; i < totalOrders; i++)
                {
                    writeOrder(createInvoiceFilePath(tmpDate), &TempOrders[i], IS_TIME_TO_WRITE_BACK);
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