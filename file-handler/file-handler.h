#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../structs/dish.h"
#include "../structs/order.h"
#include "../constant.h"
#include "../error-handler/error-handler.h"

#define BASE_DATA_PATH "./data/"
#define INVOICES_PATH "invoices/"
#define IS_TIME_TO_WRITE_BACK 1
#define FORMATTED_READ_FIELDS "%5d\t%[^\t]\t%10d\t%7d\t%11s\n"

// function prototypes
void writeMenu(const char *fileName);
void readMenu(const char *fileName);
void writeOrder(const char *filePath, Order *order, bool isAppend);
void resetOrders(const char *filePath);
int getListOrders(char listFiles[MAX][MAX], int *total);
void createOrderIndex(const char *fileName);
Order readOrder(FILE *orderP);
char *createInvoiceFilePath(char *date);
char *createDate();
int countOrders(const char *fileName);
void sortDateIndex();

void writeMenu(const char *fileName)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, fileName);
    FILE *menuP = fopen(filePath, "w");
    if (menuP == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }
    // Calculate longest lengths
    int longestPriceDigits = 0, longestName = 0, longestUnit = 0;
    for (int i = 0; i < menu.total; i++)
    {
        int priceDigits = log10(menu.dishes[i].Price) + 1;
        if (priceDigits > longestPriceDigits)
            longestPriceDigits = priceDigits;

        int nameLength = strlen(menu.dishes[i].name);
        if (nameLength > longestName)
            longestName = nameLength;

        int unitLength = strlen(menu.dishes[i].Unit);
        if (unitLength > longestUnit)
            longestUnit = unitLength;
    }

    // Determine number of tabs for each field
    int nameTabs = (longestName >= 4) ? 1 : 2;
    int priceTabs = (longestPriceDigits >= 4) ? 1 : 2;

    // Header
    fprintf(menuP, "%5s", "PIN");
    fprintf(menuP, "\t%-*s", longestName + (nameTabs - 1) * 4, "Name");
    fprintf(menuP, "\t%-*s", longestPriceDigits + (priceTabs - 1) * 4, "Price");
    fprintf(menuP, "\t%-*s", longestPriceDigits + (priceTabs - 1) * 4, "Status");
    fprintf(menuP, "\t%s\n", "Unit");

    // Data
    for (int i = 0; i < menu.total; i++)
    {
        fprintf(menuP, "%5d", menu.dishes[i].PIN);
        fprintf(menuP, "\t%-*s", longestName + (nameTabs - 1) * 4, menu.dishes[i].name);
        fprintf(menuP, "\t%-*d", longestPriceDigits + (priceTabs - 1) * 4, menu.dishes[i].Price);
        fprintf(menuP, "\t%-*d", longestPriceDigits + (priceTabs - 1) * 4, menu.dishes[i].Status);
        fprintf(menuP, "\t%s\n", menu.dishes[i].Unit);
    }

    fclose(menuP);
    return;
}
void readMenu(const char *fileName)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, fileName);
    FILE *menuP = fopen(filePath, "r");
    if (menuP == NULL)
    {
        printf("Unable to read file.");
        exit(-1);
    }
    char hole[256];
    fscanf(menuP, "%[^\n]\n", hole);
    menu.total = 0;
    while(true)
    {
        int check = fscanf(menuP, FORMATTED_READ_FIELDS,
                           &menu.dishes[menu.total].PIN,
                           menu.dishes[menu.total].name,
                           &menu.dishes[menu.total].Price,
                           &menu.dishes[menu.total].Status,
                           menu.dishes[menu.total].Unit);
        if (check != 5)
        {
            break;
        }
        ++menu.total;
    }
    for(int i = 0; i < menu.total; i++)
    {   
        for(int j = strlen(menu.dishes[i].name) - 1; j >= 0; j--)
        {
          if(myIsAlpha(menu.dishes[i].name[j]) == false && myIsAlpha(menu.dishes[i].name[j]) == false)
          {
            continue;
          }
          else
          {
            menu.dishes[i].name[j+1] = '\0';
            break; 
          }
          
        }
    }
    fclose(menuP);
}

void writeOrder(const char *filePath, Order *order, bool isAppend)
{
    // neu isNotAppend == true thi ghi de len file
    if (isAppend == false)
    {
        FILE *orderP = fopen(filePath, "w");
        if (orderP == NULL)
        {
            printf("Unable to open file %s.\n", filePath);
            return;
        }
        fprintf(orderP, "%s,%d,%s", order->date, order->orderID, order->status);
        for (int i = 0; i < order->total; i++)
        {
            // serialize
            fprintf(orderP, ",%d,%s,%d,%d",
                    order->items[i].dish.PIN,
                    order->items[i].dish.name,
                    order->items[i].quantity,
                    order->items[i].dish.Price);
        }
        fprintf(orderP, "\n");
        fclose(orderP);
        return;
    }
    // neu isNotAppend == false thi ghi tiep vao file
    else if (isAppend == true)
    {
        FILE *orderP = fopen(filePath, "a");
        if (orderP == NULL)
        {
            printf("Unable to open file %s.\n", filePath);
            return;
        }
        fprintf(orderP, "%s,%d,%s", order->date, order->orderID, order->status);
        for (int i = 0; i < order->total; i++)
        {
            // serialize
            fprintf(orderP, ",%d,%s,%d,%d",
                    order->items[i].dish.PIN,
                    order->items[i].dish.name,
                    order->items[i].quantity,
                    order->items[i].dish.Price);
        }
        fprintf(orderP, "\n");
        fclose(orderP);
        return;
    }
}
// function to reset all orders in file to empty
void resetOrders(const char *filePath)
{
    FILE *orderP = fopen(filePath, "w");
    if (orderP == NULL)
    {
        printf("Unable to open file.");
        exit(-1);
    }
    fclose(orderP);
}

int getListOrders(char listFiles[MAX][MAX], int *total)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, INVOICES_PATH);
    strcat(filePath, "index.txt");
    printf("File path: %s\n", filePath);
    FILE *indexFile = fopen(filePath, "r");
    if (indexFile == NULL)
    {
        printf("Unable to read file.\n");
        exit(-1);
    }

    *total = 0;
    while (true)
    {
        char invoiceFileName[MAX];
        int check = fscanf(indexFile, "%s\n", invoiceFileName);
        if (check != 1)
        {
            fscanf(indexFile, "\n");
            break;
        }

        strcpy(listFiles[*total], invoiceFileName);
        ++*total;
    }
    fclose(indexFile);
    return 0;
}
// function to create one order index file each time to store order file name
void createOrderIndex(const char *fileName)
{
    printf("Creating order index file...\n");
    printf("File name: %s\n", fileName);
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, INVOICES_PATH);
    strcat(filePath, "index.txt");
    FILE *indexFile = fopen(filePath, "r");
    if (indexFile == NULL)
    {
        printf("Unable to open file.");
        exit(-1);
    }
    // what if index already exists?
    char fileNameWithNewLine[MAX_PATH_LENGTH];
    strcpy(fileNameWithNewLine, fileName);
    strcat(fileNameWithNewLine, "\n");
    char line[MAX_PATH_LENGTH];
    while (fgets(line, sizeof(line), indexFile))
    {
        if (strcmp(line, fileNameWithNewLine) == 0)
        {
            // the content already exists, no need to write
            printf("Index already exists.\n");
            fclose(indexFile);
            return;
        }
    }
    // the content doesn't exist, close and reopen the file in "a"
    fclose(indexFile);
    indexFile = fopen(filePath, "a");
    if (indexFile == NULL)
    {
        printf("Unable to open file.");
        exit(-1);
    }
    fprintf(indexFile, "%s\n", fileName);
    fclose(indexFile);
}

Order readOrder(FILE *orderP)
{
    Order order;
    order.total = 0;
    int check = fscanf(orderP, "%[^,],%d,%[^,]", order.date, &order.orderID, order.status);
    if (check != 3)
    {
        printf("Unable to read file.\n");
        exit(-1);
    }
    while (true)
    {
        check = fscanf(orderP, ",%d,%[^,],%d,%d",
                       &order.items[order.total].dish.PIN,
                       order.items[order.total].dish.name,
                       &order.items[order.total].quantity,
                       &order.items[order.total].dish.Price);
        if (check != 4 || order.total == 4)
        {
            break;
        }
        ++order.total;
    }
    fscanf(orderP, "\n");
    return order;
}

// function to create string of file path for invoices sorted by date
char *createInvoiceFilePath(char date[])
{
    char *filePath = (char *)malloc(MAX_PATH_LENGTH);
    if (filePath == NULL)
    {
        printf("Unable to allocate memory.");
        exit(-1);
    }
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, INVOICES_PATH);
    strcat(filePath, date);
    strcat(filePath, ".txt");
    printf("\n");
    printf("File path: %s\n", filePath);
    return filePath;
}
// function to create date string for invoice file name
// without using time.h
char *createDate()
{
    // date will be in format dd-mm-yyyy
    // date will be scanf from user
    char *date = (char *)malloc(10); // i made change here
    if (date == NULL)
    {
        printf("Unable to allocate memory.");
        exit(-1);
    }
    printf("Nhap ngay thang nam (dd-mm-yyyy): ");
    scanf("%s", date);
    while (strlen(date) != 10 || date[2] != '-' || date[5] != '-' || date[10] != '\0' || !isValidDate(dateToInt(date)))
    {
        printf("Nhap lai ngay thang nam (dd-mm-yyyy): ");
        scanf("%s", date);
    }
    clstd();
    return date;
}
// function to sort date index then write back into the index.txt file (hasn't analyzed yet)
void sortDateIndex()
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, INVOICES_PATH);
    strcat(filePath, "index.txt");
    FILE *indexFile = fopen(filePath, "r");
    if (indexFile == NULL)
    {
        printf("Unable to read file.");
        exit(-1);
    }
    char listFiles[MAX][MAX];
    int totalFileIndex = 0;
    getListOrders(listFiles, &totalFileIndex);
    // calculate the timestamp value of each date
    int dateInts[MAX];
    for (int i = 0; i < totalFileIndex; i++)
    {
        dateInts[i] = dateToInt(listFiles[i]);
    }
    // sort the list of file names
    for (int i = 0; i < totalFileIndex; i++)
    {
        for (int j = i + 1; j < totalFileIndex; j++)
        {
            if (dateInts[i] > dateInts[j])
            {
                int tempInt = dateInts[i];
                dateInts[i] = dateInts[j];
                dateInts[j] = tempInt;
                char tempStr[MAX];
                strcpy(tempStr, listFiles[i]);
                strcpy(listFiles[i], listFiles[j]);
                strcpy(listFiles[j], tempStr);
            }
        }
    }
    // write back to the index.txt file
    fclose(indexFile);
    indexFile = fopen(filePath, "w");
    if (indexFile == NULL)
    {
        printf("Unable to open file.");
        exit(-1);
    }
    for (int i = 0; i < totalFileIndex; i++)
    {
        fprintf(indexFile, "%s\n", listFiles[i]);
    }
    fclose(indexFile);
}

// continue read orders from file
// to count number of orders
int countOrders(const char *fileName)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, INVOICES_PATH);
    strcat(filePath, fileName);
    int orderCount = 0;
    char buffer[1000];
    FILE *orderP = fopen(filePath, "r");
    if (orderP == NULL)
    {
        printf("Unable to read file.");
        return -1;
    }
    while (fgets(buffer, sizeof(buffer), orderP))
    {
        orderCount++;
    }
    fclose(orderP);
    return orderCount;
}

//function to write log of data of deleted dishes as csv file into file-handler deleted by Delete function in admin mode
void writeDeletedDishLog(Dish dish)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, "deleted.txt");
    FILE *logP = fopen(filePath, "a");
    if (logP == NULL)
    {
        printf("Unable to open file.");
        exit(-1);
    }
    fprintf(logP, "%d,%s,%d,%d,%s\n", dish.PIN, dish.name, dish.Price, dish.Status, dish.Unit);
    fclose(logP);
}
void readDeletedDishLog(Dish deletedDishes[MAX], int *total)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, "deleted.txt");
    FILE *logP = fopen(filePath, "r");
    if (logP == NULL)
    {
        printf("Unable to open file.");
        exit(-1);
    }
    *total = 0;
    while (true)
    {
        int check = fscanf(logP, "%d,%[^,],%d,%d,%s\n",
                           &deletedDishes[*total].PIN,
                           deletedDishes[*total].name,
                           &deletedDishes[*total].Price,
                           &deletedDishes[*total].Status,
                           deletedDishes[*total].Unit);
        if (check != 5)
        {
            break;
        }
        ++*total;
    }
    fclose(logP);
}