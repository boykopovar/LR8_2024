#pragma once
#include<iostream>
#include"Task_1/include/task_1.h"
#include<iomanip>
#include <codecvt>


bool check_stream(std::istream& input = std::cin);
void del_products(product*& products);

std::string string_to_lower(const std::string& str);
std::wstring str_to_wstr(const std::string& str);
std::string wstr_to_str(const std::wstring& wstr);