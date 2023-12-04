## 练习 13.33
因为我们想要修改的是 `Message` 对象所涉及的 Folder 集合，若使用 `Folder 类型或 const Folder&`，向让 `Folder` 添加/删除 Message 时，将无法实现。

## 练习 13.34
``` c++
#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <set>

class Folder;
class Message
{
    friend class Folder;
    friend void swap(Message& lhs, Message& rhs);
public:
    // folders 被隐式初始化为空集合
    explicit Message(const std::string& str="") : contents(str) {}
    // 拷贝控制成员，用来管理指向本 Message 的指针
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    // 从给定 Folder 集合中添加/删除本 Message
    void save(Folder&);
    void remove(Folder&);
private:
    std::string contents;  // 实际消息文本
    std::set<Folder*> folders;  // 包含本 Message 的 Folder
    // 拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
    // 将本 Message 添加到指向参数的 Folder 中
    void add_to_Folders(const Message&);
    // 从 folders 中的每个 Folder 中删除本 Message
    void remove_from_Folders();
};

void Message::save(Folder& f)
{
    folders.insert(&f);  // 将给定 Folder 添加到我们的 Folder 列表中
    f.addMsg(this);  // 将本 Message 添加到 f 的 Message 集合中
}

void Message::remove(Folder& f)
{
    folders.erase(&f);
    f.remMsg(this);  // 将本 Message 从 f 的 Message 集合中删除
}

// 将本 Message 添加到指向 m 的 Folder 中
void Message::add_to_Folders(const Message& m)
{
    for (auto f : m.folders)  // 对每个包含 m 的 Folder
        f->addMsg(this);  // 向该 Folder 添加一个指向本 Message 的指针
}

Message::Message(const Message& m) :
    contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}

// 从对应的 FOlder 中删除本 Message
void Message::remove_from_Folders()
{
    for (auto f : folders)  // 对 floders 中每个指针
        f->remMsg(this);  // 从该 FOlder 中删除本 Message
}

Message::~Message()
{
    remove_from_Folders();
}


Message& Message::operator=(const Message& rhs)
{
    // 通过先删除指针再插入它们来处理自赋值的情况
    remove_from_Folders();  // 更新已有 Folder
    contents = rhs.contents;  // 从 rhs 拷贝消息内容
    folders = rhs.folders;  // 从 rhs 拷贝 Folder 指针
    add_to_Folders(rhs);  // 将本 Message 添加到那些 Folder 中
    return *this;
}

void swap(Message& lhs, Message& rhs)
{
    using std::swap;  // 在本例中严格来说并不需要，但这是一个好习惯
    // 将每个消息的指针从 它(原来)所在 Folder 中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    // 交换 contents 和 Folder 指针 set
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    // 将每个 Message 的指针添加到它的新 Folder 中
    for (auto f: lhs.folders)
        f->addMsg(&lhs);
    for (auto f: rhs.folders)
        f->addMsg(&rhs);
}

#endif
```

## 练习 13.35
可能会出现：Message 与 Folder 对应，但是 Folder 没有与相应的 Message 对应。并且对于 `folders` 这样的成员，它会直接复制指针集合，这将导致两个 `Message` 对象共享相同的 `folders` 集合，即两个对象指向同一个集合的内容。这可能导致错误的行为

## 练习 13.36
``` c++
#ifndef FOLDER_H
#define FOLDER_H
#include <set>
#include "message_13_34.h"

class Folder
{
public:
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();
    void addMsg(Message* msg);
    void remMsg(Message* msg);
private:
    std::set<Message*> messages;
    void add_to_Messages(const Folder&);
    void remove_from_Messages();
};

void Folder::add_to_Messages(const Folder& rhs)
{
    for (auto m : rhs.messages)
        m->addFolder(this);
}

void Folder::remove_from_Messages()
{
    for (auto m : messages)
        m->remFolder(this);
}

void Folder::addMsg(Message* msg)
{
    messages.insert(msg);   
    msg->addFolder(this); 
}

void Folder::remMsg(Message* msg)
{
    messages.erase(msg);
    msg->remFolder(this);
}

Folder::Folder(const Folder& rhs) : messages(rhs.messages)
{
    add_to_Messages(rhs);
}

Folder& Folder::operator=(const Folder& rhs)
{
    remove_from_Messages();

    messages = rhs.messages;
    
    add_to_Messages(rhs);

    return *this;
}

Folder::~Folder()
{
    remove_from_Messages();
}

#endif
```

## 练习 13.37
``` c++
#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include "folder_13_36.h"

class Message
{
    friend class Folder;
    friend void swap(Message& lhs, Message& rhs);
public:
    // folders 被隐式初始化为空集合
    explicit Message(const std::string& str="") : contents(str) {}
    // 拷贝控制成员，用来管理指向本 Message 的指针
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    // 从给定 Folder 集合中添加/删除本 Message
    void save(Folder&);
    void remove(Folder&);
    void addFolder(Folder*);
    void remFolder(Folder*);
private:
    std::string contents;  // 实际消息文本
    std::set<Folder*> folders;  // 包含本 Message 的 Folder
    // 拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
    // 将本 Message 添加到指向参数的 Folder 中
    void add_to_Folders(const Message&);
    // 从 folders 中的每个 Folder 中删除本 Message
    void remove_from_Folders();
};

void Message::save(Folder& f)
{
    folders.insert(&f);  // 将给定 Folder 添加到我们的 Folder 列表中
    f.addMsg(this);  // 将本 Message 添加到 f 的 Message 集合中
}

void Message::remove(Folder& f)
{
    folders.erase(&f);
    f.remMsg(this);  // 将本 Message 从 f 的 Message 集合中删除
}

void Message::addFolder(Folder* f)
{
    folders.insert(f);
    f->addMsg(this);
}

void Message::remFolder(Folder* f)
{
    folders.erase(f);
    f->remMsg(this);
}

// 将本 Message 添加到指向 m 的 Folder 中
void Message::add_to_Folders(const Message& m)
{
    for (auto f : m.folders)  // 对每个包含 m 的 Folder
        f->addMsg(this);  // 向该 Folder 添加一个指向本 Message 的指针
}

Message::Message(const Message& m) :
    contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}

// 从对应的 FOlder 中删除本 Message
void Message::remove_from_Folders()
{
    for (auto f : folders)  // 对 floders 中每个指针
        f->remMsg(this);  // 从该 FOlder 中删除本 Message
}

Message::~Message()
{
    remove_from_Folders();
}


Message& Message::operator=(const Message& rhs)
{
    // 通过先删除指针再插入它们来处理自赋值的情况
    remove_from_Folders();  // 更新已有 Folder
    contents = rhs.contents;  // 从 rhs 拷贝消息内容
    folders = rhs.folders;  // 从 rhs 拷贝 Folder 指针
    add_to_Folders(rhs);  // 将本 Message 添加到那些 Folder 中
    return *this;
}

void swap(Message& lhs, Message& rhs)
{
    using std::swap;  // 在本例中严格来说并不需要，但这是一个好习惯
    // 将每个消息的指针从 它(原来)所在 Folder 中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    // 交换 contents 和 Folder 指针 set
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    // 将每个 Message 的指针添加到它的新 Folder 中
    for (auto f: lhs.folders)
        f->addMsg(&lhs);
    for (auto f: rhs.folders)
        f->addMsg(&rhs);
}

#endif
```

## 练习 13.38
拷贝并交换技术需要创建一个临时副本，并进行交换，这种操作可能会增加额外的开销