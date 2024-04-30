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
    char *status; 
} Order;
