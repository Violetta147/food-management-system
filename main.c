#include <stdio.h>
#include <string.h>
#include "structs/dish.h"
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "error-handler/error-handler.h"
#include "customer.h"
#include "billcalculate.h"
#include "menufunction.h"

int main()
{
    Order order;
    bool isLoop = true;
    char bancomuontieptuc[30] = "Ban co muon tiep tuc khong?";
    while(isLoop)
    {
        float sum;
        float sale;
        float total;

        makeOrder(&order);
        if(order.items[0].dish.PIN == 0)
        {
            
            isLoop = ynQuestion(bancomuontieptuc);
            continue;
        }
        calculateBill(&order, &sum, &sale, &total);
        printf("Tong tien: %.0f\n", sum);
        printf("Khuyen mai: %.0f\n", sale);
        printf("Thanh tien: %.0f\n", total);
        isLoop = ynQuestion(bancomuontieptuc);
    }

    isLoop = true;
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
}