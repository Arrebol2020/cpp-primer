## 练习 13.29
在 `swap(HasPtr&, HasPtr&)` 函数中调用 `std::swap(lhs.ps, rhs.ps)` 和 `std::swap(lhs.ps, rhs.ps)`，调用的是标准库中的 `swap` 函数，而被捕时再次调用 `swap(HasPtr&, HasPtr&)`，因此不会出现递归调用

## 练习 13.30
``` c++
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
```

## 练习 13.31
``` c++
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
```

## 练习 13.32
可以，因为 `swap` 函数允许在不变化对象本身的情况下，交换指向的数据。这对于指针成员来说很有用，因为指针交换会更快，并且避免了深层的数据复制，减少内存的重新分配