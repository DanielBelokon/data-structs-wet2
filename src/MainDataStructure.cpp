#include "MainDataStructure.h"

MainDataStructure::MainDataStructure(int k) : companies(k + 1), employees()
{
    // TODO: implement this
    this->num_of_companies = k;
    this->interns_employees_count = 0;
    this->interns_grade_sum = 0;
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

    employees.insert(employeeID, employee);
    company->addEmployee(employee);
    interns_employees_count++;
    interns_grade_sum += grade;
}

void MainDataStructure::RemoveEmployee(int employeeID)
{
    if (employeeID <= 0)
    {
        throw InvalidInputException();
    }

    Employee *employee = findEmployeeById(employeeID);
    Company *company = employee->getCompany();
    company = findCompanyById(company->getCompanyID());
    company->removeEmployee(employee);
    if (employee->getSalary() != 0)
    {
        employees.remove(employeeID);
        employees_tree_by_salary.remove(employee);
    }
    else
    {
        interns_employees_count--;
        interns_grade_sum -= employee->getGrade();
        company->upgradeIntern(employee);
    }
    // delete employee;
}

bool MainDataStructure::AcquireCompany(int companyID, int acquiredCompanyID, double factor)
{
    if (companyID <= 0 || acquiredCompanyID <= 0 || acquiredCompanyID > num_of_companies || companyID > num_of_companies || factor <= 0 || companyID == acquiredCompanyID)
    {
        throw InvalidInputException();
    }

    Company *company = findCompanyById(companyID);
    Company *acquiredCompany = findCompanyById(acquiredCompanyID);
    if (company == acquiredCompany)
    {
        throw InvalidInputException();
    }
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
    int prevSalary = employee->getSalary();
    Company *company = employee->getCompany();

    employees_tree_by_salary.remove(employee);
    company->getEmployeesTreeBySalary()->remove(employee);

    employee->increaseSalary(salaryIncrease);

    if (employee->getSalary() > 0)
    {
        employees_tree_by_salary.insert(employee, employee->getGrade());
        company->getEmployeesTreeBySalary()->insert(employee, employee->getGrade());
        if (prevSalary == 0)
        {
            company->upgradeIntern(employee);
            interns_employees_count--;
            interns_grade_sum -= employee->getGrade();
        }
    }
}

void MainDataStructure::PromoteEmployee(int employeeID, int bumpGrade)
{
    if (employeeID <= 0)
        throw InvalidInputException();

    Employee *employee = findEmployeeById(employeeID);

    if (bumpGrade > 0)
        employee->increaseGrade(bumpGrade);

    if (employee->getSalary() == 0)
    {
        if (bumpGrade > 0)
        {
            interns_grade_sum += bumpGrade;
            employee->getCompany()->increaseInternsGradeSum(bumpGrade);
        }
        return;
    }
    employees_tree_by_salary.remove(employee);
    employees_tree_by_salary.insert(employee, employee->getGrade());
    Company *company = employee->getCompany();
    Company *other = findCompanyById(company->getCompanyID());
    if (company->getCompanyID() != other->getCompanyID())
    {
        findCompanyById(company->getCompanyID());
    }
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

    printf("SumOfBumpGradeBetweenTopWorkersByGroup: %d\n", sum);
    return sum;
}

void MainDataStructure::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary)
{
    if (companyID < 0 || companyID > num_of_companies || lowerSalary < 0 || higherSalary < 0 || higherSalary < lowerSalary)
    {
        throw InvalidInputException();
    }
    AVLTree<Employee *> *tree;
    bool include_zero_salary = (lowerSalary == 0);
    int rank_sum = 0, worker_count = 0;
    Company *company;
    if (companyID == 0)
    {
        tree = &employees_tree_by_salary;
    }
    else
    {
        company = findCompanyById(companyID);
        tree = company->getEmployeesTreeBySalary();
    }

    // calculate sum and amount in range between salaried workers
    // find minimum salaried node that is close to range?
    if (higherSalary != 0 && tree->getSize() != 0)
    {
        int minAmount = 0, maxAmount = 0;
        Employee temp_min_emp = Employee(0, nullptr, lowerSalary, 0);
        Node<Employee *> *min_emp_node;
        Node<Employee *> *node = tree->findNode(&temp_min_emp, &min_emp_node);
        min_emp_node = (node != nullptr) ? node : min_emp_node;
        rank_sum -= tree->getRank(min_emp_node->getData(), &minAmount);
        // if the minimun not in our range
        if (min_emp_node->getData()->getSalary() >= lowerSalary)
        {
            rank_sum += min_emp_node->getRank();
            minAmount--;
        }

        Employee temp_max_emp = Employee(INT32_MAX, nullptr, higherSalary, 0);
        Node<Employee *> *max_emp_node;
        Node<Employee *> *node2 = tree->findNode(&temp_max_emp, &max_emp_node);
        max_emp_node = (node2 != nullptr) ? node2 : max_emp_node;
        rank_sum += tree->getRank(max_emp_node->getData(), &maxAmount);
        if (max_emp_node->getData()->getSalary() > higherSalary)
        {

            rank_sum -= max_emp_node->getRank();
            maxAmount--;
        }

        worker_count += (maxAmount - minAmount);
    }

    if (include_zero_salary)
    {
        if (companyID == 0)
        {
            rank_sum += interns_grade_sum;
            worker_count += interns_employees_count;
        }
        else
        {
            rank_sum += company->getInternsGradeSum();
            worker_count += company->getInternsEmployeesCount();
        }
    }

    if (worker_count <= 0)
        throw EmployeeNotFoundException();
    printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", rank_sum / (double)worker_count);
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
    {
        printf("CompanyValue: %.1f\n", (double)parentCompany->getValue());
        return company->getValue();
    }
    printf("CompanyValue: %.1f\n", parentCompany->getValue() - company->getParentValueAtPurchase() + company->getValue());
    return parentCompany->getValue() - company->getParentValueAtPurchase() + company->getValue();
}

void MainDataStructure::BumpGradeToEmployees(int lowerSalary, int higherSalary, int bumpGrade)
{
}

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
