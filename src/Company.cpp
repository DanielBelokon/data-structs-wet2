#include "Company.h"

Company::Company(int companyID, int value) : companyID(companyID), value(value)
{
    num_of_employees = 0;
    highest_earner = nullptr;
    employees = HashTable<Employee *>();
    factor = 0;
    parent_value_at_purchase = 0;
    employees_tree_by_salary = AVLTree<Employee *>(Employee::compareBySalary);
    interns_employees_count = 0;
    interns_grade_sum = 0;
};

int Company::getCompanyID() const
{
    return companyID;
}

int Company::getValue() const
{
    return value;
}

int Company::getNumOfEmployees() const
{
    return num_of_employees;
}

Employee *Company::getHighestEarner()
{
    return highest_earner;
}

void Company::setCompanyID(int newID)
{
    companyID = newID;
}

void Company::setValue(int value)
{
    this->value = value;
}

void Company::addEmployee(Employee *employee)
{
    num_of_employees++;
    this->employees.insert(employee->getEmployeeID(), employee);
    if (employee->getSalary() == 0)
    {
        this->interns_employees_count++;
        this->interns_grade_sum += employee->getGrade();
    }

    // employees_tree.insert(employee);
    // employees_tree_by_salary.insert(employee);
}

// function to change the data of employees that  is not Used anymore by is cruel manager
void Company::upgradeIntern(Employee *employee)
{
    if (employee->getSalary() == 0)
    {
        interns_employees_count--;
        interns_grade_sum -= employee->getGrade();
    }
}

void Company::removeEmployee(Employee *employee)
{
    // employees_tree.remove(employee);
    employees.remove(employee->getEmployeeID());

    employees_tree_by_salary.remove(employee);
    upgradeIntern(employee);

    num_of_employees--;
    if (employee == highest_earner) // if this employee was the richest
    {
        if (this->getNumOfEmployees() > 0)
        {
            highest_earner = employees_tree_by_salary.getHighest(); // set new one.
        }
        else
        {
            highest_earner = nullptr; // no employee in the company
        }
    }
}

void Company::merge(Company *company, double factor)
{
    if (company == nullptr || company == this)
        return;

    num_of_employees += company->getNumOfEmployees();
    this->setValue(factor * (company->getValue()) + this->getValue());

    // company->updateIds(this->getCompanyID(), company->getEmployeesTree()->getRoot());
    // company->transferEmployees(this, company->getEmployeesTree()->getRoot());
    // employees_tree.merge(company->getEmployeesTree());

    // TODO: Transfer employees to new company
    HashTable<Employee *> *targetEmployees = company->getEmployees();
    for (auto emp : *targetEmployees)
    {
        if (emp != nullptr)
        {
            emp->setCompany(this);
            targetEmployees->remove(emp->getEmployeeID());
            this->addEmployee(emp);
        }
    }

    this->employees_tree_by_salary.merge(company->getEmployeesTreeBySalary());
    setHighesEarner(company->getHighestEarner());
}

// void Company::transferEmployees(Company *new_company, Node<Employee *> *current)
// {
//     if (current == nullptr)
//         return;

//     current->getData()->setCompany(new_company);
//     transferEmployees(new_company, current->getLeft());
//     transferEmployees(new_company, current->getRight());
// }

AVLTree<Employee *> *Company::getEmployeesTreeBySalary()
{
    return &employees_tree_by_salary;
}

bool Company::compareByPointer(Company *const &a, Company *const &b)
{
    return a->getCompanyID() < b->getCompanyID();
}
HashTable<Employee *> *Company::getEmployees()
{
    return &employees;
}
int Company::SumOfBumpGradeBetweenTopWorkersByGroup(int m)
{
    return employees_tree_by_salary.getHighestMRankSum(m);
}
double Company::getFactor() const
{
    return factor;
}

double Company::getParentValueAtPurchase() const
{
    return parent_value_at_purchase;
}

void Company::setParentValueAtPurchase(double parent_value_at_purchase)
{
    this->parent_value_at_purchase = parent_value_at_purchase;
}
void Company::setFactor(double factor)
{
    this->factor = factor;
}
int Company::getInternsEmployeesCount() const
{
    return interns_employees_count;
}
int Company::getInternsGradeSum() const
{
    return interns_grade_sum;
}
void Company::increaseInternsGradeSum(int bumpGrade)
{
    interns_grade_sum += bumpGrade;
}