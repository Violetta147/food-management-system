#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "structs/order.h"
#include "constant.h"

#define INVOICE_FILE_PATH "/data/invoices/"
#define MAX_LENGTH 256

float payment(float );

float calculateBill(Order* order)
{
    float sum = 0;
    float sale = 0;
    float total = 0;

    char tmp[1000]; // nhap choice

    for (int i = 0; i < order.total; i++)
    {
        sum += order.items[i].dish.price * order.items[i].quantity;
    }

    if (sum >= SALE)
    {
        sale = sum * 25 / 100;     // 25% discount
        total = floor(sum - sale); // thanh tien = tong tien - khuyen mai
    }

    printf("__________________________________________________________________________________________  \n");
    printf("\nMa hoa don: %03d\n", countOrder);
    printf("%17s %17s %17s %17s %17s\n", "Ma so", "Mon an", "Don gia", "So luong", "Thanh tien");

    for (int i = 0; i < order.total; i++)
    {
        printf("%17d %17s %17.0f %17d %17.0f\n", order.items[i].dish.PIN, order.items[i].dish.name,
               order.items[i].dish.price, order.items[i].quantity, order.items[i].dish.price * order.items[i].quantity);
    }   
        printf("\033[0;33m");
        printf("%51s%38.0f\n", "Tong:", sum);
        printf("%57s%32.0f\n", "Khuyen mai:", sale);
        printf("%57s%32.0f\n", "Thanh tien:", total);
        printf("\033[m");

    while (true)
    {
        printf("\033[1;34m");
        printf("Ban co muon thanh toan ngay khong? [Y/N]:");
        printf("\033[m");
        clstd();
        fgets(tmp, 1000, stdin);
        tmp[strlen(tmp) - 1] = '\0';
        if (strcasecmp(tmp, "Y") == 0)
        {
            payment(total);
            printf("__________________________________");
            printf("\nBan da thanh toan don hang ma so %d\n", countOrder);
            order->status = ORDER_PAID;
            countOrder++;
            addOrder(*order);
            printf("Cam on quy khach da su dung dich vu cua chung toi.\n");
            break;
        }
        else if (strcasecmp(tmp, "N") == 0)
        {
            printf("Don hang cua quy khach da duoc luu lai.\n");
            order->status = ORDER_PROCESSING;
            addOrder(*order);
            countOrder++;
            break;
        }
        else
        {
            printf("Vui long nhap dung lua chon [Y/N]\n");
        }
}
}
float payment(float total)
{
    float change = 0;  // tien thua thoi lai
    float owe = total; // tien quy khach no, owe is temp
    float paid = 0;    // tien quy khach tra

    printf("Vui long nhap so tien quy khach can tra: ");
    
    do
    {
        scanf("%f", &paid);
        if (paid >= owe)
        {
            change = floor(paid - owe);
            printf("Tien thoi cua quy khach la: %.0f\n", change);
            break;
        }
        else
        {
            owe -= paid;
            printf("Quy khach tra tien con thieu, vui long tra them %.0f: ", owe);
        }
    } while (owe > 0);

    return change;
}
