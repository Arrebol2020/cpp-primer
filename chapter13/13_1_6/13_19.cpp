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