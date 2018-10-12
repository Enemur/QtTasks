#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <qmath.h>
#include <qstring.h>
#include <sstream>
#include "complexnumberexception.h"

class ComplexNumber
{
private:
    double _realPart;
    double _imaginaryPart;
public:
    static ComplexNumber ZERO;
    static ComplexNumber ONE;
    static ComplexNumber IMAGINARY_ONE;

    ComplexNumber();
    ComplexNumber(double realPart, double imaginaryPart = 0);
    ComplexNumber(const ComplexNumber &complexNumber);

    ComplexNumber& operator= (const ComplexNumber& number);
    bool operator== (const ComplexNumber& number) const;
    bool operator!= (const ComplexNumber& number) const;

    static ComplexNumber multiply(const ComplexNumber &left, const ComplexNumber &right);
    static ComplexNumber addition(const ComplexNumber &left, const ComplexNumber &right);
    static ComplexNumber unaryMinus(const ComplexNumber &left);
    static ComplexNumber subtraction(const ComplexNumber &left, const ComplexNumber &right);
    static ComplexNumber divide(const ComplexNumber &left, const ComplexNumber &right);

    ComplexNumber operator*(const ComplexNumber& right) const;
    ComplexNumber operator+(const ComplexNumber& right) const;
    ComplexNumber operator-() const;
    ComplexNumber operator-(const ComplexNumber& right) const;
    ComplexNumber operator/(const ComplexNumber& right) const;

    ComplexNumber& operator*=(const ComplexNumber& right);
    ComplexNumber& operator+=(const ComplexNumber& right);
    ComplexNumber& operator-=(const ComplexNumber& right);
    ComplexNumber &operator/=(const ComplexNumber& right);

    bool equal(const ComplexNumber &number) const;
    std::string toString() const;

    template <typename Stream>
    friend Stream& operator<<(Stream& stream, const ComplexNumber& number) {
        stream << number.toString();
        return stream;
    }

    ~ComplexNumber();
};

#endif // COMPLEXNUMBER_H
