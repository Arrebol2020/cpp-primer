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