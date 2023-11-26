#ifndef QUERYRESULT
#define QUERYRESULT
#include <iostream>
#include <memory>
#include <set>
#include <vector>

class QueryResult
{
friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) :
        sought(s), lines(p), file(f) { }
    std::set<line_no>::iterator begin() { return lines->begin(); }
    std::set<line_no>::iterator end() { return lines->end(); }
    std::shared_ptr<std::vector<std::string>> getfile() { return file; }
private:
    std::string sought;  // 查询单词
    std::shared_ptr<std::set<line_no>> lines;  // 出现的行号
    std::shared_ptr<std::vector<std::string>> file;  // 输入文件
};

std::string make_plural(size_t ctr, const std::string& word,
                                    const std::string& ending)
{
    return (ctr > 1) ? word + ending : word;
}

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
    // 如果找到了单词，打印出现次数和所有出现的位置
    os << qr.sought << " occurs " << qr.lines->size() << " "
        << make_plural(qr.lines->size(), "time", "s") << std::endl;
    // 打印单词出现的每一行
    for (auto num : *qr.lines)  // 对 set 中每个单词
    {
        // 避免行号从 0 开始给用户带来的困惑
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    }
    return os;
}

#endif