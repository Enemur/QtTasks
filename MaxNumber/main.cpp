#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <algorithm>

using MatrixElement = std::pair<int, uint>;
using Matrix = std::vector<std::vector<MatrixElement>>;
const size_t matrixSize = 3;

void about();
Matrix readMatrixFromFile(std::string pathToFile);
int getMaxNumberOfMatrix(const Matrix &matrix);
int getMaxNumberFromPosition(Matrix &matrix, uint index, size_t line, size_t column);
void next(Matrix &matrix, uint index, size_t line, size_t column);

int main(int argc, char *argv[])
{
    about();

    if (argc < 2)
    {
        std::cout << "argc != 2" << std::endl;
        return -1;
    }

    try
    {
        auto pathToFile = argv[1];
        auto matrix = readMatrixFromFile(pathToFile);
        std::cout << getMaxNumberOfMatrix(matrix) << std::endl;

    }
    catch(std::exception &exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }

    return 0;
}

void about()
{
    std::cout << "Ametov Pavel\n"
              << "8-T3O-302B-16"
              << std::endl;
}

Matrix readMatrixFromFile(std::string pathToFile)
{
    std::ifstream reader(pathToFile);

    if (!reader.is_open())
        throw std::runtime_error("Incorrect file");

    const std::vector<MatrixElement> row(matrixSize);
    auto result = Matrix(matrixSize, row);

    try
    {
        size_t count = 0;

        while(!reader.eof() &&  count < matrixSize * matrixSize)
        {
            int number = 0;
            reader >> number;

            size_t line = count / matrixSize;
            size_t col = count % matrixSize;

            result[line][col].first = number;
            count++;
        }
    }
    catch(std::exception)
    {
        throw std::runtime_error("incorrect input");
    }

    return result;
}

int getMaxNumberOfMatrix(const Matrix &matrix)
{
    std::vector<int> numbers;

    for (size_t line = 0; line < matrixSize; line++)
        for (size_t column = 0; column < matrixSize; column++)
        {
            auto tmp = Matrix(matrix);
            auto number = getMaxNumberFromPosition(tmp, 1, line, column);
            numbers.push_back(number);
        }

    auto result = std::max_element(numbers.begin(), numbers.end());

    if (result == numbers.end())
        throw std::runtime_error("incorrect input");

    return *result;
}

int getValue(const Matrix& m, size_t index)
{
    for (size_t line = 0; line < matrixSize; line++)
        for (size_t col = 0; col < matrixSize; col++)
            if (m[line][col].second == index)
                return m[line][col].first;

    return -1;
}

int getNumber(const Matrix& m) {
    int result = 0;

    for (size_t index = 1; index <= matrixSize * matrixSize; index++)
    {
        auto value = getValue(m, index);

        if (value == -1)
            continue;

        if (result != 0)
            result *= 10;

        result += value;
    }

    return result;
}


int getMaxNumberFromPosition(Matrix &matrix, uint index, size_t line, size_t column)
{
    matrix[line][column].second = index;

    auto newIndex = index + 1;

    next(matrix, newIndex, line, column - 1);
    next(matrix, newIndex, line, column + 1);
    next(matrix, newIndex, line - 1, column);
    next(matrix, newIndex, line + 1, column);

    return getNumber(matrix);
}

void next(Matrix &matrix, uint index, size_t line, size_t column)
{
    if (line >= 0 && column >= 0 && line < matrixSize && column < matrixSize)
    {
        const auto el = matrix[static_cast<size_t>(line)][static_cast<size_t>(column)];

        if (el.second == 0)
            auto res = getMaxNumberFromPosition(matrix, index, line, column);
    }
}
