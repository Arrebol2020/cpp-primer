## 练习 12.14
能力有限，没想到其它方式，用的原文
``` c++
struct destination;
struct connection;
connection connect(destination*);
void disconect(connection);

void end_connection(connection *p) {disconect(*p);}
void f(destination& d)
{
    connection c = connect(&d);
    std::shared_ptr<connection, end_connection> p(&c);
}
```

## 练习 12.15
``` c++
struct destination;
struct connection;
connection connect(destination*);
void disconect(connection);

void f(destination& d)
{
    connection c = connect(&d);
    std::shared_ptr<connection> p(&c, [](connection* p) { disconect(*p); });
}
```