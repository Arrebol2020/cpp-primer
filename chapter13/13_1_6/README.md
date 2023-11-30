## 练习 13.18
``` c++
#include <iostream>

class Employee
{
public:
    Employee() : name(""), employeeID(uniqueID++) {}
    Employee(const std::string& n) : name(n), employeeID(uniqueID++) {}

    const std::string& getName() const { return name; }
    int getId() const { return employeeID; }
    
private:
    std::string name;
    int employeeID;
    static int uniqueID;
};

int Employee::uniqueID = 1;
int main()
{
    Employee e1;
    Employee e2("Arrebol");
    Employee e3(e1);
    e1 = e2;

    std::cout << "Employee Name: " << e1.getName() << ", ID: " << e1.getId() << std::endl;
    std::cout << "Employee Name: " << e2.getName() << ", ID: " << e2.getId() << std::endl;
    std::cout << "Employee Name: " << e3.getName() << ", ID: " << e3.getId() << std::endl;
    return 0;
}
```

## 练习 13.19
需要，因为 Employee 需要唯一的雇员证号，`默认的拷贝构造函数会导致两个实例的雇员证号相同`，这与我们目的不同，因此需要重写拷贝构造函数和拷贝赋值函数
``` c++
#include <iostream>

class Employee
{
public:
    Employee() : name(""), employeeID(uniqueID++) {}
    Employee(const std::string& n) : name(n), employeeID(uniqueID++) {}

    Employee(const Employee& other) : name(other.name), employeeID(uniqueID++) {}
    Employee& operator=(const Employee& other)
    {
        if (&other == this) return *this;
        name = other.name;
        employeeID = uniqueID++;
        return *this;
    }

    const std::string& getName() const { return name; }
    int getId() const { return employeeID; }
    
private:
    std::string name;
    int employeeID;
    static int uniqueID;
};

int Employee::uniqueID = 1;
int main()
{
    Employee e1;
    Employee e2("Arrebol");
    Employee e3(e1);
    e1 = e2;

    std::cout << "Employee Name: " << e1.getName() << ", ID: " << e1.getId() << std::endl;
    std::cout << "Employee Name: " << e2.getName() << ", ID: " << e2.getId() << std::endl;
    std::cout << "Employee Name: " << e3.getName() << ", ID: " << e3.getId() << std::endl;
    return 0;
}
```