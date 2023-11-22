#include <iostream>
#include <memory>

void process(std::shared_ptr<int> ptr) {}
int main()
{
    auto p = new int();
    auto sp = std::make_shared<int>();

    process(sp);  // 成功，直接使用 sp 作为参数
    process(new int());  // 失败，shared_ptr 不能将一个内置指针隐式转化为一个智能指针
    process(p);  // 失败，shared_ptr 不能将一个内置指针隐式转化为一个智能指针
    process(std::shared_ptr<int>(p)); // 成功，使用 p 来生成一个临时 shared_ptr 变量 
    return 0;
}