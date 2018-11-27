#include "mainwindowmodel.h"

#include <qfiledialog.h>

MainWindowModel::MainWindowModel()
    :_model(new HanoiTowersModel()),
     _timer(new QTimer(this)),
     _logger(new Logger()),
     _buttonsActions()
{
    isStarted = false;

    _buttonsActions[Buttons::Start] = [=](){start();};
    _buttonsActions[Buttons::Stop] = [=](){stop();};
    _buttonsActions[Buttons::NextStep] = [=](){nextStep();};
    _buttonsActions[Buttons::PrevStep] = [=](){prevStep();};
    _buttonsActions[Buttons::SaveLog] = [=](){saveLogsToFile();};
    _buttonsActions[Buttons::ClearLogs] = [=](){_logger->clear();};

    _timer->setInterval(TimerInterval);
    QObject::connect(_timer, &QTimer::timeout, this, &MainWindowModel::nextStep);

    QObject::connect(_logger, &Logger::logsChanged, this, &MainWindowModel::onLogsChanged);
    QObject::connect(_logger, &Logger::logsClear, this, &MainWindowModel::onLogsClear);
    QObject::connect(_model, &HanoiTowersModel::towersChanged, this, &MainWindowModel::onTowersChanged);
    QObject::connect(_model, &HanoiTowersModel::movedTowers, this, &MainWindowModel::onMovedTowers);
    QObject::connect(_model, &HanoiTowersModel::towersFinished, this, &MainWindowModel::stop);
}

void MainWindowModel::clearLogs()
{
    _logger->clear();
}

void MainWindowModel::setN(int n)
{
    _model->setN(n);
    _timer->stop();
}

void MainWindowModel::executeButtonAction(Buttons button)
{
    if (_buttonsActions.count(button))
        _buttonsActions[button]();
}

void MainWindowModel::start()
{
    if (_model->isFinished())
        return;

    if (isStarted)
        return;

    _logger->info("loop started");
    _timer->start();

    isStarted = true;
}

void MainWindowModel::stop()
{
    if (!isStarted)
        return;

    _timer->stop();
    _logger->info("loop stoped");

    isStarted = false;
}

void MainWindowModel::nextStep()
{
    if (_model->isFinished())
        return;

    _model->nextStep();
}

void MainWindowModel::prevStep()
{
    _model->prevStep();
}

void MainWindowModel::saveLogsToFile()
{
    auto filePath = QFileDialog::getSaveFileName();
    _logger->saveToFile(filePath);
}

void MainWindowModel::onLogsChanged(const QString &message)
{
    emit logsChanged(message);
}

void MainWindowModel::onLogsClear()
{
    emit logsClear();
}

void MainWindowModel::onMovedTowers(HanoiAction action, int i1, int i2)
{
    QString str;
    if (action == HanoiAction::ANextStep)
        str += "Next step: ";
    else if (action == HanoiAction::APrevStep)
        str += "Prev step: ";

    str += QString("from #1: %1, to #2: %2").arg(QString::number(i1), QString::number(i2));

    _logger->info(str);
}

void MainWindowModel::onTowersChanged(const QVector<QVector<int>> &towers)
{
    emit towersChanged(towers);
}


MainWindowModel::~MainWindowModel()
{
    delete _timer;
    delete _logger;
    delete _model;
}
