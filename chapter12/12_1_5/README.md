## 练习 12.16
```C++
std::unique_ptr<std::string> p1(new std::string("Stegosaurus"));
std::unique_ptr<std::string> p2(p1);
```
无法引用 函数 "std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp> &) [其中 _Tp=std::string, _Dp=std::default_delete<std::string>]" (已声明 所在行数:468，所属文件:"/usr/include/c++/11/bits/unique_ptr.h") -- 它是已删除的函数C/C++(1776)

``` C++
std::unique_ptr<std::string> p3;
p3 = p2;
```
无法引用 函数 "std::unique_ptr<_Tp, _Dp>::operator=(const std::unique_ptr<_Tp, _Dp> &) [其中 _Tp=std::string, _Dp=std::default_delete<std::string>]" (已声明 所在行数:469，所属文件:"/usr/include/c++/11/bits/unique_ptr.h") -- 它是已删除的函数C/C++(1776)

> 上述都是报使用删除的函数，说明 `unique_ptr` 类中，将`赋值构造函数和拷贝构造函数声明为 delete`

## 练习 12.17
``` c++
int ix = 1024, *pi = &ix, *pi2 = new int(2048);
typedef std::unique_ptr<int> IntP;
IntP p0(ix);  // 错误：不能将普通整型变量转化为 unique_ptr
IntP p1(pi);  // 错误：不能将普通指针直接转换为 unique_ptr
IntP p2(pi2);  // 合法：拥有动态分配内存的 unique_ptr
IntP p3(&ix);  // 错误: 不能将指向栈上变量的地址转化为 unique_ptr
IntP p4(new int(2048));  // 合法：使用 new 分配内存的 unique_ptr
IntP p5(p2.get());  // 合法：但是后续可能会出现重复释放指针问题
```

## 练习 12.18
因为 release() 函数作用通常为`将智能指针释放对所管理资源的所有权，并返回向该资源的裸指针`。在 shared_ptr 中，它的所有权是通过引用计数来管理的，使用 release() 可能会导致其它共享指针在不知情情况下，操纵已释放的资源