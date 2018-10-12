#include "complexnumberexception.h"

ComplexNumberException::ComplexNumberException(std::string message)
    :_message(message){}

const char *ComplexNumberException::what() const noexcept
{
    return _message.c_str();
}

CNDivideByZeroException::CNDivideByZeroException()
    :ComplexNumberException("Dived by zero") {}
