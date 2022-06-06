#include "Employee.h"
#include "Company.h"
#include<iostream>

Employee::Employee(int employee_id, Company *company, int salary, int grade) : employee_id(employee_id), salary(salary), grade(grade), company(company) {}

// copy constctor
Employee::Employee(const Employee &other) : employee_id(other.employee_id), salary(other.salary), grade(other.grade), company(other.company) {}

bool Employee::compareBySalary(Employee *const &temp1, Employee *const &temp2)
{
    if (temp1->getSalary() < temp2->getSalary())
        return true;
    else if (temp1->getSalary() > temp2->getSalary())
        return false;
    else
        return temp1->getEmployeeID() < temp2->getEmployeeID();
}

bool Employee::compareByPointer(Employee *const &temp1, Employee *const &temp2)
{
    return temp1->getEmployeeID() < temp2->getEmployeeID();
}

int Employee::getGrade() const
{
    return grade;
};

int Employee::getSalary() const
{
    return salary;
}
int Employee::getEmployeeID() const
{
    return employee_id;
}
int Employee::getCompanyID() const
{
    return company->getCompanyID();
}

Company *Employee::getCompany() const
{
    return company;
}

void Employee::setGrade(int grade){
    this->grade = grade;
}

void Employee::setSalary(int salary){
    this->salary = salary;
}

void Employee::increaseSalary(int salary)
{
    this->salary += salary;
}

void Employee::setCompany(Company *company)
{
    this->company = company;
}

void Employee::increaseGrade(int bumpGrade)
{
    this->grade += bumpGrade;
}

bool Employee::operator<(const Employee &other) const
{
    return this->employee_id < other.employee_id;
}

bool Employee::operator==(const Employee &other) const
{
    return this->employee_id == other.employee_id;
}

bool Employee::operator>(const Employee &other) const
{
    return this->employee_id > other.employee_id;
}

bool Employee::operator!=(const Employee &other) const
{
    return this->employee_id != other.employee_id;
}
//