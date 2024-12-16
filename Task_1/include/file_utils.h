#pragma once
#include"../../global_utils.h"
#include"task_1.h"

void save_to_file(product* products, int start_index, const std::string& path = "task1.dat");
product* load_from_file(const std::string& path="task1.dat");
