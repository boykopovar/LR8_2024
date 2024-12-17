#include<iostream>
#include"global_utils.h"


bool check_stream(std::istream& input)
{
    if(input.fail() || input.get() !='\n')
    {
        input.clear();
        for(int c=0;c!='\n';c=input.get());
        return false;
    }
    return true;
}

void del_products(product*& products)
{
    delete[] products;
    products = nullptr;
}

std::string string_to_lower(const std::string& str)
{
    std::wstring w_result = str_to_wstr(str);
    for(int i =0;w_result[i]!=L'\0';++i)
    {
        w_result[i] = static_cast<wchar_t>(towlower(w_result[i]));
    }
    return wstr_to_str(w_result);
}

std::wstring str_to_wstr(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string wstr_to_str(const std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}
