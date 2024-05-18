#pragma once

#include "../constant.h"

typedef struct Dish
{
    int PIN;
    char name[MAX];
    int price;
} Dish;

typedef struct Menu
{
    Dish dishes[MAX];
    int total;
} Menu;

Menu menu;

typedef struct Popularity
{
    Dish Dish;
    int count;
} Popularity;




