#include <iostream>
#include <fstream>
#include "TextQuery.h"
#include "QueryResult.h"

void runQueries(std::ifstream& infile)
{
    // infile 是一个 ifstream，指向我们要处理的文件
    TextQuery tq(infile);  // 保存文件并建立查询 map
    // 与用户交互：提示用户输入要查询的单词，完成查询并打印结果
    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        // 若遇到文件尾或用户输入了'q'时循环终止
        if (!(std::cin >> s) || s == "q") break;
        // 指向查询并打印结果
        print(std::cout, tq.query(s)) << std::endl;
    }
}

int main()
{
    std::string filePath("./storyDataFile");
    std::ifstream fileStream(filePath);

    if (fileStream.is_open())
    {
        runQueries(fileStream);
        fileStream.close();
    }
    else
    {
        std::cerr << "Unable to open file, program exit." << std::endl;
        return 0;
    }
    

    return 0;
}