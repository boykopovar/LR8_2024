#include<iostream>

#include"../../global_utils.h"
#include"../include/init_products.h"
#include"../include/utils_products.h"
#include"../include/tools_products.h"
#include"../include/file_utils.h"

void add_products(product*& products)
{
    bool inf_get = false;
    int start_index = 0;

    int tech_count = get_inputs_count(), count=1;
    if(tech_count ==0)return;
    if(tech_count ==-1) inf_get = true;
    else count = tech_count;

    if(products == nullptr)
    {
        products = new product[count + 1];
        products[count].name[0]='\0';
    }

    else
    {
        while(products[start_index].name[0]!='\0')
        {
            ++start_index;
        }
        count+=start_index;
    }
    std::cout<<"-----------------------------------------------------------------------------\n"
               "|             Поле              | Значение по умолчанию (при нажатии enter) |\n"
               "-----------------------------------------------------------------------------\n"
               "| Наименование                  | *Пустой ввод завершит заполнение!*        |\n"
               "| Количество единиц             | 0                                         |\n"
               "| Количество испорченных единиц | 0                                         |\n"
               "| Цена                          | 0.0                                       |\n"
               "| Дата поступления на склад     | -                                         |\n"
               "|----------------------------------------------------------------------------\n";

    for(int i = start_index; i<count;++i)
    {
        if(products[i].name[0]=='\0')
        {
            longer_products(products, count);
        }
        std::cout<<"\nТовар "<<i+1<<'\n';

        std::string input_name = input_unique_name(products);
        if(input_name.empty())
        {
            products[i].name[0]='\0';
            if(i==0)
            {

                longer_products(products, 3);
                products[0]= {"Лампа настольная", "15.12.2024", 34.45, 26, 2};
                products[1]= {"Хлеб", "12.12.2024", 0.98, 30, 0};
                products[2]= {"Молоко", "10.12.2024", 1.12, 15, 1};
                save_to_file(products, start_index);
            }
            return;
        }
        products[i].name = input_name;

        products[i].count = input_product_count();
        products[i].bad_count = input_product_bad_count();
        products[i].cost.d = input_product_cost();
        products[i].date = input_product_date();
        save_to_file(products, start_index);

        if(inf_get)++count;
    }
}

int print_products(const product* products, const std::string& filter_name)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int last_product_index = -1, filtered_count = 0;
    std::string lower_filter_name = string_to_lower(filter_name);
    if(products == nullptr || products[0].name[0]=='\0')
    {
        std::cout<<"Товары не добавлены!\n";
        return 0;
    }
    freopen(nullptr, "w", stdout);
    freopen(nullptr, "r", stdin);
    std::wcout<<L'\n'<<std::left
             <<std::setw(8)<<L"№"
             <<std::setw(20)<<L"Наименование"
             <<std::setw(18)<<L"Кол-во"
             <<std::setw(20)<<L"Испорченные"
             <<std::setw(15)<<L"Цена"
             <<L"Дата\n"
             <<std::wstring(90,'-')<<L'\n';
    for(int i =0;;++i)
    {
        if (products[i].name[0] == '\0')break;
        if(filter_name.empty() || string_to_lower(products[i].name) == lower_filter_name)
        {
            std::wcout << std::left
                      << std::setw(8) << i + 1
                      << std::setw(20) << str_to_wstr(products[i].name)
                      << std::setw(18) << products[i].count
                      << std::setw(20) << products[i].bad_count
                      << std::setw(15) << products[i].cost.d
                      << str_to_wstr(products[i].date) << L'\n';
            filtered_count++;
            last_product_index=i;
        }
    }
    freopen(nullptr, "w", stdout);
    freopen(nullptr, "r", stdin);
    if(!filtered_count)std::cout<<"Нет продуктов, удовлетворяющих условиям поиска!\n";
    return last_product_index;
}

void search_elements_by_name(const product* products)
{
    print_products(products);
    std::cout<<"\nВведите наименование для поиска: ";
    std::string input_name;
    std::getline(std::cin, input_name);
    print_products(products, input_name);
}

void edit_element(product* products)
{
    print_products(products);
    std::cout<<"\nВведите наименование для редактирования: ";
    std::string input_name;
    std::getline(std::cin, input_name);
    if(is_name_unique(input_name, products))
    {
        std::cout<<"Продукт не найден!\n";
        return;
    }
    int target_index = print_products(products, input_name); //вернет индекс последнего выведенного
    if(target_index==-1)
    {
        std::cout<<"Продукт не найден!\n";
        return;
    }


    std::cout<<"\n\n-----------------------------------------------------------------------------\n"
               "|             Поле              | Значение по умолчанию (при нажатии enter) |\n"
               "-----------------------------------------------------------------------------\n"
               "| Наименование                  | *Удаление элемента*                       |\n"
               "| Количество единиц             | "<<std::setw(42)<<products[target_index].count<<"|\n"
               "| Количество испорченных единиц | "<<std::setw(42)<<products[target_index].bad_count<<"|\n"
               "| Цена                          | "<<std::setw(42)<<products[target_index].cost.d<<"|\n"
               "| Дата поступления на склад     | "<<std::setw(42)<<products[target_index].date<<"|\n"
               "|----------------------------------------------------------------------------\n";
    std::cout<<"\nТовар "<<target_index+1<<" ("<<products[target_index].name<<") "
               "[Enter - удалить элемент]\n";

    std::string new_name = input_unique_name(products, target_index);

    if(new_name.empty())
    {
        //удаление элемента
        int count = target_index+1;
        for(int i = target_index+1;products[i].name[0]!='\0';++i)
        {
            ++count;
        }
        if(count -1!=target_index)
        {
            copy_one_product(products[count-1], products[target_index]);
        }
        products[count-1].name="";
        products[count-1].name[0]='\0';
        save_to_file(products, 0);
    }
    else
    {
        products[target_index].name = new_name;

        products[target_index].count = input_product_count(products[target_index].count);
        products[target_index].bad_count = input_product_bad_count(products[target_index].bad_count);
        products[target_index].cost.d = input_product_cost(products[target_index].cost.d);
        products[target_index].date = input_product_date(products[target_index].date);
        save_to_file(products, 0);
    }

    print_products(products);
}

void sort_by_count(product* products)
{  //сортировка вставкой по убыванию
    int len = products_len(products);
    products[len].name[0]='\0';

    for(int i =1;i<len;++i)
    {
        product current = products[i];
        int j = i-1;
        for(; j>=0 && current.count>products[j].count; --j)
        {
            copy_one_product(products[j],products[j+1]);
        }
        copy_one_product(current,products[j+1]);
    }
    print_products(products);
    save_to_file(products,0);
}

int print_by_min_cost(const product* products, double min_cost)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int last_product_index = -1, filtered_count = 0;
    if(products == nullptr || products[0].name[0]=='\0')
    {
        std::cout<<"Товары не добавлены!\n";
        return 0;
    }
    freopen(nullptr, "w", stdout);
    freopen(nullptr, "r", stdin);
    std::wcout<<'\n'<<std::left
              <<std::setw(8)<<L"№"
              <<std::setw(20)<<L"Наименование"
              <<std::setw(18)<<L"Кол-во"
              <<std::setw(20)<<L"Испорченные"
              <<std::setw(15)<<L"Цена"
              <<L"Дата\n"
              <<std::wstring(90,'-')<<'\n';
    for(int i =0;;++i)
    {
        if (products[i].name[0] == '\0')break;
        if(products[i].cost.d>min_cost)
        {
            std::wcout << std::left
                       << std::setw(8) << i + 1
                       << std::setw(20) << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(products[i].name)
                       << std::setw(18) << products[i].count
                       << std::setw(20) << products[i].bad_count
                       << std::setw(15) << products[i].cost.d
                       << str_to_wstr(products[i].date) << '\n';
            filtered_count++;
            last_product_index=i;
        }
    }
    freopen(nullptr, "w", stdout);
    freopen(nullptr, "r", stdin);
    if(!filtered_count)std::cout<<"Нет продуктов дороже "<< min_cost<<'\n';
    return last_product_index;
}