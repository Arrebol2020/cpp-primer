#include <iostream>
#include <vector>

struct X
{
    X() { std::cout << "X()" << std::endl; }
    X(const X&) { std::cout << "X(const X&)" << std::endl; };
    X& operator=( const X&) { std::cout << "operator=(const X&)" << std::endl; return *this; }
    ~X() { std::cout << "~X()" << std::endl; }
};

void f1(X x) { std::cout << "value" << std::endl; };
void f2(X& x) { std::cout << "&" << std::endl; }

int main()
{
    X x;  // X()
    f1(x);  // X(const X&) value ~X()
    f2(x); // &

    X* ptr = new X(); //X()
    
    std::vector<X> v;
    v.push_back(x);  // X(const X&)
    std::cout << v.capacity() << std::endl;
    v.push_back(*ptr);  // X(const X&)
    std::cout << v.capacity() << std::endl;

    delete ptr;  // ~X()
    return 0;
}
// ~X()