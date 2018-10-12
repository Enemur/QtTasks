#ifndef MATRIXEXCEPTION_H
#define MATRIXEXCEPTION_H

#include <exception>
#include <string>

class MatrixException : std::exception
{
private:
    std::string _message;
public:
    MatrixException(const std::string &message);

    const char* what() const noexcept;
};

class DivideByZeroException : MatrixException
{
public:
    DivideByZeroException();
};

class DeterminantIsZeroException : MatrixException
{
public:
    DeterminantIsZeroException();
};

class NotSquareMatrixException : MatrixException
{
public:
    NotSquareMatrixException();
};

#endif // MATRIXEXCEPTION_H


