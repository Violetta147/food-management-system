#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "menufunction.h"

void header();
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

void header()
{
    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }
    printf("#     # ####### #        #####  ####### #     # #######    ####### #######\n");
    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }
    printf("#  #  # #       #       #     # #     # ##   ## #             #    #     #  \n");
    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }
    printf("#  #  # #       #       #       #     # # # # # #             #    #     #  \n");
    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }
    printf("#  #  # #####   #       #       #     # #  #  # #####         #    #     #  \n");
    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }
    printf("#  #  # #       #       #       #     # #     # #             #    #     #  \n");
    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }
    printf("#  #  # #       #       #     # #     # #     # #             #    #     #  \n");
    for (int i = 0; i < 20; i++)
    {
        printf(" ");
    }
    printf(" ## ##  ####### #######  #####  ####### #     # #######       #    #######  \n");

    printf("\n");

    printf("####### ####### ######  ######  #     #    ######  #######  #####  #######    #    #     # ######     #    #     # #######\n");
    printf("   #    #       #     # #     #  #   #     #     # #       #     #    #      # #   #     # #     #   # #   ##    #    #   \n");
    printf("   #    #       #     # #     #   # #      #     # #       #          #     #   #  #     # #     #  #   #  # #   #    #   \n");
    printf("   #    #####   #     # #     #    #       ######  #####    #####     #    #     # #     # ######  #     # #  #  #    #    \n");
    printf("   #    #       #     # #     #    #       #   #   #             #    #    ####### #     # #   #   ####### #   # #    #    \n");
    printf("   #    #       #     # #     #    #       #    #  #       #     #    #    #     # #     # #    #  #     # #    ##    #    \n");
    printf("   #    ####### ######  ######     #       #     # #######  #####     #    #     #  #####  #     # #     # #     #    #    \n");

    printf("\n");

    yawm();
    printf("\033[2J\033[1;1H");
}
void display(int nameWidth, int priceUnitWidth)
{
    int pinPadding = 0;
    int pinLeftPadding = 0;
    int pinRightPadding = 0;
    int longestPIN = countDigits(menu.dishes[0].PIN);

    for(int i = 1; i < menu.total; i++)
    {
        if(longestPIN < countDigits(menu.dishes[i].PIN))
        {
            longestPIN = countDigits(menu.dishes[i].PIN);
        }
    }
    for (int i = 0; i < menu.total; i++)
    {   
        int currentPIN = countDigits(menu.dishes[i].PIN);
        if(currentPIN <= longestPIN)
        {
            if(currentPIN == 1)
            {
                pinLeftPadding = 3;
                pinRightPadding = 3;
                printf("|%*s%d%*s|", pinLeftPadding, "", menu.dishes[i].PIN, pinRightPadding, "");
                printf("");
            }
        }
        
    }
}
void printMenu()
{
    header();

    int longestPriceDigits = 0;
    int longestName = 0;
    int longestUnit = 0;

    for (int i = 0; i < menu.total; i++)
    {
        if (longestName < strlen(menu.dishes[i].name))
        {
            longestName = strlen(menu.dishes[i].name);
        }
        if (longestUnit < strlen(menu.dishes[i].Unit))
        {
            longestUnit = strlen(menu.dishes[i].Unit);
        }
        if (longestPriceDigits < countDigits(menu.dishes[i].Price))
        {
            longestPriceDigits = countDigits(menu.dishes[i].Price); // or I can use log10 + 1 to get the number of digits
        }
    }

    int nameWidth = longestName;
    int priceUnitWidth = longestPriceDigits + longestUnit;

    // HEADER & TOP BORDER
    int namePadding = nameWidth - strlen("Name");
    if (namePadding < 0)
        namePadding = -namePadding;
    int nameLeftPadding = namePadding / 2;
    int nameRightPadding = namePadding - nameLeftPadding;

    int priceUnitPadding = priceUnitWidth - strlen("Price/Unit");
    if (priceUnitPadding < 0)
        priceUnitPadding = -priceUnitPadding;
    int priceUnitLeftPadding = priceUnitPadding / 2;
    int priceUnitRightPadding = priceUnitPadding - priceUnitLeftPadding;

    int pinPadding = 2;
    int pinLeftPadding = pinPadding / 2;
    int pinRightPadding = pinPadding - pinLeftPadding;

    printf("+");
    for (int i = 0; i < pinLeftPadding + 3 + pinRightPadding + 2; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < nameLeftPadding + 4 + nameRightPadding + 2; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < priceUnitLeftPadding + 10 + priceUnitRightPadding + 2; i++)
    {
        printf("-");
    }
    printf("+\n");

    printf("| %*s%s%*s | %*s%s%*s | %*s%s%*s |\n",
           pinLeftPadding, "", "PIN", pinRightPadding, "",
           nameLeftPadding, "", "Name", nameRightPadding, "",
           priceUnitLeftPadding, "", "Price/Unit", priceUnitRightPadding, "");

    // MIDDLE BORDER
    printf("+");
    for (int i = 0; i < pinLeftPadding + 3 + pinRightPadding + 2; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < nameLeftPadding + 4 + nameRightPadding + 2; i++)
    {
        printf("-");
    }
    printf("+");
    for (int i = 0; i < priceUnitLeftPadding + 10 + priceUnitRightPadding + 2; i++)
    {
        printf("-");
    }
    printf("+\n");
    display(nameWidth, priceUnitWidth);
}

int orderDish(OrderItem *orderItem)
{
    inputPositiveInt("Enter PIN of the dish you wanna order", &orderItem->dish.PIN);
    fflush(stdin);
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
    readMenu("menu.txt");
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
        readMenu("menu.txt");
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
