#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "structs/order.h"
#include "constant.h"
#include "menufunction.h"

int payment(int total)
{
    int change = 0;  // tien thua thoi lai
    int owe = total; // tien quy khach no, owe is temp
    int paid = 0;    // tien quy khach tra

    inputPositiveInt("PLEASE ENTER THE AMOUNT OF MONEY YOU NEED TO PAY IN VND", &paid);
    do
    {
        if (paid >= owe)
        {
            change = paid - owe;
            printf("YOUR CHANGE IS : %d VND\n", change);
            break;
        }
        else
        {
            owe -= paid;
            printf("YOU STILL OWE US %d VND: ", owe);
        }
    } while (owe > 0);

    return change;
}

void calculateBill(Order *order, int *sum, int *sale, int *total)
{
    *sum = 0;
    *sale = 0;
    *total = 0;

    for (int i = 0; i < order->total; i++)
    {
        if (order->items[i].dish.PIN == 0)
        {
            break;
        }
        *sum += order->items[i].dish.Price * order->items[i].quantity;
    }

    if (*sum >= SALE)
    {
        *sale = *sum * 25 / 100;      // 25% discount
        *total = floor(*sum - *sale); // thanh tien = tong tien - khuyen mai
    }
    else
    {
        *total = *sum;
    }
    // generate order ID(doesn't need because created in makeOrder) and date here
    char date[11];
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
        for (int i = totalOrders; i < 100; i++)
        {
            TempOrders[i].orderID = 0;
        }
        do // loop until order ID is unique
        {
            createOrderID(order);
        } while (isRepeatOrderID(TempOrders, order->orderID) == true || isValidOrderID(order->orderID) == false);
    }
    else
    {
        createOrderID(order);
    }

    printf("__________________________________________________________________________________________\n");
    printf("ORDER ID: %03d\n", order->orderID);
    printf("%18s %19s %18s %19s %15s\n", "PIN", "Name", "Quantity", "Price", "Total");
    printf("__________________________________________________________________________________________\n");

    for (int i = 0; i < order->total; i++)
    {
        if (order->items[i].dish.PIN == 0)
        {
            break;
        }
        //middle align the pin corresponding to "PIN" header and print only it
        

        printf("__________________________________________________________________________________________\n");
    }

    printf("\033[1;33m");
    printf("%94s%15d\n", "Total:", *sum);
    printf("%94s%15d\n", "Sale:", *sale);
    printf("%94s%15d\n", "Payment:", *total);
    printf("\033[m");
    while (true)
    {
        printf("\033[1;34m");
        printf("Do you want to pay instantly? [Y/N]:");
        printf("\033[m");
        char tmp[1000];
        scanf("%s", tmp);
        clstd();
        if (isYes(tmp))
        {
            payment(*total);
            printf("\nOrder ID %d paid.\n", order->orderID);
            strcpy(order->status, ORDER_PAID);
            // how to assign order ID to order
            writeOrder(createInvoiceFilePath(date), order, true);
            strcat(date, ".txt");
            createOrderIndex(date);
            printf("Thank you for using our service.\n");
            printf("^_^\n");
            break;
        }
        else
        {
            printf("Your order has been saved for later paying.\n");
            strcpy(order->status, ORDER_PROCESSING);
            writeOrder(createInvoiceFilePath(date), order, true);
            strcat(date, ".txt");
            createOrderIndex(date);
            break;
        }
    }
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
    int OweNeedToPay[100]; // tam thoi de 100, sau nay se thay doi
    int flag = 0;
    getListOrders(listOrderFiles, &orderFilesTotal);
    for (OrderIndex = 0; OrderIndex < orderFilesTotal; OrderIndex++)
    {
        if (strcmp(listOrderFiles[OrderIndex], tmpDate) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("Date %.*s doesn't exist.\n", strlen(tmpDate) - 4, tmpDate);
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
    totalOrders += numOrder; // de nhu v cung dc
    int length_to_keep = strlen(tmpDate) - 4;
    tmpDate[length_to_keep] = '\0';
    int isExistUnpaidOrder = 0; // chi can at least 1 order chua thanh toan
    for (i = 0; i < totalOrders; i++)
    {
        if (strcmp(TempOrders[i].status, ORDER_PROCESSING) == 0)
        {
            isExistUnpaidOrder = 1;
        }
    }
    if (isExistUnpaidOrder == 0)
    {
        printf("There is no unpaid order within the date %s.\n", tmpDate);
        return false;
    }
    // LIST OF UNPAID ORDERS
    /*---------------------------------------------------------------------------------------------------*/
    printf("List of unpaid orders within the date %s: \n", tmpDate);
    printf("%18s %19s %19s %18s %15s %15s\n", "PIN", "Name", "Price", "Quantity", "Unit", "Total");
    // access one order
    for (i = 0; i < totalOrders; i++)
    {
        if (strcasecmp(TempOrders[i].status, ORDER_PROCESSING) == 0)
        {
            printf("__________________________________________________________________________________________  \n");
            printf("\nORDER ID: %03d\n", TempOrders[i].orderID);
            // access one order's items
            for (j = 0; j < TempOrders[i].total; j++)
            {
                if (TempOrders[i].items[j].dish.PIN == 0)
                {
                    break;
                }
                printf("%18d %21s\n", TempOrders[i].items[j].dish.PIN, TempOrders[i].items[j].dish.name);
                printf("%19d %15d %18s %15d\n", TempOrders[i].items[j].dish.Price, TempOrders[i].items[j].quantity, TempOrders[i].items[j].dish.Unit, TempOrders[i].items[j].dish.Price * TempOrders[i].items[j].quantity);
                OweNeedToPay[i] += TempOrders[i].items[j].dish.Price * TempOrders[i].items[j].quantity;
            }
            printf("\033[0;33m");
            printf("%94s%15d\n", "Total:", OweNeedToPay[i]);
            if (OweNeedToPay[i] >= SALE)
            {
                printf("%94s%15d\n", "Sale", OweNeedToPay[i] * 25 / 100);
                printf("%94s%15d\n", "Payment:", OweNeedToPay[i] - OweNeedToPay[i] * 25 / 100);
            }
            else
                printf("%94s%15d\n", "Payment:", OweNeedToPay[i]);
            printf("\033[m");
        }
        printf("\n");
    }
    /*---------------------------------------------------------------------------------------------------*/
    while (true)
    {
        if (ynQuestion("Do you want to pay?"))
        {
            printf("Please enter ORDER ID you want to pay!\n");
            int orderIndex;
            inputPositiveInt("ORDER ID: ", &orderIndex);
            while (isNotExistOrderID(TempOrders, orderIndex))
            {
                clstd();
                inputPositiveInt("ORDER ID: ", &orderIndex);
            }
            // FIND 'ORDER' IN 'TEMPORDERS' MATCHES ORDER INDEX AND TAKE i VALUE TO PAY
            for (i = 0; i < totalOrders; i++)
            {
                if (TempOrders[i].orderID == orderIndex)
                {
                    break;
                }
            }
            if (OweNeedToPay[i] >= SALE)
            {
                payment(OweNeedToPay[i] - OweNeedToPay[i] * 25 / 100);
            }
            else
            {
                payment(OweNeedToPay[i]);
            }
            printf("\nYOU HAVE PAID ORDER WITH ID %d\n", orderIndex);
            // UPDATE STATUS
            for (i = 0; i < totalOrders; i++)
            {
                if (TempOrders[i].orderID == orderIndex)
                {
                    strcpy(TempOrders[i].status, ORDER_PAID);
                    break;
                }
            }
            // RESET FILE TO WRITE BACK
            resetOrders(createInvoiceFilePath(tmpDate));
            for (i = 0; i < totalOrders; i++)
            {
                writeOrder(createInvoiceFilePath(tmpDate), &TempOrders[i], IS_TIME_TO_WRITE_BACK);
            }
            printf("THANK YOU FOR USING OUR SERVICE.\n");
            return true;
        }
        else
        {
            printf("YOUR INVOICES HAVE BEEN SAVED FOR LATER PAYING.\n");
            return false;
        }
    }
    return false;
}