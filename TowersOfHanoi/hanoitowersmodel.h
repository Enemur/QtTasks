#ifndef HANOITOWERSMODEL_H
#define HANOITOWERSMODEL_H

#include <QObject>
#include <cmath>
#include <QVector>
#include <QStack>
#include "hanoiaction.h"
#include <QtMath>


class HanoiTowersModel : public QObject
{
    Q_OBJECT
private:
    int _currentStep;
    int _n;
    int _maxCountSteps;

    QVector<QVector<int>> _kernels;

    int powInt(int value, int pow);
    int mod(int a, int b);

    std::pair<int, int> setStep(int step);

    bool _isFinished;
public:
    HanoiTowersModel();

    void setN(int n);
    bool isFinished();

    void nextStep();
    void prevStep();
signals:
    void towersChanged(const QVector<QVector<int>>&);
    void movedTowers(HanoiAction, int, int);
    void towersFinished();
};

#endif // HANOITOWERSMODEL_H
