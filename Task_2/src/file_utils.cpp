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
    std::ifstream in(path);
    if(!in)return nullptr;
    int count = 6;
    auto* tickets = new ticket[count];
    tickets[5].group[0]='\0';
    int i =0;
    for(i =0;in.get()!=EOF;++i)
    {
        in.unget();
        if(tickets[i].group[0]=='\0')
        {
            count+=5;
            longer_tickets(tickets, count+5);
        }
        std::string first_line;
        std::getline(in, first_line);
        if(first_line.empty())break;
        tickets[i].group = first_line;

        std::getline(in, tickets[i].mark);
        std::getline(in, tickets[i].date);
        in>>tickets[i].status.b;
        in>>tickets[i].bad_count;
        in.ignore();
    }
    tickets[i].group[0]='\0';
    in.close();
    return tickets;
}
