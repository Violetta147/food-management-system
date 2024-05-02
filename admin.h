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