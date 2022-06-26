#include "MainDataStructure.h"

MainDataStructure::MainDataStructure(int k) : companies(k + 1), employees()
{
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
    if (employees.search(employeeID) != nullptr)
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
    company->removeEmployee(employee);
    employees.remove(employeeID);
    employees_tree_by_salary.remove(employee);

    if (employee->getSalary() == 0)
    {
        interns_employees_count--;
        interns_grade_sum -= employee->getGrade();
        company->upgradeIntern(employee);
    }
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
    if (company->getCompanyID() == acquiredCompany->getCompanyID())
    {
        throw InvalidInputException();
    }
    company->merge(acquiredCompany, factor);
    companies.merge(companyID, acquiredCompanyID, factor);
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

    employees_tree_by_salary.insert(employee, employee->getGrade());

    company->getEmployeesTreeBySalary()->insert(employee, employee->getGrade());
    if (prevSalary == 0)
    {
        company->upgradeIntern(employee);
        interns_employees_count--;
        interns_grade_sum -= employee->getGrade();
    }
}

void MainDataStructure::PromoteEmployee(int employeeID, int bumpGrade)
{
    if (employeeID <= 0)
        throw InvalidInputException();

    Employee *employee = findEmployeeById(employeeID);

    if (bumpGrade > 0)
        employee->increaseGrade(bumpGrade);
    else
        return;
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
    company->getEmployeesTreeBySalary()->remove(employee);
    company->getEmployeesTreeBySalary()->insert(employee, employee->getGrade());
}

int MainDataStructure::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m)
{
    if (companyID < 0 || companyID > num_of_companies || m <= 0)
    {
        throw InvalidInputException();
    }

    unsigned long long sum;

    if (companyID == 0)
    {
        if (employees_tree_by_salary.getSize() < m)
            throw EmployeeNotFoundException();
        sum = employees_tree_by_salary.getHighestMValueSum(m);
    }
    else
    {
        Company *company = findCompanyById(companyID);
        if (company->getEmployeesTreeBySalary()->getSize() < m)
            throw EmployeeNotFoundException();
        sum = company->SumOfBumpGradeBetweenTopWorkersByGroup(m);
    }

    printf("SumOfBumpGradeBetweenTopWorkersByGroup: %lld\n", sum);
    return sum;
}

void MainDataStructure::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary)
{
    if (companyID < 0 || companyID > num_of_companies || lowerSalary < 0 || higherSalary < 0 || higherSalary < lowerSalary)
    {
        throw InvalidInputException();
    }
    AVLTree<Employee *> *tree;
    unsigned long long rank_sum = 0, worker_count = 0;
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
    // find minimum salaried node that is close to range
    if (higherSalary != 0 && tree->getSize() != 0)
    {
        int minAmount = 0, maxAmount = 0;
        Employee temp_min_emp = Employee(0, nullptr, lowerSalary, 0);
        Node<Employee *> *min_emp_node;
        Node<Employee *> *node = tree->findNode(&temp_min_emp, &min_emp_node);
        min_emp_node = (node != nullptr) ? node : min_emp_node;
        rank_sum -= tree->getValueSumUpto(min_emp_node->getData(), &minAmount);
        // if the minimum not in our range
        if (min_emp_node->getData()->getSalary() >= lowerSalary)
        {
            rank_sum += min_emp_node->getNodeValue();
            minAmount--;
        }

        Employee temp_max_emp = Employee(INT32_MAX, nullptr, higherSalary, 0);
        Node<Employee *> *max_emp_node;
        Node<Employee *> *node2 = tree->findNode(&temp_max_emp, &max_emp_node);
        max_emp_node = (node2 != nullptr) ? node2 : max_emp_node;
        rank_sum += tree->getValueSumUpto(max_emp_node->getData(), &maxAmount);
        if (max_emp_node->getData()->getSalary() > higherSalary)
        {
            rank_sum -= max_emp_node->getNodeValue();
            maxAmount--;
        }

        worker_count += (maxAmount - minAmount);
    }

    if (lowerSalary == 0)
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
    // TODO: replace print for final submission
    if (worker_count <= 0)
        throw EmployeeNotFoundException();
    long double testing_value = std::round((rank_sum / (long double)worker_count) * 10.0) / 10.0;
    printf("AverageBumpGradeBetweenSalaryByGroup: %.1Lf\n", testing_value); // rank_sum / (double)worker_count);
}

double MainDataStructure::companyValue(int compnayID)
{
    if (compnayID <= 0 || compnayID > num_of_companies)
    {
        throw InvalidInputException();
    }
    printf("CompanyValue: %.1Lf\n", companies.getValue(compnayID));
    return 0;
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
    for (Employee *emp : employees)
    {
        delete emp;
    }

    for (int i = 1; i <= num_of_companies; i++)
    {
        delete companies.findObject(i);
    }
}
