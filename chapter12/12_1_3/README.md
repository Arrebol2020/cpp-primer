## 练习 12.10
不正确。p 已经是一个 shared_ptr<int>，将 p 传递给另一个临时的 shared_ptr<int> 是多余操作，且可能导致不必要的引用此书增加和减少。直接将 p 传递个 process 函数即可。
题目中代码可以正常运行，是因为`shared_ptr`具有复制语义

## 练习 12.11
会导致内存重复释放，因为 `shared_ptr<int>(p.get())` 也对 p 的资源进行管理，这样当 process 结束时，`临时的 shared_ptr 会释放 p 的资源，而程序结束时，p 也会去释放资源，此时 p 的资源已经被释放完，所指向的地址就是非法的，这会导致重复释放内存错误`

## 练习 12.12
```c++
auto p = new int();
auto sp = make_shared<int>();

process(sp);  // 成功，直接使用 sp 作为参数
process(new int());  // 失败，shared_ptr 不能将一个内置指针隐式转化为一个智能指针
process(p);  // 失败，shared_ptr 不能将一个内置指针隐式转化为一个智能指针
process(shared_ptr<int>(p)); // 成功，使用 p 来生成一个临时 shared_ptr 变量 
```

## 练习 12.13
``` c++
auto sp = std::make_shared<int>();
auto p = sp.get();
delete p;
```
会出现重复释放内存错误，因为 `delete p` 已经将 sp 管理的内存给释放掉，当 shared_ptr 尝试去释放时，会出现重复释放同一个内存的错误。