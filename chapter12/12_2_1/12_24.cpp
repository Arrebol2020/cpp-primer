#include <iostream>
#include <cstring>

int main() {
    const int initialSize = 10; // 初始数组大小
    int capacity = initialSize; // 当前容量大小
    char* str = new char[capacity]; // 分配初始大小的数组

    int length = 0; // 记录已读取的字符数

    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        // 如果数组已满，重新分配更大的内存
        if (length == capacity - 1) {
            capacity *= 2; // 扩大容量
            char* newStr = new char[capacity]; // 分配新的更大数组
            strcpy(newStr, str); // 复制原字符串到新数组
            delete[] str; // 释放原数组的内存
            str = newStr; // 指向新数组
        }

        // 将字符存入数组
        str[length] = ch;
        ++length;
    }

    // 添加字符串结束符
    str[length] = '\0';

    std::cout << str << std::endl;

    delete[] str; // 释放内存

    return 0;
}
