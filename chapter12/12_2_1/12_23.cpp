#include <iostream>
#include <cstring>

int main()
{
    const char* str1("hello ");
    const char* str2("world!");
    char* strCat1 = new char[strlen(str1) + strlen(str2) + 1];

    strcat(strCat1, str1);
    strcat(strCat1, str2);

    std::cout << strCat1 << std::endl;

    const std::string str3{"hello"};
    const std::string str4{"world!"};
    std::string strCat2{str3 + str4};
    std::cout << strCat2 << std::endl;
    return 0;
}