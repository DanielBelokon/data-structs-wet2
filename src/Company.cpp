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
}

// function to change the data of employees that  is not Used anymore by is cruel manager
void Company::upgradeIntern(Employee *employee)
{

    interns_employees_count--;
    interns_grade_sum -= employee->getGrade();
    return;
}

void Company::removeEmployee(Employee *employee)
{
    // employees_tree.remove(employee);
    if (employee->getSalary() != 0)
        employees_tree_by_salary.remove(employee);
    // else
    //     upgradeIntern(employee);

    num_of_employees--;
}

void Company::merge(Company *company, double factor)
{
    if (company == nullptr || company == this)
        return;

    num_of_employees += company->getNumOfEmployees();
    this->setValue(factor * (company->getValue()) + this->getValue());

    // TODO: Transfer employees to new company
    HashTable<Employee *> *targetEmployees = company->getEmployees();
    employees.merge(targetEmployees);

    for (auto emp : employees)
    {
        if (emp != nullptr)
        {
            emp->setCompany(this);
            // this->addEmployee(emp);
            // targetEmployees->remove(emp->getEmployeeID());
            // if (emp->getSalary() > 0)
            //     employees_tree_by_salary.insert(emp);
        }
    }
    this->interns_employees_count += company->getInternsEmployeesCount();
    this->interns_grade_sum += company->getInternsGradeSum();
    this->employees_tree_by_salary.merge(company->getEmployeesTreeBySalary());
}

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
long long Company::SumOfBumpGradeBetweenTopWorkersByGroup(int m)
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
    if (bumpGrade < 0)
        return;
    interns_grade_sum += bumpGrade;
}