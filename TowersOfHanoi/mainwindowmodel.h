#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include "logger.h"
#include <QObject>
#include <QTimer>
#include <vector>
#include <string>
#include <buttons.h>
#include <functional>
#include <QStringListModel>
#include "hanoitowersmodel.h"
#include "hanoiaction.h"

class MainWindowModel: public QObject
{
    Q_OBJECT
public:
    MainWindowModel();

    void saveLogsToFile(const std::string &filePath);
    void clearLogs();

    void setN(int n);

    void executeButtonAction(Buttons button);

    ~MainWindowModel();
private:
    HanoiTowersModel* _model;
    bool isStarted;
    const static int TimerInterval = 100;
    QTimer* _timer;

    Logger* _logger;
    std::map<Buttons, std::function<void()>> _buttonsActions;

    void start();
    void stop();
    void nextStep();
    void prevStep();
    void saveLogsToFile();

private slots:
    void onLogsChanged(const QString &message);
    void onLogsClear();
    void onTowersChanged(const QVector<QVector<int>> &towers);
    void onMovedTowers(HanoiAction action, int i1, int i2);
signals:
    void logsChanged(const QString &message);
    void logsClear();
    void towersChanged(const QVector<QVector<int>> &towers);
};

#endif // MAINWINDOWMODEL_H
