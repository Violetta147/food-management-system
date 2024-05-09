#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h> 
#include "strings.h"
#include "../structs/dish.h"
#define BUFFER_SIZE 4096

//function prototypes
void clstd();
void yawm();
bool isExist(Menu menu, int PIN);
bool isAlreadyPIN(int array[], int i);
bool isRepeatPIN(Menu menu, int PIN);
bool isSamePIN(Dish dishes[], int i);
bool isSameName(Menu menu, char* name);
bool isNoDif(Dish dishes[], int i);
bool isYes(char* c);
bool isNo(char* c);
void arg();
bool isRepeatOrderID(Order orders[100], int orderID);
bool isNotExistOrderID(Order orders[100], int orderID);
bool isValidOrderID(int orderID);
bool parse_int(char *string, int *integer);
char* orderIDConvert(int orderID);
bool isEOF(FILE* file);
bool isLeapYear(int year);
bool isValidDate(int date);
int dateToInt(char* date);
int dayToInt(char* date);
int monthToInt(char* date);
int yearToInt(char* date);

// clear input buffer
void clstd()
{   
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    return;
}
// clear the terminal screen after a delay of 3 seconds and ANSI escape 
void yawm()
{   
    system("color A");
    printf("Vui long doi");
    int i,j,a;
    for(int i = 0; i <= 6; i++)
    {
        for(j = 0; j < 100000000; j++) // second loop only excute a = j not printf
       { a = j;}
        system("color A");
        printf(".");
    }
    printf("\033[2J\033[1;1H");
}
// check if a PIN exists in menu
bool isExist(Menu menu, int PIN)
{
    for(int i = 0; i < menu.total; i++)
    {
        if(menu.dishes[i].PIN == PIN) return true;
    }
    printf("Khong mon nao co ma PIN %d", PIN);
    return false;
}
// check if a PIN is already chosen for deletion when delete "many" at the same time
// 1st argument = del[count]
// if delete "many" at "one" time then use this
bool isAlreadyPIN(int array[], int i)
{
    for(int j = 0; j < i; j++)
    {
        if(array[j] == array[i])
        {
            printf("mon an voi ma PIN %d da duoc chon de xoa tu truoc.\n", array[i]);
            return true;
        }
    }
    return false;
}
// check if the new PIN is unique
// compare with menu
bool isRepeatPIN(Menu menu, int PIN)
{
    for(int i = 0; i < menu.total; i++)
    {
        if(menu.dishes[i].PIN == PIN)
        {
            return true;
        }
    }
    return false;
}
// check if new PINS in "adding multiple dishes" are unique
bool isSamePIN(Dish dishes[], int i)
{
    for(int j = 0; j < i; j++)
    {
        if(dishes[j].PIN == dishes[i].PIN)
        return true;
    }
    return false;
}
// check for "duplicate" nameS in the dish array (menu)
bool isSameName(Menu menu, char* name)
{
    for(int i = 0; i < menu.total; i++)
    {
        if(strcasecmp(menu.dishes[i].name, name) == 0) return true;
    }
    return false;
}
// check if " new names" are "same" with "added names"
bool isNoDif(Dish dishes[], int i)
{
    for(int j = 0; j < i; j++)
    {
        if(strcasecmp(dishes[j].name, dishes[i].name) == 0) return true;
    }
    return false;
}
//check if user type in yes YES Y y 
bool isYes(char* c)
{
    for(int i = 0; c[i] != '\0'; i++)
    {
        c[i] =tolower(c[i]);
    }
    return (strcmp(c, "yes") == 0 || strcmp(c, "y") == 0);
}
// check if user type in no NO N n
bool isNo(char* c)
{
    for(int i = 0; c[i] != '\0'; i++)
    {
        c[i] =tolower(c[i]);
    }
    return (strcmp(c, "no") == 0 || strcmp(c, "n") == 0);
}
// ask user to confirm save changes
void arg()
{   
    do
    {
        printf("Ban co muon luu thay doi khong? [Y/N]: ");
        scanf("%c", &ans);
        clstd();
    } 
    while(toupper(ans) != 'N' && toupper(ans) != 'Y' && toupper(ans) != 'X');
}
/*----------------------------------------------------------------------------*/
/*                                 ORDER ID                                   */
//function to prevent user from entering repeated orderID
bool isRepeatOrderID(Order orders[100], int orderID)
{
    for(int i = 0; i < 100  ; i++)
    {
        if(orders[i].orderID == orderID)
        {
            printf("Ma don hang %d da ton tai. Xin moi nhap lai\n", orderID);
            return true;
        }
    }
    return false;
}
bool isNotExistOrderID(Order orders[100], int orderID)
{
    for(int i = 0; i < 100; i++)
    {
        if(orders[i].orderID == orderID)
        {
            return false;
        }
    }
    printf("Khong tim thay ma don hang %d\n", orderID);
    return true;
}
//function to check if orderID is valid
bool parse_int(char *string, int *integer)
{   
    if(integer == NULL)
    {
        printf("Integer pointer is NULL\n");
    }
    if(string == NULL)
    {
        printf("String is NULL.\n");
    }
    int i = 0;
    while(isspace(string[i])) i++;
    
    int length = strlen(string);
    
    if(length == i)
    {   
        return false;
    }
    char integer_buffer[BUFFER_SIZE];

    int integer_chars = 0;

    if(string[i] == '-')
    {   
        integer_buffer[integer_chars] = '-';
        integer_chars++;
        i++;
    }
    if(!isdigit(string[i])) 
    {   
        return false;
    }
    while(i < length && !isspace(string[i]))
    {
        if(!isdigit(string[i]))
        {   
            return false;
        }
        integer_buffer[integer_chars] = string[i];
        integer_chars++;
        i++;
    }
    integer_buffer[integer_chars] = '\0';
    while(isspace(string[i])) i++;

    if(string[i] != '\0') 
    {
        return false;
    }
    *integer = atoi(integer_buffer);
    if(*integer == 0 || *integer > 9999) 
    {   
        return false;
    }
    return true;
}
//function to check if integer is negative or not
bool isValidOrderID(int orderID)
{
    if(orderID < 0 || orderID == 0 || orderID > 9999)
    {
        printf("Ma don hang khong the am, bang 0 hoac lon hon 9999\n");
        return false;
    }
    return true;
}
//function to check for the end of file
bool isEOF(FILE* file)
{
    if(feof(file))
    {
        printf("End of file\n");
        return true;
    }
    return false;
}

/*----------------------------------------------------*/
/*                   DATE CHECK                       */
bool isLeapYear(int year)
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    //explain: if year is divisible by 400 or divisible by 4 but not divisible by 100
    //then it is a leap year
}
bool isValidDate(int date)
{   
    //extract day, month, year from date format yyyymmdd
    int day = date % 100;
    int month = (date / 100) % 100;
    int year = date / 10000;
    if(year < 2021 || year > 9999)
    {
        return false;
    }
    if(month < 1 || month > 12)
    {
        return false;
    }
    if(day < 1 || day > 31)
    {
        return false;
    }
    if(month == 2)
    {
        if(isLeapYear(year) && day > 29)
        {
            return false;
        }
        if(!isLeapYear(year) && day > 28)
        {
            return false;
        }
    }
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        {
            return false;
        }
    return true;
}
//function to take 08-05-2024 as the start date , check if newly created day cannot be earlier than the start date
bool isDateEarlier(char* date)
{
    int timequantity = 0;
    timequantity += dateToInt(date);
    if(timequantity < 20210508)
    {
        printf("Ngay khong the nho hon ngay hien tai.\n");
        return true;
    }
    if(timequantity - )
}
//function to take the value of current day 
int getCurrentDate()
{
    
}
//function to check if a date exists in the file
//date is in the format dd-mm-yyyy and it is a string
bool isDateExist(char* date1, char* date2)
{   
    int ExistDate = 0;
    int orderFilesTotal = 0;
    char listOrderFiles[MAX][MAX];
    getListOrders(listOrderFiles, &orderFilesTotal);
    for(int i = 0; i < orderFilesTotal; i++)
    {
        listOrderFiles[i][strlen(listOrderFiles[i]) - 4] = '\0';
    }

    //check if 2 dates exist in listOrderFiles
    for(int i = 0; i < orderFilesTotal; i++)
    {
        if(strcmp(date1,listOrderFiles[i]) == 0)
        {
            ExistDate = 1;
        }
    }
    for(int i = 0; i < orderFilesTotal; i++)
    {
        if(strcmp(date2,listOrderFiles[i]) == 0)
        {
            ExistDate = 1;
        }
    }
    if(ExistDate == 1)
    {   
        printf("Date exists.\n");
        return true;
    }
    else if(ExistDate == 0)
    {
        printf("Date does not exist.\n");
        return false;
    }
    return false;
}

//create atoi function for date
int dateToInt(char* date)
{
    int day, month, year;
    //extract day, month, year from date format dd-mm-yyyy
    sscanf(date, "%d-%d-%d", &day, &month, &year);
    return year * 10000 + month * 100 + day;
    //why year is multiplied by 10000, month by 100 and day by 1
    //because we want to convert date to integer format yyyymmdd
}
//create atoi function for day
int dayToInt(char* date)
{
    int day, month, year;
    //extract day, month, year from date format dd-mm-yyyy
    sscanf(date, "%d-%d-%d", &day, &month, &year);
    return day;
}
//create atoi function for month
int monthToInt(char* date)
{
    int day, month, year;
    sscanf(date, "%d-%d-%d", &day, &month, &year);
    return month;
}   
//create atoi function for year
int yearToInt(char* date)
{
    int day, month, year;
    sscanf(date, "%d-%d-%d", &day, &month, &year);
    return year;
}