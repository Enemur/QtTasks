#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <algorithm>
#include "complexnumber.h"
#include <QVector>

using std::vector;
using MatrixArr = vector<vector<ComplexNumber>>;

class Matrix
{
private:
    MatrixArr _coefficients;

    size_t _rowCount;
    size_t _colCount;
public:
    Matrix();
    Matrix(size_t colCount, size_t rowCount, const QVector<double> &coefficients);
    Matrix(const Matrix &matrix);

    Matrix& operator=(const Matrix &matrix);

    static Matrix multiply(const Matrix &left, const Matrix &right);
    static Matrix addition(const Matrix &left, const Matrix &right);
    static Matrix division(const Matrix &left, const Matrix &right);
    static Matrix subtraction(const Matrix &left, const Matrix &right);

    ~Matrix();
};

#endif // MATRIX_H
