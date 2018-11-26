#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwindowpresenter.h"
#include <QMainWindow>
#include <functional>
#include <buttons.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainWindowPresenter *presenter;
private:
    void about();
    void newScene();

    void buttonClick(Buttons button);
private slots:
    void onTowersChanged(const QVector<QVector<int> > &towers);
};

#endif // MAINWINDOW_H
