#include <iostream>

bool b()
{
    int* p = new int;
    return p;
}
int main()
{
    if (b())
        std::cout << "true";
    else
        std::cout << "false";
    return 0;
}