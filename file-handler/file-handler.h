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