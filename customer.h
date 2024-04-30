#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs/order.h"
#include "file-handler/file-handler.h"

void printMenu()
{
    Menu menu = readMenu("menu.txt");
    printf("\nWelcome to Teddy Restaurant!\n");

    printf("\n%17s  %17s  %14s\n", "PIN", "Dishes", "Price");
    for (int i = 0; i < 10; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < 50; i++)
    {
        printf("_");
    }
    printf("\n");
    for (int i = 0; i < menu.total; i++)
    {
        printf("%17d  %17s   %14.0f \n", menu.dishes[i].PIN, menu.dishes[i].name, menu.dishes[i].price);
    }
    printf("\n");
}

int orderDish(Menu menu, OrderItem *orderItem)
{
    printf("Vui long chon mon an theo ma PIN: ");

    int dishPIN;
    scanf("%d", &dishPIN);
    while (true)
    {
        if (dishPIN == 0)
        {
            printf("Ban da huy viec chon mon an\n");
            return 1;
        }

        for (int i = 0; i < menu.total; i++)
        {
            if (dishPIN == menu.dishes[i].PIN)
            {
                orderItem->dish = menu.dishes[i];
                printf("Vui long nhap so luong mon an: ");
                scanf("%d", &orderItem->quantity);
                printf("Ban da chon mon %s voi so luong %d va gia %0.0f\n", orderItem->dish.name, orderItem->quantity,orderItem->dish.price);
                return 0;
            }
        }
        printf("Mon an voi ma PIN %d khong duoc tim thay vui long nhap lai: ", dishPIN);
        scanf("%d", &dishPIN);
    }
}