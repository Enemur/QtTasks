#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "complexnumber.h"
#include "matrix.h"
#include <QVector>

void printAbout();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    printAbout();

    auto coef = QVector<double>();
    coef.append(1);
    coef.append(-2);
    coef.append(-1);
    coef.append(4);

    Matrix tmp(2, 2, coef);

    std::cout << tmp.determinant() << std::endl;
    std::cout << tmp.inverce() * tmp << std::endl;

    return a.exec();
}

void printAbout()
{
    std::cout << "Pavel Ametov"
              << "8-T3O-302B-16"
              << std::endl;
}
