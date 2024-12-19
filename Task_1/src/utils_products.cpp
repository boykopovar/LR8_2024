#include<iostream>

#include "../../global_utils.h"
#include"../include/utils_products.h"


void copy_one_product(const product& from_product, product& to_product)
{
    to_product.name = from_product.name;
    to_product.count = from_product.count;
    to_product.bad_count = from_product.bad_count;
    to_product.cost.d = from_product.cost.d;
    to_product.date = from_product.date;
}

void longer_products(product*& products, unsigned long long final_size)
{
    auto* new_products = new product[final_size + 1];
    for(int i =0;products[i].name[0]!='\0';++i)
    {
        copy_one_product(products[i], new_products[i]);
    }
    new_products[final_size].name[0]='\0';
    delete[] products;
    products = new_products;
}

bool is_name_unique(std::string& input_name, product* products, int except_index)
{
    std::string lower_input_name = string_to_lower(input_name);
    for(int i =0;products[i].name[0]!='\0';++i)
    {
        if( string_to_lower(products[i].name) == lower_input_name && i!=except_index)
        {
            return false;
        }
    }
    return true;
}

int products_len(product* products)
{
    for(int i = 0;;++i)
    {
        if(products[i].name[0]=='\0') return i;

    }
}