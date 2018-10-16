#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "complexnumber.h"
#include "matrix.h"
#include <QVector>
#include <locale>
#include "matrixexception.h"

void printAbout();
void showMatrixMethods();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(time(NULL));

    printAbout();

    showMatrixMethods();

    return a.exec();
}

void printAbout()
{
    std::cout << "Pavel Ametov\n"
              << "8-T3O-302B-16"
              << std::endl;
}

void showMatrixMethods()
{
    try
    {
        auto coef = QVector<double>();
        coef.append(2);
        coef.append(-1);
        coef.append(4);
        coef.append(3);

        Matrix matrix1 = Matrix::generate(3, 3),
               matrix2 = Matrix::generate(3, 3),
               matrix3 = Matrix::generate(3, 3),
               matrix4 = Matrix(2, 2, coef);

        std::cout << "Matrix4:\n" << matrix4 << std::endl;
        std::cout << "Inverece matrix4:\n" << matrix4.inverce() << std::endl;
        std::cout << "Rank matrix4: " << matrix4.rank() << std::endl;
        std::cout << "Trasposed matrix4:\n" << matrix4.transposed() << std::endl;

        std::cout << "Matrix1: \n" << matrix1 << std::endl;
        std::cout << "------" << std::endl;
        std::cout << "Matrix2: \n" << matrix2 << std::endl;
        std::cout << "------" << std::endl;
        std::cout << "Matrix3: \n" << matrix3 << std::endl;
        std::cout << "**************" << std::endl;

        std::cout << "Determinant of matrix3:\n" << matrix3.determinant() << std::endl;
        std::cout << "Inverce of matrix1:\n" << matrix1.inverce() << std::endl;
        std::cout << "Result divide matrix1 to matrix1:\n" << matrix1 / matrix1 << std::endl;
        std::cout << "Result divide matrix1 to matrix2:\n" << matrix1 / matrix2 << std::endl;
        std::cout << "Result multiply matrix1 to matrix2:\n" << matrix1 * matrix2 << std::endl;
        std::cout << "Result addition matrix1 to matrix2:\n" << matrix1 + matrix2 << std::endl;
        std::cout << "Result division matrix1 to matrix2:\n" << matrix1 / matrix2 << std::endl;
        std::cout << "Result substraction matrix1 to matrix2:\n" << matrix1 - matrix2 << std::endl;
        std::cout << "Rank matrix1: " << matrix1.rank() << std::endl;
        std::cout << "Conjugate matrix1:\n" << matrix1.conjugate() << std::endl;
        std::cout << "HermiteConjugated matrix1:\n" << matrix1.hermiteConjugated() << std::endl;
    }
    catch(MatrixException ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
}
