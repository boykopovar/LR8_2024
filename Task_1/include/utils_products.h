#pragma once

void copy_one_product(const product& from_product, product& to_product);
void longer_products(product*& products, unsigned long long final_size);
bool is_name_unique(std::string& input_name, product* products, int except_index =-1);
int products_len(product* products);