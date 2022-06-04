#include "MainDataStructure.h"

MainDataStructure::MainDataStructure(int k) : companies(k + 1), employees()
{
    // TODO: implement this
    this->num_of_companies = k;
    this->employees_tree_by_salary = AVLTree<Employee *>(Employee::compareBySalary);
    for (int i = 1; i <= k; i++)
    {
        AddCompany(i, i);
    }
}

void MainDataStructure::AddCompany(int companyID, int value)
{
    if (companyID <= 0 || value <= 0)
    {
        throw InvalidInputException();
    }
    Company *company = new Company(companyID, value);

    if (!companies.isEmpty(companyID))
    {
        delete company;
        throw CompanyAlreadyExistsException();
    }

    companies.makeSet(company, companyID);
}

void MainDataStructure::AddEmployee(int employeeID, int companyID, int grade)
{
    if (companyID <= 0 || employeeID <= 0 || companyID > num_of_companies || grade < 0)
    {
        throw InvalidInputException();
    }

    Company *company = findCompanyById(companyID);
    Employee *employee = new Employee(employeeID, company, 0, grade);
    if (!employees.isEmpty(employeeID))
    {
        delete employee;
        throw EmployeeAlreadyExistsException();
    }

    // employees[employeeID] = employee;
    employees.insert(employeeID, employee);
    company->addEmployee(employee);
}

void MainDataStructure::RemoveEmployee(int employeeID)
{
    if (employeeID <= 0)
    {
        throw InvalidInputException();
    }

    Employee *employee = findEmployeeById(employeeID);
    Company *company = employee->getCompany();

    company->removeEmployee(employee);
    employees.remove(employeeID);
    employees_tree_by_salary.remove(employee);
    delete employee;
}

bool MainDataStructure::AcquireCompany(int companyID, int acquiredCompanyID, double factor)
{
    if (companyID <= 0 || acquiredCompanyID <= 0 || acquiredCompanyID > num_of_companies || companyID > num_of_companies || factor <= 0 || companyID == acquiredCompanyID)
    {
        throw InvalidInputException();
    }

    Company *company = findCompanyById(companyID);
    Company *acquiredCompany = findCompanyById(acquiredCompanyID);

    company->merge(acquiredCompany, factor);
    companies.merge(companyID, acquiredCompanyID);
    acquiredCompany->setFactor(factor);
    acquiredCompany->setParentValueAtPurchase(company->getValue());
    return true;
}

void MainDataStructure::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
{
    if (salaryIncrease <= 0 || employeeID <= 0)
    {
        throw InvalidInputException();
    }

    Employee *employee = findEmployeeById(employeeID);
    employee->increaseSalary(salaryIncrease);
    employees_tree_by_salary.remove(employee);
    employees_tree_by_salary.insert(employee, employee->getGrade());
    Company *company = employee->getCompany();
    company->getEmployeesTreeBySalary()->remove(employee);
    company->getEmployeesTreeBySalary()->insert(employee, employee->getGrade());
}

void MainDataStructure::PromoteEmployee(int employeeID, int bumpGrade)
{
    if (employeeID <= 0)
        throw InvalidInputException();

    Employee *employee = findEmployeeById(employeeID);

    if (bumpGrade > 0)
        employee->increaseGrade(bumpGrade);

    if (employee->getSalary() == 0)
        return;

    employees_tree_by_salary.remove(employee);
    employees_tree_by_salary.insert(employee, employee->getGrade());
    Company *company = employee->getCompany();
    company->getEmployeesTreeBySalary()->remove(employee);
    company->getEmployeesTreeBySalary()->insert(employee, employee->getGrade());
}

int MainDataStructure::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m)
{
    if (companyID < 0 || companyID > num_of_companies || m <= 0)
    {
        throw InvalidInputException();
    }

    int sum;

    if (companyID == 0)
    {
        sum = employees_tree_by_salary.getHighestMRankSum(m);
    }
    else
    {
        Company *company = findCompanyById(companyID);
        sum = company->SumOfBumpGradeBetweenTopWorkersByGroup(m);
    }

    if (sum == 0)
        throw EmployeeNotFoundException();
    return sum;
}

double MainDataStructure::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary)
{
    if (companyID < 0 || companyID > num_of_companies || lowerSalary < 0 || higherSalary < 0 || higherSalary < lowerSalary)
    {
        throw InvalidInputException();
    }
    AVLTree<Employee *> *cur_tree;
    if (companyID == 0)
    {
        cur_tree = &employees_tree_by_salary;
    }
    else
    {
        Company *company = findCompanyById(companyID);
        cur_tree = company->getEmployeesTreeBySalary();
    }

    if (cur_tree->getSize() == 0)
        throw EmployeeNotFoundException();

    Node<Employee *> *max_node;
    Node<Employee *> *min_node;

    Employee tempMinEmp = Employee(0, nullptr, lowerSalary, 0);
    Node<Employee *> *temp_min_node = cur_tree->findNode(&tempMinEmp, &min_node);

    Employee tempMaxEmp = Employee(INT32_MAX, nullptr, higherSalary, 0);
    Node<Employee *> *temp_max_node = cur_tree->findNode(&tempMaxEmp, &max_node);

    min_node = (temp_min_node == nullptr) ? min_node : temp_min_node;
    max_node = (temp_max_node == nullptr) ? max_node : temp_max_node;

    int amt_min, amt_max, rank_min, rank_max;
    rank_min = cur_tree->getRank(min_node->getData(), &amt_min);
    rank_max = cur_tree->getRank(max_node->getData(), &amt_max);
    return ((rank_max - rank_min) / (amt_max - amt_min));
}

double MainDataStructure::companyValue(int compnayID)
{
    if (compnayID < 0 || compnayID > num_of_companies)
    {
        throw InvalidInputException();
    }

    Company *company = companies.findObject(compnayID);
    Company *parentCompany = findCompanyById(compnayID);

    // TODO: why are they sending us a damn void **
    if (company == parentCompany)
        return company->getValue();
    return parentCompany->getValue() - company->getParentValueAtPurchase() + company->getValue();
}

void MainDataStructure::BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade)
{
}

// void MainDataStructure::checkInRangeRocourisve(Node<Employee *> *current, int minId, int maxId, int minSalary, int minGrade, int *inRange, int *numOfEmployees)
// {
//     if (current == nullptr)
//         return;

//     if (current->getData()->getEmployeeID() >= minId && current->getData()->getEmployeeID() <= maxId)
//     {
//         (*inRange)++;
//         if (current->getData()->getSalary() >= minSalary && current->getData()->getGrade() >= minGrade)
//         {
//             (*numOfEmployees)++;
//         }
//     }

//     if (current->getData()->getEmployeeID() >= minId)
//         checkInRangeRocourisve(current->getLeft(), minId, maxId, minSalary, minGrade, inRange, numOfEmployees);
//     if (current->getData()->getEmployeeID() <= maxId)
//         checkInRangeRocourisve(current->getRight(), minId, maxId, minSalary, minGrade, inRange, numOfEmployees);
// }

Company *MainDataStructure::findCompanyById(int id)
{
    if (this->companies.isEmpty(id))
        throw CompanyNotFoundException();
    Company *result = this->companies.find(id);
    return result;
}

Employee *MainDataStructure::findEmployeeById(int id)
{
    Employee *result = this->employees.search(id);
    if (result == nullptr)
        throw EmployeeNotFoundException();
    return result;
}

MainDataStructure::~MainDataStructure()
{
    // Employee **employees = employees_tree.getInOrderArray();
    // for (int i = 0; i < employees_tree.getSize(); i++)
    // {
    //     delete employees[i];
    // }
    // delete[] employees;

    // Company **companies = companies_tree.getInOrderArray();
    // for (int i = 0; i < companies_tree.getSize(); i++)
    // {
    //     delete companies[i];
    // }
    // delete[] companies;
}
