#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../structs/dish.h"
#include "../structs/order.h"
#include "../constant.h"
#include "../error-handler/error-handler.h"

#define BASE_DATA_PATH "data/"

void writeMenu(const char* fileName, Menu menu)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, fileName);
 
    FILE* menuP = fopen(filePath, "a");
    if (menuP == NULL) 
    {
        printf("Unable to open file.\n");
        return;
    }
    for(int i = 0; i < menu.total; i++)
    {
        fprintf(menuP, "%d || %s || %.0f\n",
                 menu.dishes[i].PIN,
                 menu.dishes[i].name,
                 menu.dishes[i].price);
    }

    fclose(menuP);
}
Menu readMenu(const char* fileName)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, fileName);
    printf("%s\n", filePath);
    FILE* menuP = fopen(filePath, "r");
    if (menuP == NULL) {
        printf("Unable to read file.");
        exit(-1);
    } 

    Menu menu;
    menu.total = 0;
    while(true) {
        int check = fscanf(menuP, "%d || %s || %f\n", 
                            &menu.dishes[menu.total].PIN,
                             menu.dishes[menu.total].name,
                              &menu.dishes[menu.total].price);
        if(check != 3)
        {   
            break; 
        }
        ++menu.total; 
    }
    fclose(menuP);
    return menu;
}

void writeOrder(const char* fileName, Order *order, bool isNotAppend)
{
    if(isNotAppend == true)
    {   
        FILE* orderP = fopen(fileName, "w");
        if (orderP == NULL) 
        {   
            printf("Unable to open file %s.\n", fileName);
            return;
        }
        fprintf(orderP, "%s,%d", order->date, order->orderID);
        for(int i = 0; i < order->total; i++)
        {   
            //serialize
            fprintf(orderP, ",%d,%s,%d,%.0f",
                    order->items[i].dish.PIN,
                    order->items[i].dish.name,
                    order->items[i].quantity,
                    order->items[i].dish.price);
        }
        fprintf(orderP, "\n");
        fclose(orderP);
        return;
    }
    else if(isNotAppend == false)
    {  
    FILE* orderP = fopen(fileName, "a");
    if (orderP == NULL) 
    {   
        printf("Unable to open file %s.\n", fileName);
        return;
    }
    fprintf(orderP, "%s,%d", order->date, order->orderID);
    for(int i = 0; i < order->total; i++)
    {   
        //serialize
        fprintf(orderP, ",%d,%s,%d,%.0f",
                order->items[i].dish.PIN,
                order->items[i].dish.name,
                order->items[i].quantity,
                order->items[i].dish.price);
    }
    fprintf(orderP, "\n");
    fclose(orderP);
    return;
    }
}
//bool function to signify if this is the moment 
//to write all orders back to file
bool isTimeToWriteBack()
{
    return true;
}

Order readOrder(const char* fileName)
{

    FILE* orderP = fopen(fileName, "r");
    if (orderP == NULL) {
        printf("Unable to read file.");
        exit(-1);
    } 

    Order order;
    order.total = 0;
    int check = fscanf(orderP, "%[^,],%d", order.date, &order.orderID);
    if(check != 2)
    {
        printf("Unable to read file.");
        exit(-1);
    }
    while(true) {
        check = fscanf(orderP, ",%d,%[^,],%d,%f", 
                        &order.items[order.total].dish.PIN,
                         order.items[order.total].dish.name,
                          &order.items[order.total].quantity,
                           &order.items[order.total].dish.price);
        if(check != 4)
        {   
            break; 
        }
        ++order.total; 
    }
    //check eof
    return order;
    fclose(orderP);
}
//function to scan all orders from file
//to find unpaid bill with a specific orderID


//function to create string of file path for invoices sorted by date
char* createInvoiceFilePath(char* date)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, "invoices/");
    strcat(filePath, date);
    strcat(filePath, ".txt");
    return filePath;
}
//function to create date string for invoice file name
//without using time.h
char* createDate()
{
    //date will be in format dd-mm-yyyy
    //date will be scanf from user
    char* date = (char*)malloc(12);
    printf("Nhap ngay thang nam (dd-mm-yyyy): ");
    scanf("%s", date);
    clstd();
    return date;
}

//continue read orders from file 
//to count number of orders
int countOrders(const char* fileName)
{   
    int orderCount = 0;
    char buffer[1000];
    FILE* orderP = fopen(fileName, "r");
    if (orderP == NULL) {
        printf("Unable to read file.");
        return -1;
    } 
    while(fgets(buffer, sizeof(buffer), orderP))
    {
        orderCount++;
    }
    fclose(orderP);
    return orderCount;
}

//update an order at a specific orderID by rewrite all orders to file 
//using writeOrder function

