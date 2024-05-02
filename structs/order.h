#pragma once 
#include "dish.h"
#include "../constant.h"

// An orderitem
typedef struct OrderItem //old Pick
{
    Dish dish;
    int quantity;
} OrderItem;

#define ORDER_PROCESSING "Processing"
#define ORDER_PAID "Paid"
#define ORDER_CANCELLED "Cancelled"

// an Order
typedef struct Order 
{
    OrderItem items[MAX];
    int total;
    char *status; // ORDER_PROCESSING, ORDER_PAID, ORDER_CANCELLED
} Order;

Order orders[MAX_ORDERS]; // array of orders

// Function prototypes
void addOrder(Order order);
void printOrderStatus(int orderIndex);

// Function definitions
void addOrder(Order order)
{
    if(numOrder < MAX_ORDERS)
    {
        orders[numOrder] = order;
        numOrder++;
    }
    else
    {
        printf("Da vuot qua so don hang toi da\n");
    }
}
void printOrderStatus(int orderIndex)
{
    if(orderIndex < 0 || orderIndex >= numOrders)
    {
        printf("Khong tim thay don hang.\n");
    }
    else{
        printf("Trang thai don hang: %s\n", orders[orderIndex].status);
    }
}
