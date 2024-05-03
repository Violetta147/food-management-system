#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h> 
#include "strings.h"
#include "../structs/dish.h"

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

