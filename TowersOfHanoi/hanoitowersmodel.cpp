#include "hanoitowersmodel.h"


HanoiTowersModel::HanoiTowersModel()
    :_currentStep(0),
     _n(0),
     _kernels(QVector<QVector<int>>(3, QVector<int>())),
    _isFinished(true)
{

}

void HanoiTowersModel::setN(int n)
{
    _n = n;
    _currentStep = 0;
    _isFinished = false;

    for (int i = 0; i < _kernels.size(); i++)
        _kernels[i].clear();

    for(auto i = n - 1; i >= 0; i--)
        _kernels[0].append(i);

    _maxCountSteps = static_cast<int>(pow(2, _n) - 1);
    emit towersChanged(_kernels);
}

bool HanoiTowersModel::isFinished()
{
    return _isFinished;
}

int HanoiTowersModel::powInt(int value, int pow)
{
    if (pow == 0)
        return 1;
    else if (pow == 1)
        return value;

    int result = value;
    for(int i = 1 ; i < pow; i++)
        result *= value;
    return result;

}

int HanoiTowersModel::mod(int a, int b)
{
    return (b + (a % b)) % b;
}

void HanoiTowersModel::nextStep()
{
    if (_isFinished)
        return;

    if (_currentStep >= _maxCountSteps)
    {
        _isFinished = true;
        emit towersFinished();
        return;
    }

    auto res = setStep(++_currentStep);
    emit movedTowers(HanoiAction::ANextStep, res.first, res.second);
}

void HanoiTowersModel::prevStep()
{
    if (_currentStep <= 0)
        return;

    _isFinished = false;

    auto res = setStep(--_currentStep);
    emit movedTowers(HanoiAction::APrevStep, res.first, res.second);
}

std::pair<int, int> HanoiTowersModel::setStep(int step)
{
    std::pair<int, int> result;
    QVector<QVector<int>> tmpKernels(3, QVector<int>());

    for(int diskNumber = _n - 1; diskNumber >= 0; diskNumber--)
    {
        int sign = powInt(-1, _n - diskNumber);
        int a = sign * ((step / powInt(2, diskNumber)) - (step / powInt(2, diskNumber + 1)));
        int atKernel = mod(a, 3);
        tmpKernels[atKernel].push_back(diskNumber);
    }


    for (int i = 0; i < tmpKernels.size(); i++)
        if (_kernels[i].size() > tmpKernels[i].size())
            result.first = i;
        else if (_kernels[i].size() < tmpKernels[i].size())
            result.second = i;

    _kernels = tmpKernels;
    emit towersChanged(_kernels);
    return result;
}
