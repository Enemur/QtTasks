#include "hanoitowersmodel.h"

HanoiTowersModel::HanoiTowersModel()
    :_currentStep(1),
     _n(0),
     _kernels(QVector<QVector<int>>(3, QVector<int>()))
{

}

void HanoiTowersModel::setN(int n)
{
    _n = n;

    for (int i = 0; i < _kernels.size(); i++)
        _kernels[i].clear();

    for(auto i = n; i >= 0; i--)
        _kernels[0].append(i);

    _maxCountSteps = static_cast<int>(pow(_n, 2) - 1);
    emit towersChanged(_kernels);
}

void HanoiTowersModel::nextStep()
{
    int t = 0;

    if (_currentStep == _maxCountSteps)
        return;

    for(int i = 0;;i++)
        if (_currentStep >> i == 1)
        {
            t = i;
            break;
        }


    int i1 = 0;
    for (int i = 0; i < _kernels.size(); i++)
        if (_kernels[i].count(i) != 0)
            i1 = i;

    int i2 = static_cast<int>(i1 + pow(-1, t)) % 3;

    _kernels[i2].push_back(_kernels[i1].back());
    _kernels[i1].pop_back();

    _currentStep++;

    emit towersChanged(_kernels);
    emit movedTowers(HanoiAction::ANextStep, i1, i2);
}

void HanoiTowersModel::prevStep()
{
    int i1 = 0;
    int i2 = 0;
    emit towersChanged(_kernels);
    emit movedTowers(HanoiAction::ANextStep, i1, i2);
}
