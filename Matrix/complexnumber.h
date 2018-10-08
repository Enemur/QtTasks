#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <qmath.h>
#include <qstring.h>
#include <sstream>

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
    bool operator== (const ComplexNumber& number);
    bool operator!= (const ComplexNumber& number);

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

    bool equal(const ComplexNumber &number);
    std::string toString();

    ~ComplexNumber();
};

#endif // COMPLEXNUMBER_H
