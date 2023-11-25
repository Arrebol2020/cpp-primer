#ifndef TEXTQUERY
#define TEXTQUERY
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <memory>
#include "QueryResult.h"

class TextQuery
{
public:
    friend class QueryResult;
    TextQuery() : contents(std::make_shared<std::vector<std::string>>()), qResult(std::make_shared<std::set<int>>()) {}
    TextQuery(std::ifstream& inFileStream);
    bool query(std::string& q);
private:
    std::shared_ptr<std::vector<std::string>> contents;
    std::shared_ptr<std::set<int>> qResult;
    std::map<std::string, std::set<int>> word2line;
    int maxLine = 0;
};

TextQuery::TextQuery(std::ifstream& inFileStream)
    : contents(std::make_shared<std::vector<std::string>>()), qResult(std::make_shared<std::set<int>>()) {

    std::string line;
    int lineID = 0;
    while ( std::getline(inFileStream, line) )
    {
        lineID++;

        std::istringstream iss(line);
        contents->push_back(line);
        
        std::string word;
        while ( iss >> word)
        {
            auto& lineSet = word2line[word];
            lineSet.insert(lineID);
        }
        
    }
    maxLine = lineID;
}

bool TextQuery::query(std::string& q)
{
    if (word2line.find(q) == word2line.end())
    {
        return false;
    }
    else
    {
        qResult = std::make_shared<std::set<int>>(word2line[q]);
        return true;
    }
}
#endif