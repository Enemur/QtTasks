#ifndef MATRIXEXCEPTION_H
#define MATRIXEXCEPTION_H

#include <exception>
#include <string>

class MatrixException : public std::exception
{
private:
    std::string _message;
public:
    MatrixException(const std::string &message);

    const char* what() const noexcept;
};

class DivideByZeroException : public MatrixException
{
public:
    DivideByZeroException();
};

class DeterminantIsZeroException : public MatrixException
{
public:
    DeterminantIsZeroException();
};

class NotSquareMatrixException : public MatrixException
{
public:
    NotSquareMatrixException();
};

#endif // MATRIXEXCEPTION_H


