#include<iostream>
#include"../include/utils_tickets.h"


void copy_one_ticket(const ticket& from_ticket, ticket& to_ticket)
{
    to_ticket.group = from_ticket.group;
    to_ticket.mark = from_ticket.mark;
    to_ticket.bad_count = from_ticket.bad_count;
    to_ticket.status.b = from_ticket.status.b;
    to_ticket.date = from_ticket.date;
}

void longer_tickets(ticket*& tickets, int final_size)
{
    auto* new_tickets = new ticket[final_size+1];
    for(int i =0;tickets[i].group[0]!='\0';++i)
    {
        copy_one_ticket(tickets[i], new_tickets[i]);
    }
    new_tickets[final_size].group[0]='\0';
    delete[] tickets;
    tickets = new_tickets;
}

int tickets_len(ticket* tickets)
{
    for(int i = 0;;++i)
    {
        if(tickets[i].group[0]=='\0') return i;

    }
}