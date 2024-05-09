#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "structs/dish.h"
#include "error-handler/error-handler.h"
#include "file-handler/file-handler.h"
#include "constant.h"

//prompt and validate the mode selection (A/C)
void enter()
{
    for(int k = 0; k < 5; ++k)
    {
        printf("Vui long nhap (A/C) de vao che do Admin/Customer: ");
        scanf("%c", &mode);
        clstd();
        if(toupper(mode) == 'A' || toupper(mode) == 'C')
        {
            break;
        }
        else
            {
            if(k == 4 || toupper(mode) == 'X')
                {
                    printf("Exiting program due to unable to identify user's role....\n");
                    yawm();
                    exit(1);
                }
            else printf("Invalid command.\n");
            }
        }
    }
//confirm password and validation for accessing admin mode
void conf()
{
    for(int i = 0; i < 5; ++i)
    {
        char pass[MAX];
        printf("Password: ");
        scanf("%s", pass);
        clstd();
        if(strcmp(pass,PASS) == 0)
        {   
            system("color 02");
            printf("ACCESS GRANTED\n");
            yawm();
            break;
        }
        else
        {
            if(i == 4 || strcasecmp(pass,x) == 0)
            {   
                system("color 04");
                printf("Failed loading program! Exiting...");
                yawm();
                exit(2);
            }
            printf("Password sai vui long nhap lai.\n");
        }
    }
}
// admin interface for choosing to "add","change","delete" dishes
void Ans()
{
    printf("Nhap X de thoat.\n");
    for(int i = 0; i < 5; ++i)
    {
        printf("What changes do you want to perform on the MENU: Add materials(A) / Change Foods Info(C) / Delete dish(es)(D) (A/C/D) : ");
        scanf("%c", &action);
        clstd();
        if(toupper(move) == 'A' || toupper(move) == 'C' || toupper(move) == 'D')
        {
            break;
        }
        else if(i == 4 || toupper(action) == 'X')
        {
            printf("No change have been done.\n");
            yawm();
            exit(4);
        }
        else printf("Invalid Command.\n");
    }
}
//function to statistically calculate the orders from a date to another date
//getListOrders consists of all the file index date.txt
//dateToInt
//countOrders counts the number of orders in a file
void stat()
{   
    //prompt user to input two dates
    char* date1 = createDate();
    char* date2 = createDate();
    if(isDateExist(date1, date2) == false)
    {
        free(date1);
        free(date2);
        return;
    }
    //if date exists
    char TimeChoice[1024];
    int time_choice;
    bool parsed_time = true;
    do
    {
        printf("1. Thong ke doanh thu trong khoang thoi gian\n");
        printf("2. Thong ke mon an duoc yeu thich trong khoang thoi gian\n");
        printf("3. Thoat\n");
        printf("Chon chuc nang: ");
        fgets(TimeChoice, 1024, stdin);
        parsed_time = parse_int(TimeChoice,&time_choice);
        if(!parsed_time)
        {
            printf("Invalid command\n");
        }
    }while(!parsed_time || (time_choice < 1 || time_choice > 4));

    if(time_choice == 3)
    {
        free(date1);
        free(date2);
        yawm();
        return;
    }

    if(time_choice == 1)
    {
        for(int i = 0)
    }


}
    









    free(date1);
    free(date2);
}

//function to statistically calculate the popularity of dishes from date to date
void pop()
{
    char* date1 = createDate();
    char* date2 = createDate();
    if(isDateExist(date1, date2) == false)
    {
        free(date1);
        free(date2);
        return;
    }


    














}
    
//function to start a new day with the cashier entering a transaction code
