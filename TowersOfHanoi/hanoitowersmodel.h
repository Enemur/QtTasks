#ifndef HANOITOWERSMODEL_H
#define HANOITOWERSMODEL_H

#include <QObject>
#include <cmath>
#include <QVector>
#include <QStack>
#include "hanoiaction.h"

class HanoiTowersModel : public QObject
{
    Q_OBJECT
private:
    int _currentStep;
    int _n;
    int _maxCountSteps;

    QVector<QVector<int>> _kernels;
public:
    HanoiTowersModel();

    void setN(int n);

    void nextStep();
    void prevStep();

signals:
    void towersChanged(const QVector<QVector<int>> &);
    void movedTowers(HanoiAction, int, int);
};

#endif // HANOITOWERSMODEL_H
