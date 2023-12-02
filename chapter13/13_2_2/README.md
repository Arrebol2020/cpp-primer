## 练习 13.27
``` c++
class HasPtr
{
public:
    HasPtr(const std::string& s = std::string()) :
        ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) use(rhs.use){ ++*use; }
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
}
```

## 练习 13.28
``` c++
#include <iostream>

class TreeNode
{
public:
    // 默认构造函数
    TreeNode(const std::string& val = std::string(), int c = 0,
             TreeNode* l = nullptr, TreeNode* r = nullptr)
        : value(val), count(c), left(l), right(r) {}
    
    TreeNode(const TreeNode& rhs)
        : value(rhs.value), count(rhs.count),
          left(rhs.left ? new TreeNode(*rhs.left) : nullptr),
          right(rhs.right ? new TreeNode(*rhs.right) : nullptr) {}
    TreeNode& operator=(const TreeNode& rhs)
    {
        if (&rhs == this) return *this;

        value = rhs.value;
        count = rhs.count;

        delete left;
        delete right;

        left = rhs.left ? new TreeNode(*rhs.left) : nullptr;
        right = rhs.right ? new TreeNode(*rhs.right) : nullptr;

        return *this;
    }

    ~TreeNode()
    {
        delete left;
        delete right;
    }
private:
    std::string value;
    int count;
    TreeNode* left;
    TreeNode* right;
};


class BinStrTree
{
public:
    BinStrTree() : root(nullptr) {}

    BinStrTree(const BinStrTree& rhs) : root(rhs.root ? new TreeNode(*rhs.root) : nullptr) {}

    BinStrTree& operator=(const BinStrTree& rhs)
    {
        if (this != &rhs)
        {
            delete root;
            root = rhs.root ? new TreeNode(*rhs.root) : nullptr;
        }
        return *this;
    }

    ~BinStrTree()
    {
        delete root;
    }
private:
    TreeNode* root;
};
```