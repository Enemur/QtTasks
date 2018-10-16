#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <algorithm>
#include "complexnumber.h"
#include <QVector>
#include <string>
#include <sstream>
#include "matrixexception.h"

/* Определить конструктор,
принимающий количество строк матрицы, количество столбцов матрицы и ссылку на
объект типа QVector<double>, инициализирующий матрицу построчно (при передаче
недостаточного количества аргументов, оставшиеся элементы матрицы заполняются по
умолчанию нулями).
 * Перегрузить конструктор копирования и деструктор. Перегрузить
операторы “=”, “==”, “!=”; “+”, “+=” (сложение матриц), “-“, “-=” (вычитание матриц); “*”,
“*=” (умножение матриц); “*”, “*=” (умножение матрицы на число/числа на матрицу); “<<”.
Реализовать операции нахождения определителя матрицы, +
нахождения следа матрицы, +
нахождения транспонированной матрицы, +
нахождения обратной матрицы, +
нахождения ранга матрицы,
нахождения комплексно-сопряжённой матрицы, +
нахождения эрмитовосопряжённой матрицы, +
возведения матрицы в целую неотрицательную степень, +
нахождения собственных чисел и собственных векторов матрицы.
Реализовать метод на уровне типа для создания случайной матрицы. +*/

using std::vector;
using MatrixArr = vector<vector<ComplexNumber>>;

class Matrix
{
private:
    MatrixArr _coefficients;

    size_t _rowCount;
    size_t _colCount;
public:
    //Constructors
    Matrix();
    Matrix(const Matrix &matrix);
    Matrix(size_t colCount, size_t rowCount, const QVector<double> &coefficients);
    Matrix(size_t colCount, size_t rowCount);
    //

    Matrix& operator=(const Matrix &matrix);

    //ArithmeticOperations
    static Matrix multiply(const Matrix &left, const Matrix &right);
    static Matrix multiply(const Matrix &left, double number);

    static Matrix addition(const Matrix &left, const Matrix &right);
    static Matrix division(const Matrix &left, const Matrix &right);
    static Matrix subtraction(const Matrix &left, const Matrix &right);
    static Matrix unaryMinus(const Matrix &matrix);
    //

    Matrix operator*(const Matrix& right) const;
    Matrix operator+(const Matrix& right) const;
    Matrix operator-() const;
    Matrix operator-(const Matrix& right) const;
    Matrix operator/(const Matrix& right) const;

    Matrix& operator*=(const Matrix& right);
    Matrix& operator+=(const Matrix& right);
    Matrix& operator-=(const Matrix& right);
    Matrix &operator/=(const Matrix& right);

    Matrix inverce() const;
    ComplexNumber determinant() const;
    Matrix transposed() const;
    ComplexNumber trace() const;
    Matrix conjugate() const;
    Matrix pow(unsigned int power) const;
    std::vector<ComplexNumber> eigenvaluesEigenvectors() const;
    Matrix hermiteConjugated() const;
    uint rank() const;

    static Matrix generate();
    
    bool equal(const Matrix &matrix) const;
    std::string toString() const;

    template <typename Stream>
    friend Stream& operator<<(Stream& stream, const Matrix& matrix) {
        stream << matrix.toString();
        return stream;
    }

    ~Matrix();
private:
    void reverse();
    void makeTriangle(Matrix* neg = nullptr);
    void swapLines(size_t first, size_t second);
    void swapColums(size_t first, size_t second);
};

#endif // MATRIX_H
