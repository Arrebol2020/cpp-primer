## 练习 13.14
将会都输出 1，因为默认的拷贝构造函数是直接拷贝所有的数据成员，因此 a, b, c 的 mysn 均为 1

``` c++
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
```

输出：
``` bash
numbered()
1
1
1
1
```

## 练习 13.15
会改变，输出结果见后面，因为 `b = a, c = b;` 均会调用一次拷贝构造函数，而每次函数调用都会调用一次拷贝构造函数
``` c++
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
```

输出：
``` bash
numbered()
numbered(const numbered& other)
numbered(const numbered& other)
numbered(const numbered& other)
4
numbered(const numbered& other)
5
numbered(const numbered& other)
6
6
```

## 练习 13.16
会改变，输出结果见后面，因为 `b = a, c = b;` 均会调用一次拷贝构造函数，而此时`每次函数调用不再调用拷贝构造函数`，因为函数`参数是引用传递`

``` c++
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

void f(numbered& s) { std::cout << s.mysn << std::endl; }
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
```

输出：
``` bash
numbered()
numbered(const numbered& other)
numbered(const numbered& other)
1
2
3
3
```

## 练习 13.17
见上述。