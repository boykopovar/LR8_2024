#pragma once
#include"task_2.h"
#include"../../global_utils.h"

void copy_one_ticket(const ticket& from_ticket, ticket& to_ticket);
void longer_tickets(ticket*& tickets, int final_size);
int tickets_len(ticket* tickets);