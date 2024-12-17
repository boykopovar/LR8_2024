#include <iostream>
#include "global_utils.h"
#include "./Task_2/include/task_2.h"


int main()
{
    std::cout<<"--------------------------------------------------------\n";
    std::cout<<"| Выполнил   Вариант   LR                              |\n";
    std::cout<<"| Бойко А.О. 2         Лабораторная работа номер 8     |\n";
    std::cout<<"--------------------------------------------------------\n\n";

    while(true)
    {
        int choice=0;
        std::cout<<"\nМеню\n1 - Работа с продуктами\n2 - Работа с квитанциями\n"
                   "0 - Выход\n";
        std::cin>>choice;
        if(!check_stream()){break;}
        switch(choice)
        {
            case 1: task1(); break;
            case 2: task2(); break;
            default: return 0;
        }
    }
    return 0;
}