#include<iostream>
#include<fstream>
#include"../include/file_utils.h"
#include"../include/utils_products.h"

void save_to_file(product* products, int start_index, const std::string& path)
{
    std::ofstream out;
    if(start_index==0)out.open(path, std::ios::binary);
    else out.open(path, std::ios::app | std::iostream::binary);
    if(!out)return;

    for(int i =start_index;products[i].name[0]!='\0';++i)
    {
        auto name_len = static_cast<long long int>(products[i].name.size());
        out.write((char*)(&name_len), sizeof(name_len));
        out.write(products[i].name.c_str(), name_len );

        auto date_len = static_cast<long long int>(products[i].date.size());
        out.write((char*)(&date_len), sizeof(date_len));
        out.write(products[i].date.c_str(), date_len );

        out.write((char*)(&products[i].cost.d), sizeof(products[i].cost.d));
        out.write((char*)(&products[i].count), sizeof(products[i].count));
        out.write((char*)(&products[i].bad_count), sizeof(products[i].bad_count));
    }
    out.close();
}

product* load_from_file(const std::string& path)
{
    std::ifstream in(path, std::ios::binary);
    if(!in)return nullptr;
    int count = 6;
    auto* products = new product[count];
    products[5].name[0]='\0';

    int i=0;
    long long int name_len;
    while( in.read((char*)(&name_len), sizeof(name_len)) )
    {
        if(products[i].name[0]=='\0')
        {
            count+=5;
            longer_products(products, count);
        }

        products[i].name.resize(name_len);
        in.read(&products[i].name[0], name_len );

        long long int date_len;
        in.read((char*)(&date_len), sizeof(date_len));
        products[i].date.resize(date_len);
        in.read(&products[i].date[0], date_len );

        in.read((char*)&products[i].cost.d, sizeof(products[i].cost.d) );
        in.read((char*)&products[i].count, sizeof(products[i].count) );
        in.read((char*)&products[i].bad_count, sizeof(products[i].bad_count) );

        ++i;
    }

    products[i].name[0]='\0';
    in.close();
    return products;
}
