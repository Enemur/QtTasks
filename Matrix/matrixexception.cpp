#include "matrixexception.h"

MatrixException::MatrixException(const std::string &message)
    : _message(message) {}

const char* MatrixException::what() const noexcept
{
    return _message.c_str();
}

DivideByZeroException::DivideByZeroException()
    :MatrixException("Dived by zero") {}

DeterminantIsZeroException::DeterminantIsZeroException()
    :MatrixException("Determinant is zero") {}

NotSquareMatrixException::NotSquareMatrixException()
    :MatrixException("row count not equal col count") {}
