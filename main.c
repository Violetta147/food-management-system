#include <stdio.h>
#include <string.h>
#include "structs/dish.h"
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "error-handler/error-handler.h"
#include "customer.h"
#include "billcalculate.h"
#include "menufunction.h"
#include "admin.h"

int main()
{    
    // char string[100] = "\t - 123";
    // int number;
    // bool isValid = parseInt(string, &number);
    // printf("Is valid: %d\n", isValid);
    // printf("Number: %d\n", number);

    Order order;
    bool isLoop = true;
    float revenue = 0;
    while(isLoop)
    {
        float sum;
        float sale;
        float total;
        makeOrder(&order);
        int iszero;
        for(int i = 0; i < 10; i++)
        {
            if(order.items[i].dish.PIN == 0)
            {
                iszero = i;
                break;
            }
        }
        if(order.items[iszero].dish.PIN == 0)
        {
            isLoop = ynQuestion("Ban co muon tiep tuc khong?");
        }
        for(int i = 0; i < 10; i++)
        {
            if(order.items[i].dish.PIN != 0)
            {
                calculateBill(&order, &sum, &sale, &total);
                printf("Tong tien: %.0f\n", sum);
                printf("Khuyen mai: %.0f\n", sale);
                printf("Thanh tien: %.0f\n", total);
                break;
                
            }
        }   
            isLoop = ynQuestion("Ban co muon tiep tuc khong?");
    }

    isLoop = true;
    calculate_popularity_revenue(&revenue);
    while(isLoop)
    {
       bool ContinuePaying = UnpaidBill();
       if(ContinuePaying)
       {
           printf("Tiep tuc thanh toan\n");
       }
       else
       {
           printf("Cam on quy khach da su dung dich vu cua chung toi\n");
       }
       isLoop = ynQuestion("Ban co muon tiep tuc khong?");
    }
    return 0;
}