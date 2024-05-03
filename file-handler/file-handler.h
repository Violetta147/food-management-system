#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../structs/dish.h"
#include "../structs/order.h"
#include "../constant.h"

#define BASE_DATA_PATH "data/"

void writeMenu(const char* fileName, Menu menu)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, fileName);
 
    FILE* menuP = fopen(filePath, "w");
    if (menuP == NULL) 
    {
        printf("Unable to open file.\n");
        return;
    }
    for(int i = 0; i < menu.total; i++)
    {
        fprintf(menuP, "%d || %s || %f\n", menu.dishes[i].PIN, menu.dishes[i].name, menu.dishes[i].price);
    }

    fclose(menuP);
}

Menu readMenu(const char* fileName)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, fileName);

    FILE* menuP = fopen(filePath, "r");
    if (menuP == NULL) {
        printf("Unable to read file.");
        exit(-1);
    } 

    Menu menu;
    menu.total = 0;

    while(true) {
        int result = fscanf(menuP, "%d || %s || %f\n", &menu.dishes[menu.total].PIN, menu.dishes[menu.total].name, &menu.dishes[menu.total].price);
        if (result != 3) break;
        ++menu.total;
    }

    return menu;
}
// co orders globally 
// co countOrders dem so orders in array of orders 
// co order items total
void writeOrder(const char* fileName, Order order, float *sum, float *sale, float *total)
{
    char filePath[MAX_PATH_LENGTH];
    strcpy(filePath, BASE_DATA_PATH);
    strcat(filePath, fileName);

    FILE* orderP = fopen(filePath, "w");
    if (orderP == NULL) 
    {
        printf("Unable to open file.\n");
        return;
    }
    int temp = countOrders();
    // write order includes order number, dishes PIN,
    // quantity, name, price, total price after discount, 
    //total price before discount, discount, and status
    for(int i = 0; i < order.total; i++)
    {
        fprintf(orderP, "Order number: %d\n", temp);
        fprintf(orderP, "Dishes PIN: %d\n", order.items[i].dish.PIN);
        fprintf(orderP, "Quantity: %d\n", order.items[i].quantity);
        fprintf(orderP, "Name: %s\n", order.items[i].dish.name);
        fprintf(orderP, "Price: %.0f\n", order.items[i].dish.price);
        fprintf(orderP, "Total price after discount: %.0f\n", *total);
        fprintf(orderP, "Total price before discount: %.0f\n", *sum);
        fprintf(orderP, "Discount: %.0f\n", *sale);
        fprintf(orderP, "Status: %s\n", *order.status);
    }
    fclose(orderP);
}