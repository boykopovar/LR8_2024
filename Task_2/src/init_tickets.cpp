#include <iostream>

#include"../../global_utils.h"
#include"../include/init_tickets.h"


int get_tickets_count()
{
    int count = 0;
    bool input_fail=false;

    while(true)
    {
        if(input_fail) std::cout<<"Некорректный ввод! Введите количество квитанций "
                                  "(Enter - Приём до пустой группы):\n";
        else std::cout<<"Введите количество квитанций "
                        "(Enter - Приём до пустой группы):\n";

        if(std::cin.get() == '\n') return -1;
        else std::cin.unget();
        std::cin>>count;
        if(check_stream(std::cin)) break;
        input_fail = true;
    }
    return count;
}

int input_status(bool def)
{
    bool status = false;
    bool input_count_fail = false;
    while(true)
    {
        if(input_count_fail)std::cout<<"Повторите попытку. Готов ли заказ? [1 - Да | 2 - Нет]:\n";
        else std::cout<<"Готов ли заказ? [1 - Да | 0 - Нет]:\n";

        if(std::cin.get() == '\n') return def;
        else std::cin.unget();

        std::cin >> status;
        if(!check_stream(std::cin))
        {
            input_count_fail = true;
            continue;
        }
        break;
    }
    return status;
}

int input_ticket_bad_count(int def)
{
    int input_bad_count = -1;
    bool input_bad_count_fail = false;
    while(input_bad_count <0)
    {
        if(input_bad_count_fail)std::cout<<"Повторите попытку. Кол-во повреждений:\n";
        else std::cout<<"Кол-во повреждений:\n";

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

std::string input_mark(const std::string& def)
{
    std::cout << "Марка прибора:\n";
    std::string input_mark;

    if(std::cin.peek() == '\n')return def;

    std::getline(std::cin, input_mark);
    return input_mark;
}

std::string input_group()
{
    std::cout << "Группа прибора:\n";
    std::string input_name;
    std::getline(std::cin, input_name);
    return input_name;
}

std::string input_ticket_date(const std::string& def)
{
    std::cout<<"Дата приёма в ремонт:\n";
    std::string input_date;
    std::getline(std::cin, input_date);
    if (input_date.empty())return def;
    return input_date;
}

