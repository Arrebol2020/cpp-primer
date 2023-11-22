#include <iostream>
#include <memory>

void process(std::shared_ptr<int> ptr) {}
int main()
{
    auto sp = std::make_shared<int>();
    auto p = sp.get();
    delete p;
    
    return 0;
}