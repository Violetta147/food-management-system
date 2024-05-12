#pragma once

#include <stdio.h>
#include <string.h>
#include "structs/dish.h"
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "error-handler/error-handler.h"
#include "constant.h"
#include "customer.h"

//function prototypes
void printMenu(Menu menu);
void erase(Menu menu);
void delete(Menu menu, int *del, int count);
void wandp(int total);
void reset(Menu menu);
void extend(Menu menu);
void More(Menu menu, Dish* add, int count);

// 1. DELETE
/*----------------------------------------------------------------------*/
void erase(Menu menu)                                                    
{                                                                               
    int count = 0;                                                          
    erase1:                                                              
    printf("How many dishes do you want to erase: ");                    
    scanf("%d", &count);                                                 
    clstd();                                                             
    while(count < 0 || count > menu.total)                               
    {                                                                    
        printf("The amount limit is around 0 and %d\n", menu.total);     
        goto erase1;                                                     
    }                                                                    
    int *del = (int*)malloc(count * sizeof(int));                             
    if (count != 0)                                                      
    {                                                                    
        for(int i = 0; i < count; i++)                                   
        {                                                                
           do                                                            
           {                                                             
            printf("Food %d PIN: ", i + 1);                              
            scanf("%d", &del[i]);                                        
            clstd();                                                     
        }while(isExist(menu, del[i]) == false ||                         
                isAlreadyPIN(del, i) == true || del[i] == 0);            
    }                                                                    
    arg();                                                               
    if(toupper(ans) == 'N')                                              
    {                                                                    
        printMenu(menu);                                                 
        free(del);                                                       
    }                                                                    
    else if (toupper(ans) == 'Y')                                        
    {                                                                    
        delete(menu,del,count);                                          
        printf("\033[2J\033[1;1H"); //clear screen                       
        wandp(menu.total);                                               
        free(del);                                                       
    }                                                                    
    else{                                                                
        printf("No change has been made.\n");                            
        free(del);                                                       
        yawm();                                                          
        exit(5); //5 is the exit code for no change                      
    }                                                                    
}                                                                        
    else                                                                 
    {                                                                    
        printf("No change has been made.\n");
        free(del);
        yawm();
        printMenu(menu);
    }
}

void delete(Menu menu, int *del, int count)
{
    for(int i = 0; i < count; i++)
    {
        for(int j = 0; j < menu.total; j++)
        {
            if(menu.dishes[j].PIN == del[i])
            {
                for(int k = j; k < menu.total - 1; k++)
                {
                    menu.dishes[k] = menu.dishes[k + 1];
                }
                menu.total--;
                break;
            }
        }
    }
}
void wandp(int total)
{
    writeMenu("menu.txt", menu);
    printf("Changes applied successfully.\n");
    reset(menu);
    readMenu("menu.txt");
    printMenu(menu);
}

void reset(Menu menu)
{
    int TempPIN[MAX];
    int count = 0;
    for(int i = 0; i < menu.total; i++)
    {
        TempPIN[i] = menu.dishes[i].PIN;
        count++;
    }
    delete(menu, TempPIN, count);
    return;
}
/*----------------------------------------------------------------------*/
// 2. ADD
/*----------------------------------------------------------------------*/
void extend(Menu menu)
{
    int count;
    printf("How many dishes do you wanna add: ");
    scanf("%d", &count);
    clstd();
    while(count < 0 || count >= MAX - menu.total)
    {
        printf("Your choice can only be between 0 and %d\n", MAX - menu.total);
        printf("How many dishes you wanna add: ");
        scanf("%d", &count);
        clstd();
    }
    if(count != 0)
    {
        Dish* add = (Dish*)malloc(count * sizeof(Dish));
        for(int i = 0; i < count; i++)
        {
            printf("Food %d name: ", i+1);
            while(scanf("%s", add[i].name) != 1 || isSameName(menu, add[i].name) == true || isNoDif(add, i) == true)
            {
                clstd();
                printf("The name is already taken or invalid.\n");
                printf("Food %d name: ", i+1);
            }
                clstd();
                printf("Food %d price: ", i+1);
            while(scanf("%f", &add[i].price) != 1 || add[i].price <= 0)
            {
                clstd();
                printf("Invalid price.\n");
                printf("Food %d price: ", i+1);
            }
                clstd();
                printf("Food %d PIN: ", i+1);
                while(scanf("%f", &add[i].PIN) != 1 || isRepeatPIN(menu, add[i].PIN) == true || isSamePIN(add, i) == true)
                {
                    clstd();
                    printf("The PIN is already taken or invalid. Please try another one.\n");
                    printf("Food %d PIN: ", i+1);
                }
                clstd();
        }
            arg();
            if(toupper(ans) == 'N')
            {
                printMenu(menu);
                free(add);
                return;
            }
            else if(toupper(ans) == 'Y')
            {   
                //add to menu
                More(menu, add, count);
                printf("\033[2J\033[1;1H");
                wandp(menu.total);
                free(add);
                return;
            }
            else
            {
                printf("No change has been made.\n");
                free(add);
                yawm();
                exit(5);
            }
    }
    else
    {
        printf("No change has been made.\n");
        yawm();
        printMenu(menu);
    }
}
void More(Menu menu, Dish* add, int count)
{
    if(menu.total + count > MAX)
    {
        printf("CANNOT ADD MORE DISHES. MENU FULL!\n");
        return;
    }
    for(int i = 0; i < count; i++)
    {
       if(strlen(add[i].name) >= MAX)
       {
              printf("The name is too long.\n");
              return;
       }
    }
    for(int i = 0; i < count; i++)
    {
        menu.dishes[menu.total + i] = add[i]; 
        //why menu.total +i ? because we want to add the new dish
        //to the end of the menu
    }
    menu.total += count;
    return;
}
/*----------------------------------------------------------------------*/
// 3. CHANGE
/*----------------------------------------------------------------------*/
void custom(Menu menu)
{   
    bool parsed_successfully = true;
    int FoodPIN;
    do
    {  
        printf("Enter the PIN of the dish you want to change: ");
        char buffer[BUFFER_SIZE];
        fgets(buffer, BUFFER_SIZE, stdin);
        parsed_successfully = parseInt(buffer, &FoodPIN);
        if(!parsed_successfully)
        {
            printf("Invalid PIN or Repeated.\n");
        }
    }while(!parsed_successfully || isRepeatPIN(menu, FoodPIN) == false);   
}

int ynQuestion(const char *question)
{   
    printf("%s [Y/N]: ", question);
    while (true)
    {
        char tmp[1000];
        scanf("%s", tmp);
        fflush(stdin);
        if (isYes(tmp)) return true;
        if (isNo(tmp)) return false;
        printf("Vui long nhap dung lua chon [Y/N]: ");
    }
}
//input string + ask question
void input(const char *question, char *str)
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
        printf("num: %d\n", *num);
        printf("isValidInteger: %d\n", isValidInteger);
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