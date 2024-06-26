#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs/dish.h"
#include "error-handler/error-handler.h"
#include "file-handler/file-handler.h"
#include "constant.h"

// function prototypes
void enter();
void conf();
void Ans();
void calculate_popularity_revenue(int *revenue);

// prompt and validate the mode selection (A/C)
void enter()
{
    for (int k = 0; k < 5; k++)
    {
        printf("Enter (A/C) to get in admin or customer mode: ");
        scanf("%c", &mode); // no error checking
        clstd();
        if (myToUpper(mode) == 'A' || myToUpper(mode) == 'C')
        {
            break;
        }
        else
        {
            if (k == 4 || myToUpper(mode) == 'X')
            {
                printf("Exiting program due to unable to identify user's role....\n");
                yawm();
                exit(1);
            }
            else
            {
                printf("Invalid command.\n");
            }
        }
    }
}
// confirm password and validation for accessing admin mode
void conf()
{
    for (int i = 0; i < 5; i++)
    {
        char pass[MAX];
        printf("Password: ");
        scanf("%s", pass);
        clstd();
        if (strcmp(pass, PASS) == 0)
        {
            printf("\033[0;32m");
            printf("\n");
            for(int i = 0; i < 20; i++)
            {
                printf(" ");
            }
            printf("    #     #####  #####  #####  ##### #####      #####  #####     #     #    # ##### ##### ####\n");
            for(int i = 0; i < 20; i++)
            {
                printf(" ");
            }
            printf("   # #    #      #      #      #     #          #      #   #    # #    ##   #   #   #     #   #\n");
            for(int i = 0; i < 20; i++)
            {
                printf(" ");
            }
            printf("  #####   #      #      #####  ##### #####      #  ##  ####    #####   # #  #   #   ##### #    #\n");
            for(int i = 0; i < 20; i++)
            {
                printf(" ");
            }
            printf(" #     #  #      #      #          #     #      #   #  # #    #     #  #  # #   #   #     #   #\n");
            for(int i = 0; i < 20; i++)
            {
                printf(" ");
            }
            printf("#       # #####  #####  #####  ##### #####      #####  #  ## #       # #    #   #   ##### ####\n");
            printf("\n");
            printf("\n");
            yawm();
            // RESET COLOR TO NORMAL
            printf("\033[0m");
            break;
        }
        else
        {
            if (i == 4 || strcasecmp(pass, x) == 0)
            {
                system("color 04");
                printf("Failed loading program! Exiting...");
                yawm();
                exit(2);
            }
            printf("Password incorrect!! Please try again.\n");
        }
    }
}
// admin interface for choosing to "add","change","delete" dishes
void Ans()
{
    printf("Type X to exit.\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Enter A to add a dish.\n");
        printf("Enter C to change a dish.\n");
        printf("Enter D to delete a dish.\n");
        printf("Enter S to show statistics.\n");
        printf("Enter your choice: ");
        scanf("%c", &action);
        clstd();
        if (myToUpper(action) == 'A' || myToUpper(action) == 'C' || myToUpper(action) == 'D' || myToUpper(action) == 'S')
        {
            break;
        }
        else if (i == 4 || myToUpper(action) == 'X')
        {
            {
                // printf("No change have been done.\n");
                yawm();
                exit(4);
            }
        }
        else
            printf("Invalid Command.\n");
    }
}
// function to statistically calculate the popularity of dishes from date to date
void calculate_popularity_revenue(int *revenue)
{
    int flagTime = 0;
    char date1[MAX];
    char date2[MAX];
    do
    {
        flagTime = 0; // set flag to 0
        strcpy(date1, createDate());
        strcpy(date2, createDate());

        if (isDateExist(date1, date2) == false)
        {
            return;
        }
        if (dateToInt(date1) >= dateToInt(date2))
        {
            printf("Date1 has to be before Date2\n");
            flagTime = 1;
        }
    } while (flagTime == 1);

    int date1Int = dateToInt(date1);
    int date2Int = dateToInt(date2);
    Order TempOrder[100]; // 100 = number of orders in all files.
    int orderFilesTotal = 0;
    int totalOrders = 0;
    char listOrderFiles[MAX][MAX];
    char listOrderPath[MAX][MAX];
    getListOrders(listOrderFiles, &orderFilesTotal);
    int datetoInt[MAX];
    // make listorderfiles without .txt --> date
    for (int i = 0; i < orderFilesTotal; i++)
    {
        listOrderFiles[i][strlen(listOrderFiles[i]) - 4] = '\0';
    }
    // convert date to int
    for (int i = 0; i < orderFilesTotal; i++)
    {
        datetoInt[i] = dateToInt(listOrderFiles[i]);
    }
    // strcat listorderfiles with .txt
    for (int i = 0; i < orderFilesTotal; i++)
    {
        strcat(listOrderFiles[i], ".txt");
    }
    for (int i = 0; i < orderFilesTotal; i++)
    {
        if (datetoInt[i] >= date1Int && datetoInt[i] <= date2Int)
        {
            char filePath[MAX_PATH_LENGTH];
            strcpy(filePath, BASE_DATA_PATH);
            strcat(filePath, INVOICES_PATH);
            strcat(filePath, listOrderFiles[i]);
            FILE *orderP = fopen(filePath, "r");
            if (orderP == NULL)
            {
                printf("Error opening file %s\n", filePath);
                break; // because the file maybe empty
            }
            int orderCount = countOrders(listOrderFiles[i]);
            for (int j = 0; j < orderCount; j++)
            {
                TempOrder[j + totalOrders] = readOrder(orderP);
            }
            fclose(orderP);
            totalOrders += orderCount;
        }
    }
    //asign 0 to each order's field or ith dishes that exceed total because they don't have data

    Popularity pop[MAX];
    for (int i = 0; i < MAX; i++)
    {
        pop[i].Dish.PIN = 0;
        pop[i].count = 0;
        pop[i].Dish.Price = 0;
        pop[i].Dish.name[0] = '\0';
    }
    Dish deletedDishes[MAX];
    int deletedDishesCount = 0;
    for (int i = 0; i < MAX; i++)
    {
        deletedDishes[i].PIN = 0;
        deletedDishes[i].Price = 0;
        deletedDishes[i].name[0] = '\0';
    }
    readDeletedDishLog(deletedDishes, &deletedDishesCount);
    printf("%d\n", deletedDishesCount);
    for(int i = 0; i < deletedDishesCount; i++)
    {
        printf("%s\n", deletedDishes[i].name);
    }
    readMenu("menu.txt");
    int i;
    for(i = 0; i < menu.total; i++)
    {
        pop[i].Dish.PIN = menu.dishes[i].PIN;
    }
    for(int j = i; j < deletedDishesCount; j++)
    {
        if(pop[j].Dish.PIN == deletedDishes[j].PIN) 
            continue;
        else  
        {   
            if(deletedDishes[j].PIN == 0)
            {
                break;
            }
            pop[j].Dish.PIN = deletedDishes[j].PIN;
        }   
    }
    
    for(int k = 0; k < MAX; k++)
    {
        printf("%s\n", pop[k].Dish.name);
    }
    
    // generate tests to test if the popularity is correct

    // sort the popularity
    for (int i = 0; i < menu.total; i++)
    {
        for (int j = i + 1; j < menu.total; j++)
        {
            if (pop[i].count < pop[j].count)
            {
                Popularity temp = pop[i];
                pop[i] = pop[j];
                pop[j] = temp;
            }
        }
    }
    // calculate how many dishes in pop have count > 0
    int count = 0;
    for (int i = 0; i < menu.total; i++)
    {
        if (pop[i].count > 0)
        {
            count++;
        }
    }
    // print the header for ranking of dishes table
    printf("\nBANG XEP HANG MON AN BAN CHAY TU NGAY %s DEN %s\n", date1, date2);
    printf("No.  |  Name  |  Quantity\n");
    printf("----------------------------\n");
    // print the ranking of dishes
    for (int i = 0; i < count; i++)
    {
        // adjust the width of the table for each dish because each dish has different length of name
        // explain adjust width of table
        printf("%-4d | %-6s | %6d\n", i + 1, pop[i].Dish.name, pop[i].count);
    }
    // calculate the revenue , difference between revenue and total sales?
    *revenue = 0;
    int sum[MAX];
    for (int i = 0; i < MAX; i++)
    {
        sum[i] = 0;
    }
    for (int i = 0; i < totalOrders; i++)
    {
        if (strcmp(TempOrder[i].status, ORDER_PAID) != 0)
            continue;
        for (int j = 0; j < TempOrder[i].total; j++)
        {
            sum[i] += TempOrder[i].items[j].quantity * TempOrder[i].items[j].dish.Price;
        }
        if (sum[i] >= SALE)
        {
            sum[i] = sum[i] - sum[i] * 0.25;
            *revenue += sum[i];
        }
        else
        {
            *revenue += sum[i];
        }
    }
    // print the total revenue
    printf("Total revenue from %s to %s: %d\n", date1, date2, *revenue);
}