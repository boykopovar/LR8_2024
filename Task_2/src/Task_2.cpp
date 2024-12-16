#include <iostream>

#include "../../global_utils.h"
#include "../include/tools_tickets.h"
#include "../include/file_utils.h"

void task2()
{
    std::cout<<"--------------------------------------------------------\n";
    std::cout<<"| Выполнил   Вариант   Суть                            |\n";
    std::cout<<"| Бойко А.О. 2         Работа с  квитанциями о ремонте |\n";
    std::cout<<"--------------------------------------------------------\n\n";
    ticket* tickets = nullptr;
    tickets = load_tickets_from_file();

    while(true)
    {
        int choice=0;
        if(tickets==nullptr)
        {
            std::cout<<"\nЧтобы продолжить, внесите информацию о квитанциях:\n";
            add_tickets(tickets);
            continue;
        }
        else
        {
            std::cout<<"\nМеню Задание 2\n"
                       "1 - Добавить квитанцию\n"
                       "2 - Просмотр квитанций\n"
                       "3 - Поиск по группе\n"
                       "4 - Редактирование\n"
                       "5 - Сортировать по убыванию кол-ва повреждений\n"
                       "0 - Выход меню LR8\n\n";
        }
        std::cin>>choice;
        if(!check_stream()){break;}
        switch(choice)
        {
            case 1: add_tickets(tickets); break;
            case 2: print_tickets(tickets); break;
            case 3: search_elements_by_group(tickets); break;
            case 4: edit_element(tickets); break;
            case 5: sort_by_count(tickets); break;
            default: return;
        }
    }
    delete[] tickets;
}