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


int main()
{
    
    StrBlob b1 = {"a", "an", "the"};
    const StrBlob b2 = {"a", "an", "the"};
    
    
    b1.front();
    b2.front();

    b1.back();
    b2.back();

    return 0;
}