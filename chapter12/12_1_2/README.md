## 练习 12.6
``` c++
#include <iostream>
#include <vector>

std::vector<int>* getVector()
{
    return new std::vector<int>();
}

void getInput(std::istream& in, std::vector<int>& nums)
{
    int tmp;
    while (in >> tmp)
    {
        nums.push_back(tmp);
    }
}

void printResult(std::vector<int>& nums)
{
    for (auto num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main()
{
    auto p = getVector();
    getInput(std::cin, *p);
    printResult(*p);
    delete p;
    return 0;
}
```

## 练习 12.7
``` c++
#include <iostream>
#include <vector>
#include <memory>


std::shared_ptr<std::vector<int>> getVector()
{
    return std::make_shared<std::vector<int>>();
}

void getInput(std::istream& in, std::shared_ptr<std::vector<int>>& nums)
{
    int tmp;
    while (in >> tmp)
    {
        nums->push_back(tmp);
    }
}

void printResult(std::shared_ptr<std::vector<int>>& nums)
{
    for (auto num : *nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main()
{
    auto p = getVector();
    getInput(std::cin, p);
    printResult(p);
    //delete p;
    return 0;
}
```

## 练习 12.8
错误，但是可以正常运行，存在内存泄漏。因为函数 b 返回值为 bool，函数体中申请了一块内存，并将内存地址返回，此时会出现隐式类型转换（内存地址转化为 bool 类型，基本转化为 true），函数能够正常调用，但是申请的内存地址并没有销毁，从而会导致内存泄漏。

## 练习 12.9
``` c++
int *q = new int(42), *r = new int(100);
r = q;
```
上述代码中，让 r 也指向了 q 所指向的内存地址，没有对 r 原来指向的内存空间释放，会导致内存泄漏

``` c++
auto q2 = std::make_shared<int>(42), r2 = std::make_shared<int>(100);
r2 = q2;
```
而在这里，使用了 shared_ptr 指针，当 r2 = q2 时，r2 会将原来的指针引用计数减一，然后指向和 q2 一样的地址，q2 的指针引用计数加一。然后判断指针的引用计数是否为 0，为 0 就会释放申请的内存空间，从而不会和之前一样出现内存泄露问题。