#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "menufunction.h"

void printMenu(Menu menu);
int orderDish(Menu menu, OrderItem *orderItem);
void makeOrder(Order *order);
void orderAgain(Order *order);
void createOrderID(Order *order);


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
    inputPositiveInt("Vui long chon PIN mon an", &orderItem->dish.PIN);

    while (true)
    {
        if (orderItem->dish.PIN == 0)
        {
            printf("Ban da huy viec chon mon an\n");
            return 1;
        }

        for (int i = 0; i < menu.total; i++)
        {
            if (orderItem->dish.PIN == menu.dishes[i].PIN)
            {
                orderItem->dish = menu.dishes[i];
                inputPositiveInt("Vui long nhap so luong", &orderItem->quantity);
                printf("Ban da chon mon %s voi so luong %d va gia %0.0f\n", orderItem->dish.name, orderItem->quantity, orderItem->dish.price);
                return 0;
            }
        }
        printf("Mon an voi ma PIN %d khong duoc tim thay vui long nhap lai: ", orderItem->dish.PIN);
    }
}

void makeOrder(Order *order)
{
    int i = 0;
    int Contflag = 0;
    menu = readMenu("menu.txt");
    OrderItem orderitem;
    order->total = 0;
    // yawm();
    system("color 0F");
    printMenu(menu);
    while (true)
    {
        orderDish(menu, &orderitem);
        // first loop doesn't excute
        for (int j = 0; j < order->total; j++)
        {
            if (order->items[j].dish.PIN == orderitem.dish.PIN)
            {
                order->items[j].quantity += orderitem.quantity;
                Contflag = 1;
                break;
            }
        }
        if (Contflag == 0)
        {
            order->items[i] = orderitem;
            i++;
            order->total++;
            strcpy(order->status, ORDER_PROCESSING);
        }
        else
            Contflag = 0;

        if (ynQuestion("Ban co muon dat mon an khac khong?") == 0)
        {
            if (order->total > MAX_ORDER_ITEMS)
            {
                printf("So mon an da dat vuot qua so luong cho phep.\n");
                break;
            }
            else
            {
                break;
            }
        }
    }
}

void orderAgain(Order *order)
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
// function to create and assign order ID to order not file
void createOrderID(Order *order)
{
    char buffer[BUFFER_SIZE];
    bool parsedCorrect = true;
    do
    {
        printf("Vui long nhap Order ID: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        parsedCorrect = parseInt(buffer, &order->orderID);
        if (!parsedCorrect)
        {
            printf("Vui long nhap dung Order ID.\n");
        }
    } while (!parsedCorrect);
}
