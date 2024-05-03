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
    
    float sum;
    float sale;
    float total;

    Order order = OrderManyDishes();
    calculateBill(&order, &sum, &sale, &total);
    printf("Tong tien: %.0f\n", sum);
    printf("Khuyen mai: %.0f\n", sale);
    printf("Thanh tien: %.0f\n", total);
    // //write order to file
    // writeOrder("order.txt", order, sum, sale, total);
}