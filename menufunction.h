#pragma once

#include <stdio.h>
#include <string.h>
#include "structs/dish.h"
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "error-handler/error-handler.h"
#include "constant.h"
#include "customer.h"

// function prototypes
void printMenu();
void display(int nameWidth, int longestPriceDigits, int longestUnit);
void Erase();
void Delete(int arrayPIN[], int count);
void wandp();
void resetMenu();

void appendMenu();
void custom();
void Customize(int PIN);

void inputPositiveInt(const char *question, int *num);
void inputInt(const char *question, int *num);
bool input(const char *question, char str[]);
int ynQuestion(const char *question);

// 1. DELETE
/*----------------------------------------------------------------------*/
// function to delete one dish in the menu at a time
void Erase()
{
    int count = 1;
    int del[MAX];
    inputInt("Enter the PIN of the dish you want to delete", &del[0]);
    while (isRepeatPIN(menu, del[0]) == false || del[0] < 0)
    {
        if (del[0] < 0)
        {
            printf("Please enter non negative integer!\n");
            inputInt("Enter the PIN of the dish you want to delete", &del[0]);
        }
        else
        {
            printf("Did not find the dish with PIN %d\n", del[0]);
            inputInt("Enter the PIN of the dish you want to delete", &del[0]);
        }
    }
    do
    {
        printf("Are you sure you want to delete this dish?(Y/N) : ");
        scanf("%c", &ans);
        clstd();
    } while (myToUpper(ans) != 'N' && myToUpper(ans) != 'Y' && myToUpper(ans) != 'X');
    if (myToUpper(ans) == 'N')
    {
        printf("No change was applied.\n");
        yawm();
        printMenu();
    }
    else if (myToUpper(ans) == 'Y')
    {
        Delete(del, count);
        printf("\033[2J\033[1;1H");
        wandp();
    }
    else
    {
        printf("Exiting Program.\n");
        yawm();
        exit(1);
    }
}
void Delete(int arrayPIN[], int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < menu.total; j++)
        {
            if (menu.dishes[j].PIN == arrayPIN[i])
            {
                for (int k = j; k < menu.total - 1; k++)
                {
                    menu.dishes[k] = menu.dishes[k + 1];
                }
                (menu.total)--;
                break;
            }
        }
    }
    return;
}
// write the menu back after deletion and read back into global variable menu
void wandp()
{
    writeMenu("menu.txt");
    printf("Change applied.\n");
    resetMenu();
    readMenu("menu.txt");
    printMenu();
    return;
}
void resetMenu()
{
    int arrayPIN[MAX];
    int count = 0;
    for (int i = 0; i < menu.total; i++)
    {
        arrayPIN[i] = menu.dishes[i].PIN;
        count++;
    }
    Delete(arrayPIN, count);
    return;
}
/*----------------------------------------------------------------------*/
// 2. ADD
/*----------------------------------------------------------------------*/
// FUNCTION TO ADD "1 DISH AT A TIME" INTO MENU
void appendMenu()
{
    Dish Temp;
    printf("Here you can add new dishes into menu.\n");
    /*--------------------------------------------------------*/
    input("Enter new dish's name", Temp.name);
    while (isSameName(menu, Temp.name) == true)
    {
        printf("Please use other names not to confuse anyone.\n");
        input("Enter new dish's name", Temp.name);
    }
    /*----------------------------------------------------------*/
    inputInt("Enter new dish's PIN", &Temp.PIN);
    while (isRepeatPIN(menu, Temp.PIN) == true || Temp.PIN < 0)
    {
        printf("The PIN you entered already existed before. Please choose another PIN!\n");
        inputInt("Enter new dish's PIN", &Temp.PIN);
    }
    /*----------------------------------------------------------*/
    inputPositiveInt("Enter new dish's price", &Temp.Price);
    /*----------------------------------------------------------*/
    inputInt("Enter the status of the dish (1 for available, 0 for not available)", &Temp.Status);
    while (Temp.Status != 0 && Temp.Status != 1)
    {
        printf("Please enter 1 or 0\n");
        inputInt("Enter the status of the dish (1 for available, 0 for not available)", &Temp.Status);
    }
    /*----------------------------------------------------------*/
    input("Enter new dish's Unit", Temp.Unit);
    while (true)
    {
        for (int i = 0; i < strlen(Temp.Unit); i++)
        {
            if (myIsAlpha(Temp.Unit[i]) == false)
            {   
                printf("Unit should not include special characters or number\n");
                input("Enter dish's new Unit", Temp.Unit);
            }
        }
        break;
    }
    /*----------------------------------------------------------*/
    // CONFIRMATION
    //  y for yes, n for no, x for exit
    do
    {
        printf("Are you sure you want to add this dish?(Y/N) : ");
        scanf("%c", &ans);
        clstd();
    } while (myToUpper(ans) != 'N' && myToUpper(ans) != 'Y' && myToUpper(ans) != 'X');
    if (myToUpper(ans) == 'N')
    {
        printf("No change was applied.\n");
        yawm();
        printMenu();
    }
    else if (myToUpper(ans) == 'Y')
    {
        menu.dishes[menu.total] = Temp;
        ++(menu.total);
        wandp();
    }
    else
    {
        printf("Exiting Program.\n");
        yawm();
        exit(1);
    }
}
/*----------------------------------------------------------------------*/
// 3. CUSTOMIZATION
/*----------------------------------------------------------------------*/
// FUNCTION TO CUSTOMIZE A DISH
void custom()
{
    int FoodPIN;
    inputInt("Enter the PIN of the dish you wanna customize", &FoodPIN);
    while (isRepeatPIN(menu, FoodPIN) == false || FoodPIN < 0)
    {
        if (FoodPIN < 0)
        {
            printf("Please enter non negative integer!\n");
            inputInt("Enter the PIN of the dish you wanna customize", &FoodPIN);
        }
        else
        {
            printf("Sorry but no PIN was found matched code %d\n", FoodPIN);
            inputInt("Enter the PIN of the dish you wanna customize", &FoodPIN);
        }
    }
    if (FoodPIN == 0)
    {
        printf("YOU CANCELLED.\n");
        return;
    }
    else if (FoodPIN != 0)
    {
        Customize(FoodPIN);
    }
}
void Customize(int PIN)
{
    Dish Temp;
    int Pivot = 0;
    for (int i = 0; i < menu.total; i++)
    {
        if (menu.dishes[i].PIN == PIN)
        {
            Pivot = i;
            break;
        }
    }
    printf("Here you can change dish's information, type '0' if you don't wanna make change to a field.\n");
    /*-----------------------NAME FIELD--------------------------*/
    printf("Dish current name: %s\n", menu.dishes[Pivot].name);
    input("Enter dish's new name", Temp.name);
    while (true)
    {
        if (isSameName(menu, Temp.name) == true)
        {
            printf("Name already exists. Enter another name.\n");
            input("Enter dish's new name", Temp.name);
        }
        else if (strlen(Temp.name) > MAX)
        {
            printf("Name's length is too long, max length is 30 characters.\n");
            input("Enter dish's new name", Temp.name);
        }
        else
        {
            for (int i = 0; i < strlen(Temp.name); i++)
            {
                if (myIsAlpha(Temp.name[i]) == false)
                {
                    printf("Name should not include special characters or number\n");
                    input("Enter dish's new name", Temp.name);
                }
            }
        }
        // SUCCESS VALIDATING NAME
        break;
    }
    if (strcmp(Temp.name, "0") == 0)
        strcpy(Temp.name, menu.dishes[Pivot].name);
    /*-----------------------PIN FIELD--------------------------*/
    printf("Dish's current PIN: %d\n", menu.dishes[Pivot].PIN);
    inputInt("Enter dish's new PIN", &Temp.PIN);

    while (true)
    {
        if (isRepeatPIN(menu, Temp.PIN) == true)
        {
            printf("PIN already exists. Enter another PIN.\n");
            inputInt("Enter dish's new PIN", &Temp.PIN);
        }
        else if (Temp.PIN < 0)
        {
            printf("Please enter non negative integer!\n");
            inputInt("Enter dish's new PIN", &Temp.PIN);
        }
        else
        {
            // SUCCESS VALIDATING PIN
            break;
        }
    }
    if (Temp.PIN == 0)
    {
        Temp.PIN = menu.dishes[Pivot].PIN;
    }
    /*-----------------------PRICE FIELD--------------------------*/
    printf("Dish's current price: %d\n", menu.dishes[Pivot].Price);
    while (true)
    {
        inputPositiveInt("Enter dish's new price", &Temp.Price);
        break;
    }
    if (Temp.Price == 0)
    {
        Temp.Price = menu.dishes[Pivot].Price;
    }
    /*-----------------------STATUS FIELD--------------------------*/

    printf("Dish's current status: %d\n", menu.dishes[Pivot].Status);
    int Yn = ynQuestion("Do you want to switch status?");
    if (Yn == true)
    {
        Temp.Status = (menu.dishes[Pivot].Status + 1) % 2;
    }
    /*------------------------UNIT FIELD---------------------------*/
    printf("Dish's current unit: %s\n", menu.dishes[Pivot].Unit);
    input("Enter dish's new unit", Temp.Unit);
    while (true)
    {
        for (int i = 0; i < strlen(Temp.Unit); i++)
        {
            if (myIsAlpha(Temp.Unit[i]) == false)
            {
                printf("Unit should not include special characters or number\n");
                input("Enter dish's new unit", Temp.Unit);
            }
        }
        break;
    }
    if (strcmp(Temp.Unit, "0") == 0)
        strcpy(Temp.Unit, menu.dishes[Pivot].Unit);

    /*-----------------------CONFIRMATION--------------------------*/
    //  y for yes, n for no, x for exit
    do
    {
        printf("Are you sure you want to customize this dish?(Y/N) : ");
        scanf("%c", &ans);
        clstd();
    } while (myToUpper(ans) != 'N' && myToUpper(ans) != 'Y' && myToUpper(ans) != 'X');
    if (myToUpper(ans) == 'N')
    {
        printf("No change was applied.\n");
        yawm();
        printMenu();
    }
    else if (myToUpper(ans) == 'Y')
    {
        menu.dishes[Pivot] = Temp;
        printf("\033[2J\033[1;1H");
        wandp();
    }
    else
    {
        printf("Exiting Program.\n");
        yawm();
        exit(1);
    }
}
/*----------------------------------------------------------------------*/
int ynQuestion(const char *question)
{
    printf("%s [Y/N]: ", question);
    while (true)
    {
        char tmp[1000];
        scanf("%s", tmp);
        clstd();
        fflush(stdin);
        if (isYes(tmp))
            return true;
        if (isNo(tmp))
            return false;
        printf("Please enter yes or no [Y/N]: ");
    }
}
// input string + ask question
bool input(const char *question, char str[])
{
    printf("%s: ", question);
    fgets(str, MAX_STRING_LENGTH, stdin);
    str[strlen(str) - 1] = '\0';
    fflush(stdin);
    if(strlen(str) > 0)
    {
        return true;
    }
    return false;
}
void inputInt(const char *question, int *num)
{
    bool isValid = false;
    while (!isValid)
    {
        char tmp[MAX_STRING_LENGTH];
        isValid = input(question, tmp) && parseInt(tmp, num);
        if (!isValid)
        {
            printf("Please enter integer!\n");
        }
    }
}

void inputPositiveInt(const char *question, int *num)
{
    inputInt(question, num);
    while (*num <= 0)
    {
        printf("Please enter positive integer!\n");
        inputInt(question, num);
    }
}