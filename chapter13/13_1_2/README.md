## 练习 13.6
定义：拷贝赋值函数是用一个类对象的实例去赋值给另一个类对象的实例。

什么时候使用：当执行类似 `a = b;` 的赋值操作时，其中 a 和 b 是同一类的渡西iang，赋值运算符被调用

什么时候完成工作：合成的拷贝赋值运算符负责按成员变量顺序执行浅复制操作，对于自定义类型需要注意可能存在浅拷贝问题。

什么时候生成：类没有显示定义自己的拷贝赋值运算符或移动赋值运算符

## 练习 13.7
对于 StrBlob，会调用默认的赋值构造函数，左边的 StrBlob 的 data 会使 `shared_ptr` 加1，和右边的 StrBlob 的 data 共享同一个底层数据。

对于 StrBlobStr，会调用默认的赋值构造函数，会执行浅拷贝，即复制 wptr 和 curr 成员变量的值。

## 练习 13.8
``` c++
class HasPtr
{
public:
    HasPtr(const std::string& s = std::string()) :
        ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr& rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) { }
    HasPtr& operator=(const HasPtr& rhs)
    {
        if (&rhs == this) return *this;    
        delete ps;

        ps = new std::string(*rhs.ps);
        i = rhs.i;

        return *this;
    }
private:
    std::string *ps;
    int i;
}
```