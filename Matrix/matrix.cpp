#include "matrix.h"

Matrix::Matrix()
    :_rowCount(0), _colCount(0)
{
    _coefficients = MatrixArr();
}

Matrix::Matrix(size_t colCount, size_t rowCount, const QVector<double> &coefficients)
    : _rowCount(rowCount), _colCount(colCount)
{
    std::vector<ComplexNumber> line(_colCount, ComplexNumber::ZERO);
    _coefficients = MatrixArr(_rowCount, line);

    int index = 0;
    for(size_t i = 0; i < _rowCount; i++)
        for(size_t j = 0; j < _colCount; j++)
        {
            if (index < coefficients.count())
                _coefficients[i][j] = ComplexNumber(coefficients[index++]);
            else
                break;
        }
}

Matrix::Matrix(size_t colCount, size_t rowCount)
    : _rowCount(rowCount), _colCount(colCount)
{
    std::vector<ComplexNumber> line(_colCount, ComplexNumber::ZERO);
    _coefficients = MatrixArr(_rowCount, line);
}

Matrix::Matrix(const Matrix &matrix)
    : _rowCount(matrix._rowCount), _colCount(matrix._colCount)
{
    _coefficients = matrix._coefficients;
}

Matrix& Matrix::operator=(const Matrix &matrix)
{
    if (this != &matrix)
    {
        _colCount = matrix._colCount;
        _rowCount = matrix._rowCount;

        _coefficients.clear();
        _coefficients = MatrixArr(matrix._coefficients);
    }
    return *this;
}

Matrix Matrix::multiply(const Matrix &left, const Matrix &right)
{
    auto result = Matrix(left._colCount, left._rowCount);
    if (left._colCount != right._rowCount)
        throw new std::exception();

    for (size_t i = 0; i < left._rowCount; i++)
        for (size_t j = 0; j < right._colCount; j++)
            for (size_t k = 0; k < left._colCount; k++)
                result._coefficients[i][j] +=
                        left._coefficients[i][k] * right._coefficients[k][j];

    return result;
}

Matrix Matrix::multiply(const Matrix &left, double number)
{
    auto result = Matrix(left);

    for (size_t i = 0; i < left._rowCount; i++)
        for (size_t j = 0; j < left._colCount; j++)
            result._coefficients[i][j] = left._coefficients[i][j] * number;

    return result;
}

Matrix Matrix::addition(const Matrix &left, const Matrix &right)
{
    auto result = Matrix(left._colCount, left._rowCount);

    for (size_t i = 0; i < left._rowCount; i++)
        for (size_t j = 0; j < left._colCount; j++)
            result._coefficients[i][j] = left._coefficients[i][j]
                    + right._coefficients[i][j];

    return result;
}

Matrix Matrix::division(const Matrix &left, const Matrix &right)
{
    // TODO: add division
}

Matrix Matrix::subtraction(const Matrix &left, const Matrix &right)
{   
    auto result = Matrix(left._colCount, left._rowCount);

    for (size_t i = 0; i < left._rowCount; i++)
        for (size_t j = 0; j < left._colCount; j++)
            result._coefficients[i][j] = left._coefficients[i][j]
                    - right._coefficients[i][j];

    return result;
}

Matrix Matrix::unaryMinus(const Matrix &matrix)
{
    auto result = Matrix(matrix);
    for (size_t i = 0; i < matrix._rowCount; i++)
        for (size_t j =0; j < matrix._colCount; j++)
            result._coefficients[i][j] = -result._coefficients[i][j];

    return result;
}

Matrix Matrix::operator*(const Matrix &right) const
{
    return multiply(*this, right);
}

Matrix Matrix::operator+(const Matrix &right) const
{
    return addition(*this, right);
}

Matrix Matrix::operator-() const
{
    return unaryMinus(*this);
}

Matrix Matrix::operator-(const Matrix &right) const
{
    return subtraction(*this, right);
}

Matrix Matrix::operator/(const Matrix &right) const
{
    return division(*this, right);
}

Matrix &Matrix::operator*=(const Matrix &right)
{
    *this = multiply(*this, right);
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &right)
{
    *this = addition(*this, right);
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &right)
{
    *this = subtraction(*this, right);
    return *this;
}

Matrix &Matrix::operator/=(const Matrix &right)
{
    *this = division(*this, right);
    return *this;
}

Matrix Matrix::inverce() const
{
   if (determinant() == ComplexNumber::ZERO)
       throw DeterminantIsZeroException();

   auto tmp{*this};

   auto amount = static_cast<int>(_rowCount * _rowCount);
   QVector<double> vect(amount, 1.0);
   Matrix negative(_rowCount, _rowCount, vect);

   tmp.makeTriangle(&negative);
   tmp.reverse();
   negative.reverse();

   tmp.makeTriangle(&negative);
   tmp.reverse();
   negative.reverse();

   for (size_t line = 0; line < _rowCount; line++)
       for (size_t column = 0; column < _colCount; column++)
           negative._coefficients[line][column] /= tmp._coefficients[line][line];

   return negative;
}

ComplexNumber Matrix::determinant() const
{
    Matrix tmp(*this);

    if (_rowCount != _colCount)
        throw new NotSquareMatrixException();

    try
    {
        tmp.makeTriangle();
    }
    catch (...)
    {
        return ComplexNumber::ZERO;
    }

    auto result = tmp._coefficients[0][0];

    for (size_t i = 1; i < _rowCount; i++) {
        result *= tmp._coefficients[i][i];
    }

    return result;
}

Matrix Matrix::transposed() const
{
    auto result = Matrix(_colCount, _rowCount);

    for (size_t i = 0; i < _rowCount; i++)
        for (size_t j = 0; j < _colCount; j++)
            result._coefficients[i][j] = _coefficients[j][i];

    return result;
}

ComplexNumber Matrix::trace() const
{
    auto result = ComplexNumber();

    for (size_t i = 0; i < _rowCount; i++)
        result += _coefficients[i][i];

    return result;
}

Matrix Matrix::conjugate() const
{
    auto result = transposed();
    result = unaryMinus(result);

    return result;
}

Matrix Matrix::pow(unsigned int power) const
{
    auto result = Matrix(*this);

    for (unsigned int i = 1; i < power; i++)
        result *= result;

    return result;
}

std::vector<ComplexNumber> Matrix::eigenvaluesEigenvectors() const
{
    auto result = std::vector<ComplexNumber>();



    return result;
}

Matrix Matrix::generate()
{
    size_t colCount = rand() % 10;
    size_t rowCount = rand() % 10;

    auto coefficents = QVector<double>();
    for(size_t i = 0; i < colCount * rowCount; i++)
        coefficents.append(rand());

   return Matrix(colCount, rowCount, coefficents);
}

bool Matrix::equal(const Matrix &matrix) const
{
    auto isEqualColCount = _colCount == matrix._colCount;
    auto isEqualRowCount = _rowCount == matrix._rowCount;

    if (!isEqualColCount || !isEqualRowCount)
        return false;

    for (size_t i = 0; i < _rowCount; i++)
        for (size_t j = 0; j < _colCount; j++)
            if (_coefficients[i][j] != matrix._coefficients[i][j])
                return false;

    return true;
}

std::string Matrix::toString() const
{
    auto result = std::stringstream();

    for (size_t i = 0; i < _rowCount; i++)
    {
        for (size_t j = 0; j < _colCount; j++)
        {
            result << "["
                   << _coefficients[i][j].toString()
                   << "]";
        }
        if (i != _rowCount - 1)
            result << "|";
    }

    return result.str();
}

void Matrix::makeTriangle(Matrix* neg)
{
    for (size_t line = 0; line < _colCount; line++)
    {
        if (_coefficients[line][line] == ComplexNumber::ZERO)
            for (size_t inner_line = line + 1; inner_line < _colCount; inner_line++)
                if (_coefficients[inner_line][line] != ComplexNumber::ZERO)
                {
                    swapLines(line, inner_line);

                    if (neg != nullptr)
                        neg->swapLines(line, inner_line);
                }

        if (_coefficients[line][line] == ComplexNumber::ZERO)
            throw DeterminantIsZeroException();

        for (size_t inner_line = line + 1; inner_line < _rowCount; inner_line++)
        {
            auto coef = _coefficients[inner_line][line] / _coefficients[line][line];

            for (size_t inner_col = 0; inner_col < _rowCount; inner_col++)
            {
                _coefficients[inner_line][inner_col] -= (coef * _coefficients[line][inner_col]);

                if (neg != nullptr)
                    neg->_coefficients[inner_line][inner_col] -= (coef * neg->_coefficients[line][inner_col]);
            }
        }
    }
}

void Matrix::swapLines(size_t first, size_t second)
{
    if (first >= _rowCount || second >= _rowCount)
        return;

    for (size_t i = 0; i < _rowCount; i++)
        std::swap(_coefficients[first][i], _coefficients[second][i]);
}

void Matrix::swapColums(size_t first, size_t second)
{
    if (first >= _rowCount || second >= _rowCount)
        return;

    for (size_t i = 0; i < _rowCount; i++) {
        std::swap(_coefficients[i][first], _coefficients[i][second]);
    }
}

Matrix::~Matrix()
{
    _coefficients.clear();
}

void Matrix::reverse()
{
    for (size_t line = 0; line < (_rowCount / 2); line++)
        swapLines(line, _rowCount - 1 - line);

    for (size_t column = 0; column < (_colCount / 2); column++)
        swapColums(column, _colCount - 1 - column);
}
