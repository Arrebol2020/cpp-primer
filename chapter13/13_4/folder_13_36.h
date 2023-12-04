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