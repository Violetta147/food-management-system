#pragma once

#include "../constant.h"

typedef struct Dish
{
    int PIN;
    char name[101];
    int Price;
    int Status;
    char Unit[10];
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




