#include "complexnumber.h"

ComplexNumber ComplexNumber::ZERO = ComplexNumber();
ComplexNumber ComplexNumber::ONE = ComplexNumber(1, 0);
ComplexNumber ComplexNumber::IMAGINARY_ONE = ComplexNumber(0, 1);

ComplexNumber::ComplexNumber()
{
    _realPart = 0;
    _imaginaryPart = 0;
}

ComplexNumber::ComplexNumber(double realPart, double imaginaryPart)
{
    _realPart = realPart;
    _imaginaryPart = imaginaryPart;
}

ComplexNumber::ComplexNumber(const ComplexNumber &complexNumber)
{
    _realPart = complexNumber._realPart;
    _imaginaryPart = complexNumber._imaginaryPart;
}

ComplexNumber &ComplexNumber::operator=(const ComplexNumber &number)
{
    if (this != &number)
    {
        _realPart = number._realPart;
        _imaginaryPart = number._imaginaryPart;
    }

    return *this;
}

bool ComplexNumber::operator==(const ComplexNumber &number) const
{
    return equal(number);
}

bool ComplexNumber::operator!=(const ComplexNumber &number) const
{
    return !equal(number);
}

ComplexNumber ComplexNumber::multiply(const ComplexNumber &left, const ComplexNumber &right)
{
    auto result = ComplexNumber();

    result._realPart = left._realPart * right._realPart -
            left._imaginaryPart * right._imaginaryPart;
    result._imaginaryPart = left._realPart * right._imaginaryPart +
            right._realPart * left._imaginaryPart;

    return result;
}

ComplexNumber ComplexNumber::addition(const ComplexNumber &left, const ComplexNumber &right)
{
    auto result = ComplexNumber(left);

    result._imaginaryPart += right._imaginaryPart;
    result._realPart += right._realPart;

    return result;
}

ComplexNumber ComplexNumber::unaryMinus(const ComplexNumber &left)
{
    auto result = ComplexNumber(-left._realPart, -left._imaginaryPart);
    return result;
}

ComplexNumber ComplexNumber::subtraction(const ComplexNumber &left, const ComplexNumber &right)
{
    ComplexNumber result = ComplexNumber(left);

    result._imaginaryPart -= right._imaginaryPart;
    result._realPart -= right._realPart;

    return result;
}

ComplexNumber ComplexNumber::divide(const ComplexNumber &left, const ComplexNumber &right)
{
    auto result = ComplexNumber();

    if (right == ComplexNumber::ZERO)
        throw new CNDivideByZeroException();

    result._realPart = (left._realPart * right._realPart +
            left._imaginaryPart * right._imaginaryPart) /
            (right._realPart * right._realPart +
             right._imaginaryPart * right._imaginaryPart);
    result._imaginaryPart = (right._realPart * left._imaginaryPart -
                             left._realPart * right._imaginaryPart) /
            (right._realPart * left._realPart +
             right._imaginaryPart * right._imaginaryPart);

    return result;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber &right) const
{
    auto result = ComplexNumber::multiply(*this, right);
    return result;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber &right) const
{
    auto result = ComplexNumber::addition(*this, right);
    return result;
}

ComplexNumber ComplexNumber::operator-() const
{
    auto result = ComplexNumber::unaryMinus(*this);
    return result;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber &right) const
{
    auto result = ComplexNumber::subtraction(*this, right);
    return result;
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber &right) const
{
    auto result = ComplexNumber::divide(*this, right);
    return result;
}

ComplexNumber &ComplexNumber::operator*=(const ComplexNumber &right)
{
    *this = ComplexNumber::multiply(*this, right);
    return *this;
}

ComplexNumber &ComplexNumber::operator+=(const ComplexNumber &right)
{
    *this = ComplexNumber::addition(*this, right);
    return *this;
}

ComplexNumber &ComplexNumber::operator-=(const ComplexNumber &right)
{
    *this = ComplexNumber::subtraction(*this, right);
    return *this;
}

ComplexNumber &ComplexNumber::operator/=(const ComplexNumber &right)
{
    *this = ComplexNumber::divide(*this, right);
    return *this;
}

bool ComplexNumber::equal(const ComplexNumber &number) const
{
    auto realPartIsEqual = fabs(_realPart - number._realPart) == 0.0;
    auto imgPartIsEqual = fabs(_imaginaryPart - number._imaginaryPart) == 0.0;

    return realPartIsEqual && imgPartIsEqual;
}

std::string ComplexNumber::toString() const
{
    auto result = std::stringstream();

    if (_realPart != 0.0 || _imaginaryPart == 0.0)
        result << _realPart;
    if (_imaginaryPart != 0.0)
    {
        if (_realPart != 0.0 && _imaginaryPart > 0.0)
            result << "+";

        result << _imaginaryPart << "i";
    }

    return result.str();
}

ComplexNumber::~ComplexNumber()
{

}
