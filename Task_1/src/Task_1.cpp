#include <iostream>

#include "../../global_utils.h"
#include "../include/tools_products.h"
#include "../include/file_utils.h"

void task1()
{
    std::cout<<"--------------------------------------------------------\n";
    std::cout<<"| Выполнил   Вариант   Суть                              |\n";
    std::cout<<"| Бойко А.О. 2         Работа со списком товаров       |\n";
    std::cout<<"--------------------------------------------------------\n\n";
    product* products = nullptr;
    products = load_from_file();

    while(true)
    {
        int choice=0;
        if(products==nullptr)
        {
            std::cout<<"\nЧтобы продолжить, заполните информацию о товарах:\n";
            add_products(products);
            continue;
        }
        else
        {
            std::cout<<"\nМеню Задание 1\n"
                       "1 - Добавить продукт\n"
                       "2 - Просмотр содержимого\n"
                       "3 - Поиск по наименованию\n"
                       "4 - Редактирование\n"
                       "5 - Сортировать по убыванию кол-ва\n"
                       "6 - Вывести товары, стоимость которых превышает 100.341\n\n"
                       "0 - Выход меню LR8\n\n";
        }
        std::cin>>choice;
        if(!check_stream()){break;}
        switch(choice)
        {
            case 1: add_products(products); break;
            case 2: print_products(products); break;
            case 3: search_elements_by_name(products); break;
            case 4: edit_element(products); break;
            case 5: sort_by_count(products); break;
            case 6: print_by_min_cost(products, 101.341); break;
            default: return;
        }
    }
    del_products(products);
}