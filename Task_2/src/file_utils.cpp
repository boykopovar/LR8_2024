#include<iostream>
#include<fstream>

#include"../include/file_utils.h"
#include"../include/utils_tickets.h"


void save_tickets_to_file(ticket* tickets, int start_index, const std::string& path)
{
    std::ofstream out;

    if(start_index==0)out.open(path);
    else out.open(path, std::ios::app);

    if(!out)return;

    for(int i =start_index;tickets[i].group[0]!='\0';++i)
    {
        out<<tickets[i].group<<'\n';
        out<<tickets[i].mark<<'\n';
        out<<tickets[i].date<<'\n';
        out<<tickets[i].status.b<<'\n';
        out<<tickets[i].bad_count<<"\n";
    }

    out.close();
}

ticket* load_tickets_from_file(const std::string& path)
{
    std::ifstream file(path);
    if(!file) return nullptr;
    int i, count = 6;

    auto* tickets = new ticket[count];
    tickets[5].group[0]='\0';

    for(i =0; file.peek() != EOF; ++i)
    {
        if(tickets[i].group[0]=='\0')
        {
            count+=5;
            longer_tickets(tickets, count+5);
        }

        std::string first_line;
        std::getline(file, first_line);

        if(first_line.empty())break;

        tickets[i].group = first_line;
        std::getline(file, tickets[i].mark);
        std::getline(file, tickets[i].date);

        file >> tickets[i].status.b;
        file >> tickets[i].bad_count;

        file.get(); // '\n' завершает каждую структуру
    }
    tickets[i].group[0]='\0';
    file.close();

    return tickets;
}
