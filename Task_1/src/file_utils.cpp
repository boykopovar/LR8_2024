#include<fstream>
#include<filesystem>

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

void edit_product_in_file(product* products, int target_index, const std::string& path)
{
    std::ifstream in(path, std::ios::binary | std::ios::in);
    if(!in)
    {
        save_to_file(products, 0, path);
        return;
    }

    unsigned long long int i, pos=0;
    for(i=0; (in && in.peek()!=EOF && products[i].name[0]!='\0') ; ++i)
    {
        if(i==target_index)
        {
            in.close();
            std::filesystem::resize_file(path, pos); //обрезка файла, (остаются pos байтов)
            save_to_file(products, target_index, path);
            return;
        }

        pos+= sizeof(long long int) + line_from_bin(in).size(); //строка name
        pos+= sizeof(long long int) + line_from_bin(in).size(); //строка date

        double cost_buf;
        int count_buf;

        in.read((char*)&cost_buf, sizeof(products[i].cost.d) );
        pos+= sizeof(products[i].cost.d);

        in.read((char*)&count_buf, sizeof(products[i].count) );
        pos+= sizeof(products[i].count);

        in.read((char*)&count_buf, sizeof(products[i].bad_count) );
        pos+= sizeof(products[i].bad_count);
    }
    save_to_file(products, 0, path);
}

product* load_from_file(const std::string& path)
{
    std::ifstream in(path, std::ios::binary);
    if(!in)return nullptr;

    int i, count = 6;
    auto* products = new product[count];
    products[5].name[0]='\0'; //начальная память

    for(i=0;  in && in.peek()!=EOF; ++i)
    {
        if(products[i].name[0]=='\0')
        {
            count+=5;
            longer_products(products, count);
        }

        products[i].name = line_from_bin(in);
        products[i].date = line_from_bin(in);

        in.read((char*)&products[i].cost.d, sizeof(products[i].cost.d) );
        in.read((char*)&products[i].count, sizeof(products[i].count) );
        in.read((char*)&products[i].bad_count, sizeof(products[i].bad_count) );
    }

    products[i].name[0]='\0';
    in.close();
    return products;
}

template <typename type> // по умолчанию long long int
std::string line_from_bin(std::ifstream& file)
{
    std::string line;
    type len; //только численный тип

    file.read( (char*)&len, sizeof(len));
    line.resize(len);
    file.read((char*)&line[0], len);

    return line;
}