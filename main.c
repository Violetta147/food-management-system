#include <stdio.h>
#include <string.h>
#include "structs/dish.h"
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "error-handler/error-handler.h"
#include "customer.h"
#include "billcalculate.h"

int main(void)
{
    Menu menu = readMenu("menu.txt");
    printMenu();
    OrderItem orderitem;
    orderDish(menu, &orderitem);
    Order order;
    order.total = 1;
    order.items[0] = orderitem;
    calculateBill(order);
    yawm();
    // int a,j,i;
    // for(i = 0; ; i++)
    // {
    //     for(int j = 0; j < 100000; j++)
    //     a = j;
    //     system("color 02");
    //     printf("\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c", i+1,i+2,i+3,i+4,i+5,i+6,i+7,i+8,i+9,i+10);
    //         system("color 04");
    //             printf("\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c", i+1,i+2,i+3,i+4,i+5,i+6,i+7,i+8,i+9,i+10);
    //                     system("color 06");
    //                     printf("\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c", i+1,i+2,i+3,i+4,i+5,i+6,i+7,i+8,i+9,i+10);                                printf("\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c", i+1,i+2,i+3,i+4,i+5,i+6,i+7,i+8,i+9,i+10);
}