#include"task_1.h"

void add_products(product*& products);
int print_products(const product* products, const std::string& name_filter= "");
void search_elements_by_name(const product* products);
void edit_element(product* products);
void sort_by_count(product* products);
int print_by_min_cost(const product* products, double min_cost);