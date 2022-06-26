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
    UnionFind<Company *> companies;
    HashTable<Employee *> employees;
    AVLTree<Employee *> employees_tree_by_salary;
    int num_of_companies;
    int interns_employees_count;
    unsigned long long interns_grade_sum;

public:
    MainDataStructure(int k);
    void AddCompany(int companyID, int value);
    void AddEmployee(int employeeID, int companyID, int grade);
    void RemoveEmployee(int employeeID);
    bool AcquireCompany(int companyId, int aquiredCompanyId, double factor);
    void EmployeeSalaryIncrease(int employeeID, int salaryIncrease);
    void PromoteEmployee(int EmployeeID, int bumpGrade);
    int SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m);
    void AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary);
    double companyValue(int compnayID);
    void BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade); // BONUS
    ~MainDataStructure();

private:
    Company *findCompanyById(int id);
    Employee *findEmployeeById(int id);
};

#endif