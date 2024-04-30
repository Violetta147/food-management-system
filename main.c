#include <stdio.h>
#include <string.h>
#include "structs/dish.h"
#include "structs/order.h"
#include "file-handler/file-handler.h"
#include "customer.h"

int main(void)
{
// {
    Menu menu = readMenu("menu.txt");
    printMenu();
    OrderItem orderitem;
    orderDish(menu, &orderitem);
}