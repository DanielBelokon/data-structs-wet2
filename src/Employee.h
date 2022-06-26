
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Company;

class Employee
{
    int employee_id;
    unsigned long long salary;
    unsigned long long grade; // the rank of the employee
    Company *company;

public:

    Employee() = default;
    // copyconstructor
    Employee(const Employee &);
    Employee(int employee_id, Company *company, int salary , int grade);
    ~Employee() = default;

    unsigned long long getGrade() const;
    int getSalary() const;
    int getEmployeeID() const;
    int getCompanyID() const;
    Company *getCompany() const;
    void setCompany(Company *company);
    void setGrade(unsigned long long grade);
    void increaseGrade(int bumpGrade);
    void setSalary(int salary);
    void increaseSalary(int salary);

    bool operator<(const Employee &other) const;
    bool operator>(const Employee &other) const;
    bool operator==(const Employee &other) const;
    bool operator!=(const Employee &other) const;
    static bool compareBySalary(Employee *const &temp1, Employee *const &temp2);
    static bool compareByPointer(Employee *const &temp1, Employee *const &temp2);
};

#endif