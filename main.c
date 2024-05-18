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
    while (true)
    {
        printf("Nhap X de thoat khoi chuong trinh.\n");
        enter();
        if (myToUpper(mode) == 'A')
        {
            printf("De vao che do Admin vui long nhap mat khau.\n");
            conf();
            menu = readMenu("menu.txt");
            printMenu(menu);
            do
            {
                Ans();
                if (myToUpper(action) == 'D')
                {
                    Erase();
                }
                if (myToUpper(action) == 'A')
                {
                    appendMenu();
                }
                if (myToUpper(action) == 'C')
                {
                    custom(menu);
                }
                if (myToUpper(action) == 'S')
                {   
                    int revenue = 0;
                    calculate_popularity_revenue(&revenue);
                }
            } while (true);
        }
        else if (myToUpper(mode) == 'C') // customer mode
        {
            Customer();
            return 0;
        }
    }
}