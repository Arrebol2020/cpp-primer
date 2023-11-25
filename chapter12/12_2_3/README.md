## 练习 12.27
代补充

## 练习 12.28
``` c++
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

std::vector<std::string> contents;
std::map<std::string, std::set<int>> word2line;
int maxSize = 0;

void removeSign(std::string& s)
{
    int i = 0;
    for (int j = 0; j < s.size(); j++)
    {
        if ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z') \
            || (s[j] >= '0' && s[j] <= '9') || s[j] == ' ')
        {
            s[i++] = s[j];
        }
    }

    s.resize(i);
}

void readFromStream(std::ifstream& file)
{
    std::string line;
    while (std::getline(file, line))
    {
        std::string word;
        removeSign(line);
        std::istringstream iss(line);

        ++maxSize;

        while (iss >> word)
        {
            auto& lineSet = word2line[word];
            lineSet.insert(maxSize);
        }
        contents.push_back(line);
    }
}

void query(std::ostream& out, std::string& q)
{
    if (word2line.find(q) == word2line.end())
    {
        out << "Not find query word: " << q << std::endl;
    }
    else
    {
        auto& lineSet = word2line[q];
        out << q << " occurs " << lineSet.size() << " times" << std::endl;
        for (auto line_id : lineSet)
        {
            out << "\t (line " << line_id << ") " << contents[line_id - 1] << std::endl;
        }
    }
}

void runQueries(std::ifstream& infile)
{
    // infile 是一个 ifstream，指向我们要处理的文件
    readFromStream(infile); 
    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        // 若遇到文件尾或用户输入了'q'时循环终止
        if (!(std::cin >> s) || s == "q") break;
        query(std::cout, s);
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
```

## 练习 12.29
``` c++
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

std::vector<std::string> contents;
std::map<std::string, std::set<int>> word2line;
int maxSize = 0;

void removeSign(std::string& s)
{
    int i = 0;
    for (int j = 0; j < s.size(); j++)
    {
        if ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z') \
            || (s[j] >= '0' && s[j] <= '9') || s[j] == ' ')
        {
            s[i++] = s[j];
        }
    }

    s.resize(i);
}

void readFromStream(std::ifstream& file)
{
    std::string line;
    while (std::getline(file, line))
    {
        std::string word;
        removeSign(line);
        std::istringstream iss(line);

        ++maxSize;

        while (iss >> word)
        {
            auto& lineSet = word2line[word];
            lineSet.insert(maxSize);
        }
        contents.push_back(line);
    }
}

void query(std::ostream& out, std::string& q)
{
    if (word2line.find(q) == word2line.end())
    {
        out << "Not find query word: " << q << std::endl;
    }
    else
    {
        auto& lineSet = word2line[q];
        out << q << " occurs " << lineSet.size() << " times" << std::endl;
        for (auto line_id : lineSet)
        {
            out << "\t (line " << line_id << ") " << contents[line_id - 1] << std::endl;
        }
    }
}

void runQueries(std::ifstream& infile)
{
    // infile 是一个 ifstream，指向我们要处理的文件
    readFromStream(infile); 
    do
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        // 若遇到文件尾或用户输入了'q'时循环终止
        if (!(std::cin >> s) || s == "q") break;
        query(std::cout, s);
    }while (true);
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
```