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
    sortDateIndex();
    while (true)
    {
        printf("Enter 'X' to exit program.\n");
        enter();
        if (myToUpper(mode) == 'A')
        {
            printf("To enter ADMIN mode please input PASSWORD.\n");
            conf();
            readMenu("menu.txt");
            printMenu();
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