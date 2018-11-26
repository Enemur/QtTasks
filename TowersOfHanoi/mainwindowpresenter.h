#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include "mainwindowmodel.h"
#include <qaction.h>
#include <map>
#include <functional>
#include <buttons.h>
#include <QMainWindow>
#include <QListView>

class MainWindowPresenter: public QObject
{
    Q_OBJECT
private:
    MainWindowModel* _model;
    QListView* _listView;
    QStringListModel* _listViewModel;
public:
    MainWindowPresenter();

    void executeButtonAction(Buttons button);
    void setListView(QListView* listView);
    void setN(int n);

    ~MainWindowPresenter();

private slots:
    void onLogsChanged(const QString &message);
    void onLogsClear();
    void onTowersChanged(const QVector<QVector<int>> &towers);
signals:
    void towersChanged(const QVector<QVector<int>> &towers);
};

#endif // MAINWINDOWPRESENTER_H
