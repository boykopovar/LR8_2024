#include<fstream>
#include<filesystem>

#include"../include/file_utils.h"
#include"../include/utils_products.h"

const char MAGIC_TITLE[] = {"BoykoLR"}; //8байт


void save_to_file(product* products, int start_index, const std::string& path)
{
    unsigned long long static_struct = sizeof(products[0].cost.d) + 2*sizeof(products[0].count);
    unsigned long long int count = 0, i = 0;

    std::fstream file(path, std::ios::binary | std::ios::out | std::ios::in);
    if(!file)
    {
        file.open(path, std::ios::binary | std::ios::out);
        file.write(MAGIC_TITLE, sizeof(MAGIC_TITLE));
        file.write((char*)&i, sizeof(i));
        file.close();
        file.open(path, std::ios::binary | std::ios::in | std::ios::out);
    }

    if(!file)return;
    file.seekg(sizeof(MAGIC_TITLE));
    file.read((char*)&count, sizeof(count));
    //if(start_index>count) start_index = count;

    unsigned long long int static_pos= start_index*static_struct+sizeof(i)+sizeof(MAGIC_TITLE);
    file.seekp(static_cast<long>(static_pos));

    //статические поля структуры
    for(i=start_index;products[i].name[0]!='\0';++i)
    {
        file.write((char*)(&products[i].cost.d), sizeof(products[i].cost.d));
        file.write((char*)(&products[i].count), sizeof(products[i].count));
        file.write((char*)(&products[i].bad_count), sizeof(products[i].bad_count));
    }
    count = std::max(count, i);

    unsigned long long str_pos = sizeof(MAGIC_TITLE) + sizeof(i) + count*static_struct;
    std::filesystem::resize_file(path, str_pos);
    //std::filesystem::resize_file(path, count*static_struct + sizeof(i) + sizeof(MAGIC_TITLE));
    file.seekp(static_cast<long>(str_pos));

    //strings в конец
    for(i=0;products[i].name[0]!='\0';++i)
    {
        auto name_len = static_cast<long long int>(products[i].name.size());
        file.write((char*)(&name_len), sizeof(name_len));
        file.write(products[i].name.c_str(), name_len );

        auto date_len = static_cast<long long int>(products[i].date.size());
        file.write((char*)(&date_len), sizeof(date_len));
        file.write(products[i].date.c_str(), date_len );
    }
    file.seekp(sizeof(MAGIC_TITLE));
    file.write((char*)&i, sizeof(i)); //запись количества продуктов после MAGIC_TITLE
    file.close();
}


void edit_product_in_file(product* products, int target_index, const std::string& path)
{
    unsigned long long static_struct = sizeof(products[0].cost.d) + 2*sizeof(products[0].count);
    std::ifstream in(path, std::ios::binary | std::ios::in);
    if(!in)
    {
        save_to_file(products, 0, path);
        return;
    }

    unsigned long long int i, count=0, str_pos=0;
    std::string load_magic_title = get_magic_title(in);
    if(load_magic_title != MAGIC_TITLE)
    {
        in.close();
        return;
    }

    in.read((char*)&count, sizeof(count));
    in.close();

    if(target_index < count)
    {
        std::ofstream file(path, std::ios::binary | std::ios::out);
        unsigned long long static_pos = sizeof(MAGIC_TITLE) + sizeof(count) + target_index*static_struct;
        file.seekp(static_cast<long>(static_pos));

        file.write((char*)&products[target_index].cost.d,sizeof(products[target_index].cost.d));
        file.write((char*)&products[target_index].count,sizeof(products[target_index].count));
        file.write((char*)&products[target_index].bad_count,sizeof(products[target_index].bad_count));

        file.close();
    }

    str_pos = sizeof(MAGIC_TITLE) + sizeof(count);
    str_pos += count * static_struct;

    std::ifstream file(path, std::ios::binary | std::ios::in);
    for(i=0; (i<count && in && in.peek()!=EOF && products[i].name[0]!='\0') ; ++i)
    {
        if(i==target_index)
        {
            std::filesystem::resize_file(path, str_pos+target_index); //обрезка файла, (остаются pos байтов)
            strings_to_file(products, target_index, str_pos, path);
            return;
        }
        line_from_bin(file); //наименование
        line_from_bin(file); //дата
    }
    file.close();
    save_to_file(products, 0, path);
}


product* load_from_file(const std::string& path)
{
    std::ifstream in(path, std::ios::binary | std::ios::in);
    if(!in || in.peek() == EOF)
    {
        in.close();
        return nullptr;
    }

    std::string load_magic_title = get_magic_title(in);
    if(MAGIC_TITLE != load_magic_title)
    {
        in.close();
        return nullptr;
    }

    unsigned long long int i, count = 1;
    in.read((char*)&count, sizeof(count));

    auto* products = new product[count+1]; //начальная память
    for(i=0; i<count && in && in.peek()!=EOF; ++i)
    {
        if(i>=count)
        {
            count+=5;
            longer_products(products, count);
        }

        in.read((char*)&products[i].cost.d, sizeof(products[i].cost.d) );
        in.read((char*)&products[i].count, sizeof(products[i].count) );
        in.read((char*)&products[i].bad_count, sizeof(products[i].bad_count) );
    }

    //считывание strings в конце
    for(i=0; i<count && in && in.peek()!=EOF; ++i)
    {
        products[i].name = line_from_bin(in);
        products[i].date = line_from_bin(in);
    }

    products[i].name[0]='\0';
    in.close();
    return products;
}


template <typename type> // - не обязательно; по умолчанию long long int
std::string line_from_bin(std::ifstream& file)
{
    std::string line;
    type len; //только численный тип

    file.read( (char*)&len, sizeof(len));
    line.resize(len);
    file.read((char*)&line[0], len);

    return line;
}


std::string get_magic_title(std::ifstream& file, long long title_size)
{
    std::string load_magic_title;
    load_magic_title.resize(title_size-1);

    file.read((char*)&load_magic_title[0], title_size);
    return MAGIC_TITLE;
}


void strings_to_file(product* products, unsigned long long target, unsigned long long str_pos, const std::string& path)
{
    std::ofstream file(path, std::ios::binary | std::ios::out);
    file.seekp(static_cast<long long>(str_pos));

    for(unsigned long long i=target; products[i].name[0]!='\0'; ++i)
    {
        auto name_len = static_cast<long long int>(products[i].name.size());
        file.write((char *) (&name_len), sizeof(name_len));
        file.write(products[i].name.c_str(), name_len);

        auto date_len = static_cast<long long int>(products[i].date.size());
        file.write((char *) (&date_len), sizeof(date_len));
        file.write(products[i].date.c_str(), date_len);
    }
    file.close();
}