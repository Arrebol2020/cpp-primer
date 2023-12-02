#include <iostream>
#include <vector>
#include <algorithm>

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
    
    bool operator<(HasPtr& rhs)
    {
        if (*ps > *rhs.ps) swap(rhs);
        return *ps < *rhs.ps;
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
    std::vector<HasPtr> v;
    v.emplace_back("C");
    v.emplace_back("A");
    v.emplace_back("B");
    
    std::sort(v.begin(), v.end());

    for (auto& ptr : v)
    {
        std::cout << ptr.getPs() << std::endl;
    }

    return 0;
}