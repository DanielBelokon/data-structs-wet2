#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class CompanyNotFoundException : public std::exception
{
};

class EmployeeNotFoundException : public std::exception
{
};

class CompanyAlreadyExistsException : public std::exception
{
};

class EmployeeAlreadyExistsException : public std::exception
{
};

class NegativeValueException : public std::exception
{
};

class NotEnoughCompaniesException : public std::exception
{
};

class AqcuirementFailedException : public std::exception
{
};

class InvalidInputException : public std::exception
{
};

class CompanyHasEmployeesException : public std::exception
{
};

class EmptyTreeException : public std::exception
{
};

#endif // EXCEPTIONS_H