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

    Matrix tmp(4, 4, QVector<double>(2, 3)),
            tmp2;

    tmp = Matrix::generate();
    std::cout << tmp.toString() << std::endl;

    return a.exec();
}

void printAbout()
{
    std::cout << "Pavel Ametov"
              << "8-T3O-302B-16"
              << std::endl;
}
