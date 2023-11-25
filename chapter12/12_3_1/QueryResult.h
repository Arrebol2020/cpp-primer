#ifndef QUERYRESULT
#define QUERYRESULT

#include "TextQuery.h"

class QueryResult
{
public:
    QueryResult(TextQuery& tq) : wkptrContents(tq.contents), wkptrQResult(tq.qResult) {};
    void print(std::ostream& out, bool isFind);
private:
    std::weak_ptr<std::vector<std::string>> wkptrContents;
    std::weak_ptr<std::set<int>> wkptrQResult;
};

void QueryResult::print(std::ostream& out, bool isFind)
{
    if (isFind)
    {
        auto qResult = wkptrQResult.lock();
        if (!qResult)
            throw std::runtime_error("unbound textquery");
        
        auto contents = wkptrContents.lock();
        if (!contents)
            throw std::runtime_error("unbound textquery");

        out << "This word occur " << (*qResult).size() << std::endl;
        for (auto line_id : (*qResult))
        {
            out << "\t (line " << line_id << ") " << (*contents)[line_id - 1] << std::endl;
        }

    }
    else
    {
        out << "Not fine this word!" << std::endl; 
    }
}

#endif