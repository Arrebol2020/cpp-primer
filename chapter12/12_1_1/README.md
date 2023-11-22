## 练习 12.1
各有 4 个。
测试代码：
``` c++
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

class StrBlob{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // 元素访问
    std::string& front();
    std::string& back();
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) { }
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) { }
void StrBlob::check(size_type i, const std::string &msg) const
{
    if ( i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}


int main()
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        std::cout << b1.size() << " " << b2.size() << std::endl;
    }
    std::cout << b1.size();

    return 0;
}
```

## 练习 12.2
代码
``` c++
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

class StrBlob{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // 元素访问
    std::string& front();
    std::string& back();
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) { }
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) { }
void StrBlob::check(size_type i, const std::string &msg) const
{
    if ( i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}


int main()
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        std::cout << b1.size() << " " << b2.size() << std::endl;
    }
    std::cout << b1.size();

    return 0;
}
```

## 练习 12.3
不需要，因为 push_back 和 pop_back 需要对成员变量进行修改，而在 const 成员函数中调用的函数应该是不会修改对象状态的，这样才能保证 const 对象在其生命周期内不被修改。如果在 const 成员函数中调用会修改对象状态的函数，会导致编译错误，因为这违反了 const 的语义

## 练习 12.4
因为 data->size() 至少是 0，因此不需要进行额外检查 i 是否大于 0

## 练习 12.5
优点：
- 简化对象创建： 不使用 explicit 关键字的构造函数可以允许隐式类型转换，使得对象的创建更加便利。用户可以通过传递一个 initializer_list 来创建 StrBlob 对象，而不需要显式调用构造函数。

- 便于代码编写： 省略 explicit 关键字可以减少代码量，使得代码编写更加简洁和直观。

缺点：
- 意外的隐式转换： 如果没有 explicit 关键字，initializer_list 类型的隐式转换可能会导致一些意外的行为。例如，可能导致用户意外地创建 StrBlob 对象，而不清楚正在进行的隐式类型转换。

- 潜在的歧义： 如果有其他构造函数也接受相同类型的参数（比如 std::vector<std::string>），这可能导致歧义，使得编译器无法确定应该调用哪一个构造函数。