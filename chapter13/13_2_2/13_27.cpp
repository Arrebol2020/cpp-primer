#include <iostream>


class HasPtr
{
public:
    HasPtr(const std::string& s = std::string()) :
        ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i), use(rhs.use){ ++*use; }
    HasPtr& operator=(const HasPtr& rhs)
    {
        ++*rhs.use;
        
        if (--*use == 0)
        {
            delete ps;
            delete use;
        }
        ps = rhs.ps;
        i = rhs.i;
        use = rhs.use;
        return *this;
    }
    ~HasPtr()
    {
        if (--*use == 0)
        {
            delete ps;
            delete use;
        }
    }
private:
    std::string *ps;
    int i;
    std::size_t *use;
};

int main()
{
    HasPtr hp1("Hellp");
    HasPtr hp2 = hp1;

    return 0;
}