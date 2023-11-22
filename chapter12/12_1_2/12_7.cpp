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