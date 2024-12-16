#pragma once

typedef struct product
{
    std::string name;
    std::string date;
    union
    {
        double d;
        int i;
    } cost;
    int count;
    int bad_count;
} product;

void task1();