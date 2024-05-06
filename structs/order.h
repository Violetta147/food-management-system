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
    char date[12]; // dd-mm-yyyy
    int orderID;
    OrderItem items[MAX_ORDER_ITEMS];
    int total; 
    char* status; 
} Order;
