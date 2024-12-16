#pragma once

typedef struct ticket
{
    std::string group;
    std::string mark;
    std::string date;
    union
    {
        bool b;
        int i;
    } status;
    int bad_count;
} ticket;

void task2();