#include <iostream>

class HasPtr
{
public:
    friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const std::string& s = std::string()) :
        ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) { }
    HasPtr& operator=(const HasPtr& rhs)
    {
        auto newp = new std::string(*rhs.ps);
        delete ps;
        ps = newp;
        i = rhs.i;
        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
    void swap(HasPtr& rhs) {
        using std::swap;
        swap(ps, rhs.ps);
        swap(i, rhs.i);
        std::cout << "Swap executed!" << std::endl;
    }
    std::string getPs()
    {
        return *ps; 
    }
private:
    std::string *ps;
    int i;
};

void swap(HasPtr& lhs, HasPtr& rhs)
{
    lhs.swap(rhs);
}

int main()
{
    HasPtr h1("Hello"), h2("World");
    std::cout << "Before swap: " << std::endl;
    std::cout << "h1: " << h1.getPs() << ", h2: " << h2.getPs() << std::endl;

    swap(h1, h2);

    std::cout << "After swap: " << std::endl;
    std::cout << "h1: " << h1.getPs() << ", h2: " << h2.getPs() << std::endl;

    return 0;
}