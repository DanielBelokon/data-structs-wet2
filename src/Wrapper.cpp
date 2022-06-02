#include "library2.h"
#include <exception>
#include "MainDataStructure.h"

StatusType ExceptionToEnum(std::exception &e);

void *Init(int k)
{
    MainDataStructure *ds = new MainDataStructure(k);
    return ds;
}

StatusType AddCompany(void *DS, int CompanyID, int Value)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->AddCompany(CompanyID, Value);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Grade)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->AddEmployee(EmployeeID, CompanyID, Grade);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType RemoveEmployee(void *DS, int EmployeeID)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->RemoveEmployee(EmployeeID);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        bool success = ((MainDataStructure *)DS)->AcquireCompany(AcquirerID, TargetID, Factor);
        return success ? SUCCESS : FAILURE;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType EmployeeSalaryIncrease(void *DS, int EmployeeID, int salaryIncrease)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->EmployeeSalaryIncrease(EmployeeID, salaryIncrease);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int BumpGrade)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->PromoteEmployee(EmployeeID, BumpGrade);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m, void **sum)
{
    if (DS == NULL || sum == NULL)
        return INVALID_INPUT;
    try
    {
        *(int *)*sum = ((MainDataStructure *)DS)->SumOfBumpGradeBetweenTopWorkersByGroup(companyID, m);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary, void **averageBumpGrade)
{
    if (DS == NULL || averageBumpGrade == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->AverageBumpGradeBetweenSalaryByGroup(companyID, lowerSalary, higherSalary, averageBumpGrade);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType CompanyValue(void *DS, int CompanyID, void **Value)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->companyValue(CompanyID);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}
void Quit(void **DS)
{
    MainDataStructure *ds = (MainDataStructure *)*DS;
    delete ds;
    *DS = nullptr;
}

StatusType ExceptionToEnum(std::exception &ex)
{
    if (dynamic_cast<InvalidInputException *>(&ex))
    {
        return INVALID_INPUT;
    }
    else if (dynamic_cast<CompanyAlreadyExistsException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<CompanyNotFoundException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<CompanyHasEmployeesException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<EmployeeAlreadyExistsException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<EmployeeNotFoundException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<std::bad_alloc *>(&ex))
    {
        return ALLOCATION_ERROR;
    }
    else
    {
        return FAILURE;
    }
}