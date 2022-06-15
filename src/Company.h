#ifndef COMPANY_H
#define COMPANY_H

#include "Employee.h"
#include "AVLTree.h"
#include "HashTable.h"

class Company
{
    int companyID;
    int value;
    int num_of_employees;
    Employee *highest_earner;
    HashTable<Employee *> employees;
    AVLTree<Employee *> employees_tree_by_salary;
    // double factor;
    // double parent_value_at_purchase;
    int interns_employees_count;
    int interns_grade_sum;

public:
    Company() = default;
    Company(int companyID, int value);
    int getCompanyID() const;
    int getValue() const;
    int getNumOfEmployees() const;
    AVLTree<Employee *> *getEmployeesTree();
    AVLTree<Employee *> *getEmployeesTreeBySalary();
    Employee *getHighestEarner();
    void setCompanyID(int newID);
    void setValue(int value);
    void setHighesEarner(Employee *emp);
    void addEmployee(Employee *employee);
    void removeEmployee(Employee *employee);
    void merge(Company *company, double factor);
    double getFactor() const;
    void setFactor(double factor);
    double getParentValueAtPurchase() const;
    void setParentValueAtPurchase(double parent_value_at_purchase);
    bool operator<(const Company &other) const;
    bool operator>(const Company &other) const;
    bool operator==(const Company &other) const;
    bool operator!=(const Company &other) const;
    long long SumOfBumpGradeBetweenTopWorkersByGroup(int m);
    static bool compareByPointer(Company *const &a, Company *const &b);
    HashTable<Employee *> *getEmployees();
    void upgradeIntern(Employee *employee);
    int getInternsEmployeesCount() const;
    int getInternsGradeSum() const;
    void increaseInternsGradeSum(int bumpGrade);

private:
    void transferEmployees(Company *new_company, Node<Employee *> *current);
};

#endif