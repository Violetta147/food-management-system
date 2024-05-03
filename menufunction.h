#pragma once

#include <stdio.h>
#include <string.h>
#include "structs/dish.h"
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "error-handler/error-handler.h"


//function definitions
void erase(Menu menu)
{
    int count = 0;
    erase1:
    printf("How many dishes do you want to erase: ");
    scanf("%d", &count);
    clstd();
    while(count < 0 || count > menu.total)
    {
        printf("The amount limit is around 0 and %d\n", menu.total);
        goto erase1;
    }
    if (count != 0)
    {
        int del[count];
        for(int i = 0; i < count; i++)
        {
           do
           {
            printf("Food %d PIN: ", i + 1);
            scanf("%d", &del[i]);
            clstd();
        }while(isExist(menu, del[i]) == false || isAlreadyPIN(del, i) == true || del[i] == 0);
        }
    }
    arg();
    if(toupper(ans) == 'N') printMenu()
}