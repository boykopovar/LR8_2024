#pragma once
#include<iostream>
#include"task_2.h"

int get_tickets_count();

int input_status(bool def = false);
int input_ticket_bad_count(int def = 0);
std::string input_mark();
std::string input_group();
std::string input_ticket_date(const std::string& def = "-");