#include "library1.h"
#include <exception>
#include "MainDataStructure.h"

StatusType ExceptionToEnum(std::exception &e);

void *Init()
{
    MainDataStructure *ds = new MainDataStructure();
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

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->AddEmployee(EmployeeID, CompanyID, Salary, Grade);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType RemoveCompany(void *DS, int CompanyID)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->RemoveCompany(CompanyID);
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

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->GetCompanyInfo(CompanyID, Value, NumEmployees);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->GetEmployeeInfo(EmployeeID, EmployerID, Salary, Grade);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->IncreaseCompanyValue(CompanyID, ValueIncrease);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID)
{
    if (DS == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->HireEmployee(EmployeeID, NewCompanyID);
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

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID)
{
    if (DS == NULL || EmployeeID == NULL)
        return INVALID_INPUT;
    try
    {
        *EmployeeID = ((MainDataStructure *)DS)->GetHighestEarner(CompanyID);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees)
{
    if (DS == NULL || Employees == NULL || NumOfEmployees == NULL)
        return INVALID_INPUT;
    try
    {
        *NumOfEmployees = ((MainDataStructure *)DS)->GetAllEmployeesBySalary(CompanyID, Employees);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees)
{
    if (DS == NULL || Employees == NULL)
        return INVALID_INPUT;
    try
    {
        ((MainDataStructure *)DS)->GetHighestEarnerInEachCompany(NumOfCompanies, Employees);
        return SUCCESS;
    }
    catch (std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                   int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    if (DS == NULL || TotalNumOfEmployees == NULL || NumOfEmployees == NULL)
        return INVALID_INPUT;
    try
    {
        *NumOfEmployees = ((MainDataStructure *)DS)->GetNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees);
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