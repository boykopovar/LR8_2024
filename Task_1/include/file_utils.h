#pragma once
#include"../../global_utils.h"
#include"task_1.h"

void save_to_file(product* products, int start_index, const std::string& path = "task1.dat");
void edit_product_in_file(product* products, int target_index, const std::string& path = "task1.dat");
product* load_from_file(const std::string& path="task1.dat");

template <typename type = long long int>
std::string line_from_bin(std::ifstream& file);

std::string get_magic_title(std::ifstream& file, long long title_size=8);
void strings_to_file(product* products, unsigned long long target, unsigned long long str_pos, const std::string& path);