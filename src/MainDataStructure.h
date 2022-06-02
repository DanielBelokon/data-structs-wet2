// this is the main system

#ifndef MAINDATASTRCTURE_H
#define MAINDATASTRCTURE_H
#include "Company.h"
#include "Employee.h"
#include "AVLTree.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "Exceptions.h"

class MainDataStructure
{

private:
    // AVLTree<Company *> companies_tree;
    // AVLTree<Company *> companies_with_employees_tree;
    // AVLTree<Employee *> employees_tree;
    // AVLTree<Employee *> employees_tree_by_salary;
    // Employee *highest_earner;
    UnionFind<Company *> companies;
    HashTable<Employee *> employees;
    AVLTree<Employee *> employees_tree_by_salary;
    int num_of_companies;

public:
    MainDataStructure(int k);
    void AddCompany(int companyID, int value);
    void AddEmployee(int employeeID, int companyID, int grade);
    void RemoveEmployee(int employeeID);
    bool AcquireCompany(int companyId, int aquiredCompanyId, double factor);
    void EmployeeSalaryIncrease(int employeeID, int salaryIncrease);
    void PromoteEmployee(int EmployeeID, int bumpGrade);
    int SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m);
    void AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary, void **averageBumpGrade);
    double companyValue(int compnayID);
    void BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade); // BONUS
    ~MainDataStructure();

    // void RemoveCompany(int companyID, bool force = false);
    // void HireEmployee(int EmployeeID, int newCompanyID);
    // int GetHighestEarner(int companyId);
    // void setHighesEarner(Employee *emp);
    // int GetAllEmployeesBySalary(int companyId, int **employees); // returns num of employees
    // void GetHighestEarnerInEachCompany(int numOfCompanies, int **highestEarners);
    // int GetNumEmployeesMatching(int companyId, int minId, int maxId, int minSalary, int minGrad, int *inRange);

    // void GetCompanyInfo(int companyId, int *value, int *numOfEmployees);
    // void GetEmployeeInfo(int employeeID, int *employerID, int *salary, int *grade);
    // void IncreaseCompanyValue(int companyID, int valueIncrease);
private:
    // void checkInRangeRocourisve(Node<Employee *> *current, int minId, int maxId, int minSalary, int minGrade, int *inRange, int *numOfEmployees);
    Company *findCompanyById(int id);
    Employee *findEmployeeById(int id);
};

#endif