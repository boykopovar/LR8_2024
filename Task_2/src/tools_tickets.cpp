#include<iostream>

#include"../../global_utils.h"
#include"../include/init_tickets.h"
#include"../include/utils_tickets.h"
#include"../include/tools_tickets.h"
#include"../include/file_utils.h"

void add_tickets(ticket*& tickets)
{
    bool inf_get = false;
    int start_index = 0;

    int tech_count = get_tickets_count(), count=1;
    if(tech_count ==0)return;
    if(tech_count ==-1) inf_get = true;
    else count = tech_count;

    if(tickets == nullptr)
    {
        tickets = new ticket[count + 1];
        tickets[count].group[0]='\0';
    }

    else
    {
        while(tickets[start_index].group[0]!='\0')
        {
            ++start_index;
        }
        count+=start_index;
    }
    std::cout<<"-----------------------------------------------------------------------------\n"
               "|             Поле              | Значение по умолчанию (при нажатии enter) |\n"
               "-----------------------------------------------------------------------------\n"
               "| Группа                        | *Пустой ввод завершит заполнение!*        |\n"
               "| Марка                         | -                                         |\n"
               "| Количество повреждений        | 0                                         |\n"
               "| Состояние готовности          | 0                                         |\n"
               "| Дата приёма в ремонт          | -                                         |\n"
               "|----------------------------------------------------------------------------\n";

    for(int i = start_index; i<count;++i)
    {
        if(tickets[i].group[0]=='\0')
        {
            longer_tickets(tickets, count);
        }
        std::cout<<"\nКвитанция "<<i+1<<'\n';

        std::string input_gr = input_group();
        if(input_gr.empty())
        {
            tickets[i].group[0]='\0';
            if(i==0)
            {

                longer_tickets(tickets, 3);
                tickets[0]= {"Телевизор", "Horizont", "12.12.2024", false, 3};
                tickets[1]= {"Радиоприемник", "Huawei", "10.12.2024", true,  0};
                tickets[2]= {"Антенна", "Apple", "11.12.2024", false, 1};
                save_tickets_to_file(tickets, start_index);
            }
            return;
        }
        tickets[i].group = input_gr;

        tickets[i].mark = input_mark();
        tickets[i].bad_count = input_ticket_bad_count();
        tickets[i].status.b = input_status();
        tickets[i].date = input_ticket_date();
        save_tickets_to_file(tickets, start_index);

        if(inf_get)++count;
    }
}

int print_tickets(const ticket* tickets, const std::string& filter_group)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int last_ticket_index = -1, filtered_count = 0;
    std::string lower_filter_name = string_to_lower(filter_group);

    if(tickets == nullptr || tickets[0].group[0]=='\0')
    {
        std::cout<<"Квитанции не добавлены!\n";
        return 0;
    }

    freopen(nullptr, "w", stdout);
    freopen(nullptr, "r", stdin);

    std::wcout<<'\n'<<std::left
              <<std::setw(8)<<L"№"
              <<std::setw(20)<<L"Группа"
              <<std::setw(18)<<L"Марка"
              <<std::setw(20)<<L"Повреждений"
              <<std::setw(15)<<L"Стутус"
              <<L"Дата\n"
              <<std::wstring(90,'-')<<'\n';

    for(int i =0;;++i)
    {
        if (tickets[i].group[0] == '\0')break;

        //индекс первого вхождения filter в string_to_lower(tickets[i].group)
        unsigned long entry_filter = string_to_lower(tickets[i].group).find(lower_filter_name);

        if(entry_filter!= std::string::npos)
        {
            if(entry_filter!= 0 && tickets[i].group[entry_filter-1]!= ' ')
            {
                entry_filter = std::string::npos;
            }
        }

        if(filter_group.empty() || entry_filter != std::string::npos)
        {
            std::wcout << std::left
                      << std::setw(8) << i + 1
                      << std::setw(20) << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(tickets[i].group)
                      << std::setw(18) << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(tickets[i].mark)
                      << std::setw(20) << tickets[i].bad_count
                      << std::setw(15) << tickets[i].status.b
                      << str_to_wstr(tickets[i].date) << '\n';
            filtered_count++;
            last_ticket_index=i;
        }
    }
    freopen(nullptr, "w", stdout);
    freopen(nullptr, "r", stdin);

    if(!filtered_count)std::cout<<"Нет приборов, удовлетворяющих условиям поиска!\n";
    return last_ticket_index;
}

void search_elements_by_group(const ticket* tickets)
{
    print_tickets(tickets);
    std::cout<<"\nВведите группу для поиска: ";
    std::string input_gr;

    std::getline(std::cin, input_gr);
    print_tickets(tickets, input_gr);
}

void edit_element(ticket* tickets)
{
    print_tickets(tickets);
    std::cout<<"\nВведите номер для редактирования: ";

    if(std::cin.get() == '\n') return;
    else std::cin.unget();

    int target_index = -1;
    std::cin>>target_index;

    if(!check_stream() || target_index<=0)
    {
        std::cout<<"Прибор не найден!\n";
        return;
    }
    --target_index;

    std::cout<<std::left<<
           "\n\n-----------------------------------------------------------------------------\n"
               "|             Поле              | Значение по умолчанию (при нажатии enter) |\n"
               "-----------------------------------------------------------------------------\n"
               "| Группа                        | *Удаление элемента*                       |\n"
               "| Марка                         | "<<std::setw(42)<<tickets[target_index].mark<<"|\n"
               "| Количество повреждений        | "<<std::setw(42)<<tickets[target_index].bad_count<<"|\n"
               "| Статус                        | "<<std::setw(42)<<tickets[target_index].status.b<<"|\n"
               "| Дата приема на ремонт         | "<<std::setw(42)<<tickets[target_index].date<<"|\n"
               "|----------------------------------------------------------------------------\n";

    std::cout<<"\nПрибор "<<target_index+1<<" ("<<tickets[target_index].group<<") "
               "[Enter - удалить элемент]\n";

    std::string new_group = input_group();

    if(new_group.empty())
    {
        //удаление элемента
        int count = target_index+1;
        for(int i = target_index+1;tickets[i].group[0]!='\0';++i)
        {
            ++count;
        }
        if(count -1!=target_index)
        {
            copy_one_ticket(tickets[count-1], tickets[target_index]);
        }
        tickets[count-1].group="";
        tickets[count-1].group[0]='\0';

        save_tickets_to_file(tickets, 0);
    }
    else
    {
        tickets[target_index].group = new_group;

        tickets[target_index].mark = input_mark(tickets[target_index].mark);
        tickets[target_index].bad_count = input_ticket_bad_count(tickets[target_index].bad_count);
        tickets[target_index].status.b = input_status(tickets[target_index].status.b);
        tickets[target_index].date = input_ticket_date(tickets[target_index].date);
        save_tickets_to_file(tickets, 0);
    }
    print_tickets(tickets);
}

void sort_by_count(ticket* tickets)
{  //сортировка вставкой по убыванию
    int len = tickets_len(tickets);
    tickets[len].group[0]='\0';

    for(int i =1;i<len;++i)
    {
        ticket current = tickets[i];
        int j = i-1;
        for(; j>=0 && current.bad_count>tickets[j].bad_count; --j)
        {
            copy_one_ticket(tickets[j],tickets[j+1]);
        }
        copy_one_ticket(current,tickets[j+1]);
    }
    print_tickets(tickets);
    save_tickets_to_file(tickets,0);
}