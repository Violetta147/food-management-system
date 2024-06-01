#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "menufunction.h"

void header();
void printMenu();
void display(int totalDishes, int temp1, int temp2, int temp3, int temp4);
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
void display(int totalItems, int temp1 , int temp2, int temp3, int temp4)
{
    int currentPINLength = countDigits(menu.dishes[totalItems].PIN);
    int currentPriceLength = countDigits(menu.dishes[totalItems].Price);
    int currentNameLength = strlen(menu.dishes[totalItems].name);
    int currentUnitLength = strlen(menu.dishes[totalItems].Unit);

    int pinLeftPadding = (temp1 - currentPINLength) / 2 + (temp1 - currentPINLength) % 2;
    int pinRightPadding = temp1 - currentPINLength - pinLeftPadding;
    int nameLeftPadding = (temp2 - currentNameLength) / 2 + (temp2 - currentNameLength) % 2;
    int nameRightPadding = temp2 - currentNameLength - nameLeftPadding;
    int priceLeftPadding = (temp3 - currentPriceLength) / 2 + (temp3 - currentPriceLength) % 2;
    int priceRightPadding = temp3 - currentPriceLength - priceLeftPadding;
    int unitLeftPadding = (temp4 - currentUnitLength) / 2 + (temp4 - currentUnitLength) % 2;
    int unitRightPadding = temp4 - currentUnitLength - unitLeftPadding;
    
    printf("|");
    printf("%*s%d%*s", pinLeftPadding, "", menu.dishes[totalItems].PIN, pinRightPadding, "");
    printf("|");
    printf("%s%*s", menu.dishes[totalItems].name, nameRightPadding + nameLeftPadding, "");
    printf("|");
    printf("%*s%d%*s", priceLeftPadding, "", menu.dishes[totalItems].Price, priceRightPadding, "");
    printf("|");
    printf("%*s%s%*s", unitLeftPadding, "", menu.dishes[totalItems].Unit, unitRightPadding, "");
    printf("|\n");
    
    
}
void printMenu()
{
    header();
    
    int longestPriceDigits = countDigits(menu.dishes[0].Price);
    int longestName = strlen(menu.dishes[0].name);
    int longestUnit = strlen(menu.dishes[0].Unit);
    int longestPIN = countDigits(menu.dishes[0].PIN);

    for(int i = 1; i < menu.total; i++) 
    {   
        if(longestPIN < countDigits(menu.dishes[i].PIN))
        {
            longestPIN = countDigits(menu.dishes[i].PIN);
        }
        if(longestName < strlen(menu.dishes[i].name))
        {
            longestName = strlen(menu.dishes[i].name);
        }
        if(longestUnit < strlen(menu.dishes[i].Unit));
        {
            longestUnit = strlen(menu.dishes[i].Unit);
        }
        if(longestPriceDigits < countDigits(menu.dishes[i].Price))
        {
            longestPriceDigits = countDigits(menu.dishes[i].Price);
        }
    }

    int pinWidth = longestPIN;
    int nameWidth = longestName;
    int priceWidth = longestPriceDigits;
    int unitWidth = longestUnit;

    //TOP BORDER
    nameWidth = nameWidth - 4;
    if(nameWidth < 0)
        nameWidth = -nameWidth;
    int nameLeftPadding = nameWidth / 2;
    int nameRightPadding = nameWidth - nameLeftPadding;
    
    pinWidth = pinWidth - 5; //Ma so
    if(pinWidth < 0)
        pinWidth = -pinWidth;
    int pinLeftPadding = pinWidth / 2;
    int pinRightPadding = pinWidth - pinLeftPadding;

    priceWidth = priceWidth - 5;
    if(priceWidth < 0)
        priceWidth = -priceWidth;
    int priceLeftPadding = priceWidth / 2;
    int priceRightPadding = priceWidth - priceLeftPadding;

    unitWidth = unitWidth - 4;
    if(unitWidth < 0)
        unitWidth = -unitWidth;
    int unitLeftPadding = unitWidth / 2;
    int unitRightPadding = unitWidth - unitLeftPadding;

    int temp1, temp2, temp3, temp4;

    temp1 = pinLeftPadding + 5 + pinRightPadding;
    temp2 = nameLeftPadding + 4 + nameRightPadding;
    temp3 = priceLeftPadding + 5 + priceRightPadding;
    temp4 = unitLeftPadding + 4 + unitRightPadding;

    printf("+");
    for(int i = 0; i < temp1; i++) printf("-");
    printf("+");
    for(int i = 0; i < temp2; i++) printf("-");
    printf("+");
    for(int i = 0; i < temp3; i++) printf("-");
    printf("+");
    for(int i = 0; i < temp4; i++) printf("-");
    printf("+\n");

    //HEADER

    printf("|");
    for(int i = 0; i < pinLeftPadding; i++) printf(" ");
    printf("Ma so");
    for(int i = 0; i < pinRightPadding; i++) printf(" ");
    printf("|");
    for(int i = 0; i < nameLeftPadding; i++) printf(" ");
    printf("NAME");
    for(int i = 0; i < nameRightPadding; i++) printf(" ");
    printf("|");
    for(int i = 0; i < priceLeftPadding; i++) printf(" ");
    printf("PRICE");
    for(int i = 0; i < priceRightPadding; i++) printf(" ");
    printf("|");
    for(int i = 0; i < unitLeftPadding; i++) printf(" ");
    printf("UNIT");
    for(int i = 0; i < unitRightPadding; i++) printf(" ");
    printf("|\n");

    //MIDDLE BORDER
    printf("+");
    for(int i = 0; i < temp1; i++) printf("-");
    printf("+");
    for(int i = 0; i < temp2; i++) printf("-");
    printf("+");
    for(int i = 0; i < temp3; i++) printf("-");
    printf("+");
    for(int i = 0; i < temp4; i++) printf("-");
    printf("+\n");

    int total = 0;
    while(true)
    {   
        if(total == menu.total)
        {
            break;
        }
        display(total, temp1, temp2, temp3, temp4);
        //SEPERATOR
        printf("+");
        for(int i = 0; i < temp1; i++) printf("-");
        printf("+");
        for(int i = 0; i < temp2; i++) printf("-");
        printf("+");
        for(int i = 0; i < temp3; i++) printf("-");
        printf("+");
        for(int i = 0; i < temp4; i++) printf("-");
        printf("+\n");
        ++total;
    }
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
    if (menu.total == 0)
    {
        printf("OUR RESTAURANT IS CURRENTLY CLOSED. PLEASE COMEBACK LATER\n");
        yawm();
        exit(0);
    }
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
