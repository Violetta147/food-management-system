#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "menufunction.h"

void printMenu();
void display();
int orderDish(OrderItem *orderItem);
void makeOrder(Order *order);
void orderAgain(Order *order);
void createOrderID(Order *order);
void resetOrder(Order *order);
void Customer();
void calculateBill(Order *order, int *sum, int *sale, int *total);
bool UnpaidBill();

void display()
{
    for (int i = 0; i < menu.total; i++)
    {
        if (menu.dishes[i].Status == 1)
        {
            char hole[5];
            sprintf(hole, "%d", menu.dishes[i].PIN);
            int q = ((11 - strlen(hole)) / 2) + strlen(hole) + (strlen(hole) + 1) % 2;
            printf("%9c%*d", '|', q, menu.dishes[i].PIN);
            int F = ((11 - strlen(hole)) / 2);
            for (; F > 0; F--)
            {
                printf(" ");
            }
            printf("|");
            q = ((24 - strlen(menu.dishes[i].name)) / 2) + strlen(menu.dishes[i].name) + (strlen(menu.dishes[i].name)) % 2;
            printf("%*s", q, menu.dishes[i].name);
            F = ((24 - strlen(menu.dishes[i].name)) / 2);
            for (; F > 2; F--)
            {
                printf(" ");
            }
            printf("|");
            // print price and unit on the same line seperated by /
            printf("%*d/%s|", 21 - strlen(menu.dishes[i].Unit) - 1, menu.dishes[i].Price, menu.dishes[i].Unit); //-1 because of / 
            printf("\n");
        }
        else if (toupper(mode) == 'A')
        {
            if (menu.dishes[i].Status == 0)
            {
                printf("\033[0;31m"); // SET COLOR TO RED
            }
            char hole[5];
            sprintf(hole, "%d", menu.dishes[i].PIN);
            int q = ((11 - strlen(hole)) / 2) + strlen(hole) + (strlen(hole) + 1) % 2;
            printf("%9c%*d", '|', q, menu.dishes[i].PIN);
            int F = ((11 - strlen(hole)) / 2);
            for (; F > 0; F--)
            {
                printf(" ");
            }
            printf("|");
            q = ((24 - strlen(menu.dishes[i].name)) / 2) + strlen(menu.dishes[i].name) + (strlen(menu.dishes[i].name)) % 2;
            printf("%*s", q, menu.dishes[i].name);
            F = ((24 - strlen(menu.dishes[i].name)) / 2);
            for (; F > 2; F--)
            {
                printf(" ");
            }
            printf("|");
            // print price and unit on the same line seperated by /
            printf("%*d/%s|", 21 - strlen(menu.dishes[i].Unit) - 1, menu.dishes[i].Price, menu.dishes[i].Unit);
            printf("\n");
        }
        // RESET COLOR TO NORMAL
        printf("\033[0m");
    }
    return;
}
void printMenu()
{
    printf("\nWELCOME TO TEDDY RESTAURANT\n");
    printf("%9c", '+');
    for (int i = 0; i < 11; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < 22; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < 21; i++)
    {
        printf("-");
    }
    printf("+\n");
    printf("        |    PIN    |        Dishes        |        Price        |\n");
    printf("\t");
    printf("|");
    for (int i = 0; i < 11; i++)
    {
        printf("-");
    }
    printf("|");
    for (int i = 0; i < 22; i++)
    {
        printf("-");
    }
    printf("|");
    for (int i = 0; i < 21; i++)
    {
        printf("-");
    }
    printf("|\n");
    display();
    printf("%9c", '+');
    for (int i = 0; i < 11; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < 22; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < 21; i++)
    {
        printf("-");
    }
    printf("+\n");
}

int orderDish(OrderItem *orderItem)
{
    inputPositiveInt("Enter PIN of the dish you wanna order", &orderItem->dish.PIN);
    while (true)
    {
        if (orderItem->dish.PIN == 0)
        {
            printf("You stopped ordering.\n");
            return 1;
        }
        for (int i = 0; i < menu.total; i++)
        {
            if (orderItem->dish.PIN == menu.dishes[i].PIN)
            {
                orderItem->dish = menu.dishes[i];
                inputPositiveInt("How many of this dish you want to order", &orderItem->quantity);
                printf("You chose %s with the amount of %d %s and price for each is %d\n", orderItem->dish.name, orderItem->quantity, orderItem->dish.Unit, orderItem->dish.Price);
                return 0;
            }
            // NO PIN FOUND MATCHED THE INPUT
            if (i == menu.total - 1)
            {
                printf("DISH WITH PIN %d NOT FOUND.\n", orderItem->dish.PIN);
                inputPositiveInt("Enter PIN of the dish you wanna orer", &orderItem->dish.PIN);
            }
        }
    }
}

void makeOrder(Order *order)
{
    int i = 0;
    int ContFlag = 0;
    menu = readMenu("menu.txt");
    OrderItem OrderItem;
    order->total = 0;
    // yawm();
    system("color 0F");
    printMenu();
    while (true)
    {
        orderDish(&OrderItem);
        // first loop doesn't excute
        for (int j = 0; j < order->total; j++)
        {
            if (order->items[j].dish.PIN == OrderItem.dish.PIN)
            {
                order->items[j].quantity += OrderItem.quantity;
                ContFlag = 1;
                break;
            }
        }
        if (ContFlag == 0)
        {
            order->items[i] = OrderItem;
            i++;
            order->total++;
            strcpy(order->status, ORDER_PROCESSING);
        }
        else
            ContFlag = 0;
        if (ynQuestion("Do you want to order anything else?") == 0)
        {
            if (order->total > MAX_ORDER_ITEMS)
            {
                printf("Number of dishes exceeds 5.\n");
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

    if (ynQuestion("Do you want to make another Order?"))
    {
        Menu menu = readMenu("menu.txt");
        OrderItem orderitem;
        yawm();
        system("color 0F");
        makeOrder(order);
    }
    else
        printf("Thank you for using our service.\n");
}
// function to create and assign order ID to order not file
void createOrderID(Order *order)
{
    char buffer[BUFFER_SIZE];
    bool parsedCorrect = true;
    do
    {
        printf("Please enter ORDER ID: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        parsedCorrect = parseInt(buffer, &order->orderID);
        if (!parsedCorrect)
        {
            printf("ORDER ID INVALID.\n");
        }
    } while (!parsedCorrect);
}
// function to reset the order
void resetOrder(Order *order)
{
    order->total = 0;
    order->orderID = 0;
    strcpy(order->status, ORDER_PROCESSING);
}
// function to prompt customers to choose these options
// 1. Make Order & Payment
// 2. Pay unpaid bill
void Customer()
{
    Order order;
    int sum;
    int sale;
    int total;
    int revenue;
    bool isLoop = true;

    while (isLoop)
    {
        int choice;
        printf("1.Order and pay\n");
        printf("2.Unpaid bills\n");
        printf("3.Exit\n");

        inputPositiveInt("Please choose 1 option", &choice);
        if (choice == 1)
        {
            makeOrder(&order);
            if (order.items[0].dish.PIN == 0)
            {
                printf("You have not ordered anything.\n");
                break;
            }
            else if (order.total > 0)
            {
                printf("Calculating bill...\n");
                calculateBill(&order, &sum, &sale, &total);
                resetOrder(&order);
            }
        }
        else if (choice == 2)
        {
            bool ContinueToPay = true;
            while (ContinueToPay)
            {
                UnpaidBill();
                ContinueToPay = ynQuestion("Do you want to continue paying for unpaid bills?");
            }
        }
        else if (choice == 3)
        {
            isLoop = false;
        }
    }
    return;
}
