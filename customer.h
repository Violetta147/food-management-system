#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "menufunction.h"

void printMenu(Menu menu)
{
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
        printf("%17d  %17s  %14.0f \n", menu.dishes[i].PIN, menu.dishes[i].name, menu.dishes[i].price);
    }
    printf("\n");
}

int orderDish(Menu menu, OrderItem *orderItem)
{

    printf("Vui long chon mon an theo ma PIN: ");
    int dishPIN;
    int result; // truyen du lieu dishPIN cho result de check
    while ((result = scanf("%d", &dishPIN)) != 1)
    {
        while (getchar() != '\n')
            ; // clear input buffer
        printf("Vui long nhap dung ma PIN: ");
    }
    clstd();

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
                while(scanf("%d", &orderItem->quantity) != 1)
                {   
                    if(orderItem->quantity <= 0)
                        {
                            clstd();
                            printf("Vui long nhap dung so luong: ");
                        }
                    else
                    {
                        clstd();
                        printf("Vui long nhap dung so luong: ");
                    }
                }
                printf("Ban da chon mon %s voi so luong %d va gia %0.0f\n", orderItem->dish.name, orderItem->quantity, orderItem->dish.price);
                return 0;
            }
        }
        printf("Mon an voi ma PIN %d khong duoc tim thay vui long nhap lai: ", dishPIN);
        while ((result = scanf("%d", &dishPIN)) != 1)
        {
            while (getchar() != '\n'); // clear input buffer
            printf("\nVui long nhap dung ma PIN: ");
        }
    }
}


void makeOrder(Order *order)
{   int i = 0;
    int Contflag = 0;
    menu = readMenu("menu.txt");
    OrderItem orderitem;
    order->total = 0;
    yawm();
    system("color 0F");
    printMenu(menu);
    while (true)
    {   
        orderDish(menu, &orderitem);
        //first loop doesn't excute
        for(int j = 0; j < order->total; j++)
        {
            if(order->items[j].dish.PIN == orderitem.dish.PIN)
            {
                order->items[j].quantity += orderitem.quantity;
                Contflag = 1;
                break;
            }
        }
        if(Contflag == 0)
        {
        order->items[i] = orderitem;
        i++;
        order->total++;
        order->status = ORDER_PROCESSING;
        }
        else Contflag = 0;

        if (ynQuestion("Ban co muon dat mon an khac khong?") == 0)
        {   
            if (order->total > MAX_ORDER_ITEMS)
                break;
            else
            {
                createOrderID(order);
                break;
            }
        }
    }
}

void OrderAgain(Order *order)
{

    if (ynQuestion("Ban co muon dat order khac khong?"))
    {
        Menu menu = readMenu("menu.txt");
        OrderItem orderitem;
        yawm();
        system("color 0F");
        makeOrder(order);
    }
    else
        printf("Cam on quy khach da su dung dich vu cua chung toi.\n");
}
//function to create and assign order ID to order not file
void createOrderID(Order *order)
{
    order->orderID = 0;
    //prompt user to enter order ID
    //what if user enter a character?
    printf("Vui long nhap ma don hang: ");
    while (scanf("%d", &order->orderID) != 1 || order->orderID <= 0)
    {
        clstd();    
        printf("Vui long nhap dung ma don hang: ");
    }
    clstd();
}
