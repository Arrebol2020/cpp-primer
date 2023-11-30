## 练习 13.1
拷贝构造函数是通过一个已有的对象，去创建一个新的对象。
一般会在：
- 使用一个对象初始化另一个同类对象
- 将一个对象作为函数参数传递给函数，并且该参数是按值传递的
- 从函数返回一个对象，如果返回值是按值传递的

## 练习 13.2
``` c++
Sales_data::Sales_data(Sales_data rhs);
```
上述代码中，当使用
``` c++
Sales_data sd1;
Sales_data sd2(sd1);
```
时，会出现无限循环调用 `Sales_data::Sales_data(Sales_data rhs);`，为了调用该函数，必须拷贝它的实参，但为了拷贝实参，又要调用该函数，就出现了无限循环

## 练习 13.3
在 StrBlob 中，没有显示定义拷贝构造函数，因此`编译器会提供一个默认的浅拷贝构造函数`。当拷贝 `StrBlob` 对象时，它会简单地逐个复制每个成员变量的值，包括 `shared_ptr` 会增加引用计数，但是不会复制底层的 vector

在 StrBlob 中，也没有显示定义拷贝构造函数，因此`编译器会提供一个默认的浅拷贝构造函数`。当拷贝 `StrBlobStr` 对象时，会简单的复制指针和其它成员变量，而不会深度复制其指向的数据

## 练习 13.4
``` c++
Point global;
Point foo_bar(Point arg)
{
    Point local = arg, *heap = new Point(global);
    *heap = local;
    Point pa[4] = {local, *heap};
    return *heap;
}
```
上述代码片段中，以下地方使用了拷贝构造函数：
- 当调用 函数 `Point foo_bar(Point arg)` 时
- `Point local = arg` ，拷贝构造函数使用 arg 初始化 local 对象
- `Point pa[4] = {local, *heap};` ，在这行代码中，数组 pa 中的两个元素通过拷贝构造函数初始化。local 和 *heap 被拷贝到数组元素中。
- `return *heap;`，*heap 对象被复制到调用 'foo_bar' 的上下文中


## 练习 13.5
``` c++
class HasPtr
{
public:
    HasPtr(const std::string& s = std::string()) :
        ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr& rhs)
    {
        ps(new std::string(*rhs.ps));
        i(rhs.i);
    }
private:
    std::string *ps;
    int i;
}
```