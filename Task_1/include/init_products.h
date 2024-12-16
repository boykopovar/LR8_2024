#pragma once
#include<iostream>
#include"task_1.h"

int get_inputs_count();

int input_product_count(int def = 0);
int input_product_bad_count(int def = 0);
double input_product_cost(double def = 0.0);
std::string input_unique_name(product* tickets, int except_unique_index =-1);
std::string input_product_date(const std::string& def = "-");