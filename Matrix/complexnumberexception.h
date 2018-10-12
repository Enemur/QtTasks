#ifndef COMPLEXNUMBEREXCEPTION_H
#define COMPLEXNUMBEREXCEPTION_H

#include <exception>
#include <string>

class ComplexNumberException : public std::exception
{
private:
    std::string _message;
public:
    ComplexNumberException(std::string message);
    const char* what() const noexcept;
};

class CNDivideByZeroException : public ComplexNumberException
{
public:
    CNDivideByZeroException();
};

#endif // COMPLEXNUMBEREXCEPTION_H
