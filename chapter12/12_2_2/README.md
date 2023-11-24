## 练习：12.26
``` c++
#include <iostream>
#include <memory>

int main()
{
    std::allocator<int> alloc;
    auto p = alloc.allocate(10);

    auto q = p;

    for (int i = 0; i < 10; i++)
    {
        alloc.construct(q++, i);
    }

    auto r = p;
    while (q != r)
    {
        std::cout << *r << " ";
        alloc.destroy(r++);
    }

    alloc.deallocate(p, 10);
    std::cout << std::endl;
    return 0;
}
```