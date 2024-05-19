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
void Erase();
void Delete(int PIN);
void wandp();
void resetMenu();
void appendMenu();
void printMenu(Menu menu);
void custom(Menu menu);
void Customize(int PIN);
int ynQuestion(const char *question);
void input(const char *question, char *str);
void inputInt(const char *question, int *num);
void inputPositiveInt(const char *question, int *num);

// 1. DELETE
/*----------------------------------------------------------------------*/
// function to delete one dish in the menu at a time
void Erase()
{
    int FoodPIN;
    inputInt("Nhap ma PIN cua mon an ban muon xoa", &FoodPIN);
    while (isRepeatPIN(menu, FoodPIN) == false || FoodPIN < 0)
    {
        if (FoodPIN < 0)
        {
            printf("Vui long nhap so nguyen ko am!\n");
            inputInt("Nhap ma PIN cua mon an ban muon xoa", &FoodPIN);
        }
        else
        {
            printf("Khong tim thay mon an tuong ung voi ma PIN %d\n", FoodPIN);
            inputInt("Nhap ma PIN cua mon an ban muon xoa", &FoodPIN);
        }
    }
    if (FoodPIN == 0)
    {
        printf("Ban da huy viec chon mon an\n");
        return;
    }
    Delete(FoodPIN);
}
void Delete(int PIN)
{
    int Pivot = 0;
    for (int i = 0; i < menu.total; i++)
    {
        if (menu.dishes[i].PIN == PIN)
        {
            Pivot = i;
            break;
        }
    }
    int Yn = ynQuestion("Ban co chac chan muon xoa mon an nay khong?");
    if (Yn == true)
    {
        menu = readMenu("menu.txt");
        for (int i = Pivot; i < menu.total - 1; i++)
        {
            menu.dishes[i] = menu.dishes[i + 1];
        }
        menu.total--;
        wandp();
    }
    else if (Yn == false)
    {
        printf("Ban da huy viec xoa mon an\n");
    }
    return;
}
// write the menu back after deletion and read back into global variable menu
void wandp()
{
    writeMenu("menu.txt", menu, false);
    printf("Da xoa mon an thanh cong!\n");
    menu = readMenu("menu.txt");
    printMenu(menu);
    return;
}
/*----------------------------------------------------------------------*/
// 2. ADD
/*----------------------------------------------------------------------*/
// function to add one dish at a time
void appendMenu()
{
    Dish Temp;
    printf("Tai day ban co the them mon an moi vao menu.\n");
    /*--------------------------------------------------------*/
    input("Nhap ten mon an", Temp.name);
    while (isSameName(menu, Temp.name) == true)
    {
        printf("Ten mon an da ton tai. Vui long nhap lai.\n");
        input("Nhap ten mon an", Temp.name);
    }
    /*----------------------------------------------------------*/
    inputInt("Nhap ma PIN", &Temp.PIN);
    while (isRepeatPIN(menu, Temp.PIN) == true || Temp.PIN < 0)
    {
        printf("Ma PIN da ton tai. Vui long nhap lai.\n");
        inputInt("Nhap ma PIN", &Temp.PIN);
    }
    /*----------------------------------------------------------*/
    inputPositiveInt("Nhap gia tien", &Temp.price);
    int Yn = ynQuestion("Ban co chac chan muon them mon an nay khong?");
    if (Yn == true)
    {
        menu.dishes[menu.total] = Temp;
        menu.total++;
    }
    // delete the file data and write the new menu(is not necessary because "w" will overwrite the file)
    //overwrite the file with the new menu
    printf("\033[2J\033[1;1H");
    writeMenu("menu.txt", menu, false);
    menu = readMenu("menu.txt");
    printMenu(menu);
    return;
}
/*----------------------------------------------------------------------*/
// 3. CHANGE
/*----------------------------------------------------------------------*/
// function to change one dish's information at a time
void custom(Menu menu)
{
    int FoodPIN;
    inputInt("Nhap ma PIN cua mon an ban muon thay doi", &FoodPIN);
    while (isRepeatPIN(menu, FoodPIN) == false || FoodPIN < 0)
    {
        if (FoodPIN < 0)
        {
            printf("Vui long nhap so nguyen ko am!\n");
            inputInt("Nhap ma PIN cua mon an ban muon thay doi", &FoodPIN);
        }
        else
        {
            printf("Khong tim thay mon an tuong ung voi ma PIN %d\n", FoodPIN);
            inputInt("Nhap ma PIN cua mon an ban muon thay doi", &FoodPIN);
        }
    }
    if (FoodPIN == 0)
    {
        printf("Ban da huy viec chon mon an\n");
        return;
    }
    Customize(FoodPIN);
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
    printf("Tai day ban co the thay doi nhieu thong tin cua mon an. Nhap 0 doi voi thong tin ban khong muon thay doi.\n");
    /*-----------------------NAME FIELD--------------------------*/
    printf("Ten mon an hien tai: %s\n", menu.dishes[Pivot].name);
    while (true)
    {
        input("Nhap ten mon an moi", Temp.name);
        if (isSameName(menu, Temp.name) == true)
        {
            printf("Ten mon an da ton tai. Vui long nhap lai.\n");
        }
        else if (strlen(Temp.name) > MAX)
        {
            printf("Ten mon an qua dai. Vui long nhap lai.\n");
        }
        else
        {
            break;
        }
    }
    if (strcmp(Temp.name, "0") == 0)
    {
        strcpy(Temp.name, menu.dishes[Pivot].name);
    }
    /*-----------------------PIN FIELD--------------------------*/
    printf("Ma PIN hien tai: %d\n", menu.dishes[Pivot].PIN);
    while (true)
    {
        inputInt("Nhap ma PIN moi", &Temp.PIN);
        if (isRepeatPIN(menu, Temp.PIN) == true)
        {
            printf("Ma PIN da ton tai. Vui long nhap lai.\n");
        }
        else if (Temp.PIN < 0)
        {
            printf("Vui long nhap so nguyen ko am!\n");
        }
        else
        {
            break;
        }
    }
    if (Temp.PIN == 0)
    {
        Temp.PIN = menu.dishes[Pivot].PIN;
    }
    /*-----------------------PRICE FIELD--------------------------*/
    printf("Gia tien hien tai: %d\n", menu.dishes[Pivot].price);
    while (true)
    {
        inputPositiveInt("Nhap gia tien moi", &Temp.price);
        break;
    }
    if (Temp.price == 0)
    {
        Temp.price = menu.dishes[Pivot].price;
    }
    /*-----------------------CONFIRMATION--------------------------*/
    int yn = ynQuestion("Ban co chac chan muon thay doi thong tin mon an nay khong?");
    if (yn == true)
    {
        menu.dishes[Pivot] = Temp;
    }
    printf("\033[2J\033[1;1H");
    wandp(menu.total);
    return;
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
        printf("Vui long nhap dung lua chon [Y/N]: ");
    }
}
// input string + ask question
void input(const char *question, char str[30])
{
    printf("%s: ", question);
    scanf("%[^\n]%*c", str);
    fflush(stdin);
}
void inputInt(const char *question, int *num)
{
    bool isValid = false;
    while (!isValid)
    {
        printf("%s: ", question);
        char tmp[MAX_STRING_LENGTH];
        fgets(tmp, MAX_STRING_LENGTH, stdin);
        fflush(stdin);
        bool isValidIntegerLength = strlen(tmp) < 10; // 2^32 - 1 has 10 digits
        bool isValidInteger = parseInt(tmp, num);
        isValid = isValidInteger && isValidIntegerLength;
        if (!isValid)
        {
            printf("Vui long nhap so nguyen!\n");
        }
    }
}

void inputPositiveInt(const char *question, int *num)
{
    inputInt(question, num);
    while (*num <= 0)
    {
        printf("Vui long nhap so nguyen duong!\n");
        inputInt(question, num);
    }
}