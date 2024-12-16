#pragma once
#include"../../global_utils.h"
#include"task_2.h"

void save_tickets_to_file(ticket* tickets, int start_index, const std::string& path = "task2.dat");
ticket* load_tickets_from_file(const std::string& path="task2.dat");
