## 练习 13.23
差异地方在于，样例代码中，是通过及那个右侧运算符对象拷贝到一个局部临时对象中，而我在上一节编写中，通过 if 条件对右侧运算符对象是否时自身进行了检测

## 练习 13.24
未定义析构函数，会导致内存泄露。因为该类使用了动态分配的内存，没有通过析构函数将申请的内存释放。
为定义拷贝构造函数，可能会导致重复释放相同的内存。默认的拷贝构造函数仅进行值复制，可能会让多个 HasPtr 对象指向相同的 std::string 对象，进而在析构函数时会尝试多次删除统一块内存，从而导致程序崩溃或其他未定义的行为

## 练习 13.25
拷贝构造函数：`拷贝 std::shared_ptr 所管理的动态分配资源`
拷贝赋值函数：对自身赋值进行检测，且将右侧对象的资源拷贝给左侧对象
不需要析构函数：StrBlobStr 中的内存是通过 shared_ptr 进行管理的，当引用计数为 0 时会自动释放，不需要手动定义析构函数来释放资源

## 练习 13.26
``` c++
class StrBlobPtr;
class StrBlob{
public:
    friend class StrBlobPtr;
    StrBlobPtr begin();
    StrBlobPtr end();

    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    StrBlob(const StrBlob& other) : data(std::make_shared<std::vector<std::string>>(*rhs.data)) { }
    StrBlob& operator=(const StrBlob& other)
    {
        if (&other == this) return *this;
        data = std::make_shared<std::vector<std::string>>(*rhs.data);
        return *this;
    }
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // 元素访问
    std::string& front();
    std::string& back();
    std::string& front() const;
    std::string& back() const;
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
    std::cout << "front" << std::endl;
    return data->front();
}

std::string& StrBlob::front() const
{
    check(0, "const front on empty StrBlob");
    std::cout << "const front" << std::endl;
    return data->front();
}

std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    std::cout << "back" << std::endl;
    return data->back();
}

std::string& StrBlob::back() const
{
    check(0, "const back on empty StrBlob");
    std::cout << "const back" << std::endl;
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
```

