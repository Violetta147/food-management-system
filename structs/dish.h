#pragma once

#include "../constant.h"

typedef struct Dish
{
    int PIN;
    char name[MAX];
    float price;
} Dish;

typedef struct Menu
{
    Dish dishes[MAX];
    int total;
} Menu;

Menu menu;
