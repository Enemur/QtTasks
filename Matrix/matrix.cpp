#include "matrix.h"

Matrix::Matrix()
{
    _coefficients = vector<vector<ComplexNumber>>();
    _rowCount = 0;
    _colCount = 0;
}

Matrix::Matrix(size_t colCount, size_t rowCount, const QVector<double> &coefficients)
    : _rowCount(rowCount), _colCount(colCount)
{
    std::vector<ComplexNumber> line(_colCount, ComplexNumber::ZERO);
    _coefficients = MatrixArr(_rowCount, line);

    for(size_t i = 0, index = 0; i < _rowCount; i++)
        for(size_t j = 0; j < _colCount; j++)
        {
            if (index < coefficients.count())
                _coefficients[i][j] = ComplexNumber(coefficients[index++]);
            else
                break;
        }
}

Matrix::Matrix(const Matrix &matrix)
    : _rowCount(matrix._rowCount), _colCount(matrix._colCount)
{
    _coefficients = MatrixArr(matrix._coefficients);
}

Matrix& Matrix::operator=(const Matrix &matrix)
{
    if (this != &matrix)
    {
        _colCount = matrix._colCount;
        _rowCount = matrix._rowCount;

        _coefficients.clear();
        _coefficients = MatrixArr(_coefficients);
    }
    return *this;
}

Matrix Matrix::multiply(const Matrix &left, const Matrix &right)
{
    auto result = Matrix(left);
    if (left._colCount != right._rowCount)
        throw new std::exception();



    return result;
}

Matrix Matrix::addition(const Matrix &left, const Matrix &right)
{

}

Matrix Matrix::division(const Matrix &left, const Matrix &right)
{

}

Matrix Matrix::subtraction(const Matrix &left, const Matrix &right)
{

}

Matrix::~Matrix()
{
    _coefficients.clear();
}
