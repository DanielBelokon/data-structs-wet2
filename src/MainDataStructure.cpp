#include "MainDataStructure.h"

MainDataStructure::MainDataStructure()
{
}

void MainDataStructure::AddCompany(int companyID, int value)
{
    if (companyID <= 0 || value <= 0)
    {
        throw InvalidInputException();
    }
    Company *company = new Company(companyID, value);

    if (companies_tree.find(company) != nullptr)
    {
        delete company;
        throw CompanyAlreadyExistsException();
    }
    companies_tree.insert(company);
}

void MainDataStructure::AddEmployee(int employeeID, int companyID, int grade)
{
    if (companyID <= 0 || employeeID <= 0 || companyID > num_of_companies || grade < 0)
    {
        throw InvalidInputException();
    }

    Company *company = findCompanyById(companyID);
    Employee *employee = new Employee(employeeID, company, 0, grade);
    if (employees[employeeID] != nullptr)
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
    employees_tree_by_salary.insert(employee);
}

void MainDataStructure::PromoteEmployee(int employeeID, int bumpGrade)
{
    if (employeeID <= 0)
        throw InvalidInputException();

    Employee *employee = findEmployeeById(employeeID);

    if (bumpGrade > 0)
        employee->increaseGrade();

    employees_tree_by_salary.remove(employee);
    employees_tree_by_salary.insert(employee);
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
    return;
}

void MainDataStructure::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary, void *averageBumpGrade)
{
}

void MainDataStructure::companyValue(int compnayID, void *standing)
{
}
void MainDataStructure::BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade)
{
}

void MainDataStructure::checkInRangeRocourisve(Node<Employee *> *current, int minId, int maxId, int minSalary, int minGrade, int *inRange, int *numOfEmployees)
{
    if (current == nullptr)
        return;

    if (current->getData()->getEmployeeID() >= minId && current->getData()->getEmployeeID() <= maxId)
    {
        (*inRange)++;
        if (current->getData()->getSalary() >= minSalary && current->getData()->getGrade() >= minGrade)
        {
            (*numOfEmployees)++;
        }
    }

    if (current->getData()->getEmployeeID() >= minId)
        checkInRangeRocourisve(current->getLeft(), minId, maxId, minSalary, minGrade, inRange, numOfEmployees);
    if (current->getData()->getEmployeeID() <= maxId)
        checkInRangeRocourisve(current->getRight(), minId, maxId, minSalary, minGrade, inRange, numOfEmployees);
}

Company *MainDataStructure::findCompanyById(int id)
{
    Company *result = this->companies.find(id);
    if (result == nullptr)
        throw CompanyNotFoundException();
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
    Employee **employees = employees_tree.getInOrderArray();
    for (int i = 0; i < employees_tree.getSize(); i++)
    {
        delete employees[i];
    }
    delete[] employees;

    Company **companies = companies_tree.getInOrderArray();
    for (int i = 0; i < companies_tree.getSize(); i++)
    {
        delete companies[i];
    }
    delete[] companies;
}
