#include <iostream>

class numbered
{
public:
    numbered()
    {
        std::cout << "numbered()" << std::endl;
        curID += 1;
        mysn = curID;
    }
    numbered(const numbered& other)
    {
        std::cout << "numbered(const numbered& other)" << std::endl;
        curID += 1;
        mysn = curID;
    }
public:
    int mysn;
    static int curID;
};

int numbered::curID = 0;

void f(numbered s) { std::cout << s.mysn << std::endl; }
int main()
{
    numbered a, b = a, c = b;
    //numbered a, b, c;
    //b = a;
    //c = a;
    f(a);
    f(b);
    f(c);
    std::cout << numbered::curID << std::endl;
    return 0;
}