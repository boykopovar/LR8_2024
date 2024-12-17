#include <iostream>

#include"../../global_utils.h"
#include"../include/init_products.h"
#include"../include/utils_products.h"



int get_inputs_count()
{
    int count = 0;
    bool input_fail=false;

    while(true)
    {
        if(input_fail) std::cout<<"Некорректный ввод! Введите количество товаров "
                                  "(Enter - Приём до пустого наименования):\n";
        else std::cout<<"Введите количество товаров "
                        "(Enter - Приём до пустого наименования):\n";

        if(std::cin.get() == '\n') return -1;
        else std::cin.unget();
        std::cin>>count;
        if(check_stream(std::cin)) break;
        input_fail = true;
    }
    return count;
}

int input_product_count(int def)
{
    int input_count = -1;
    bool input_count_fail = false;
    while(input_count <0)
    {
        if(input_count_fail)std::cout<<"Повторите попытку. Общее кол-во единиц товара:\n";
        else std::cout<<"Общее кол-во единиц товара:\n";

        if(std::cin.get() == '\n') return def;
        else std::cin.unget();

        std::cin >> input_count;
        if(!check_stream(std::cin))
        {
            input_count = -1;
            input_count_fail = true;
            continue;
        }
    }
    return input_count;
}

int input_product_bad_count(int def)
{
    int input_bad_count = -1;
    bool input_bad_count_fail = false;
    while(input_bad_count <0)
    {
        if(input_bad_count_fail)std::cout<<"Повторите попытку. Кол-во испорченных единиц товара:\n";
        else std::cout<<"Кол-во испорченных единиц товара:\n";

        if(std::cin.get() == '\n') return def;
        else std::cin.unget();

        std::cin >> input_bad_count;
        if(!check_stream(std::cin))
        {
            input_bad_count = -1;
            input_bad_count_fail = true;
            continue;
        }
    }
    return input_bad_count;
}

double input_product_cost(double def)
{
    double input_cost = -1;
    bool input_cost_fail = false;
    while(input_cost<0)
    {
        if(input_cost_fail)std::cout<<"Повторите попытку. Цена товара:\n";
        else std::cout<<"Цена товара:\n";

        if(std::cin.get() == '\n') return def;
        else std::cin.unget();

        std::cin >> input_cost;
        if(!check_stream())
        {
            input_cost = -1;
            input_cost_fail = true;
            continue;
        }
    }
    return input_cost;
}

std::string input_unique_name(product* tickets, int except_unique_index)
{
    while(true)
    {
        std::cout << "Наименование товара:\n";
        std::string input_name;
        std::getline(std::cin, input_name);
        if(is_name_unique(input_name, tickets, except_unique_index))
        {
            return input_name;
        }
        else std::cout<<"Ошибка! Элемент с таким именем уже сущесвует!\n";
    }
}

std::string input_product_date(const std::string& def)
{
    std::cout<<"Дата поступления:\n";
    std::string input_date;
    std::getline(std::cin, input_date);
    if (input_date.empty())return def;
    return input_date;
}

