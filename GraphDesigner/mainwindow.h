#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "apppresenter.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QGraphicsView>

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
    AppPresenter* _presenter;
private:
    void setConnection();

    void about();
    void onButtonClicked();
};

#endif // MAINWINDOW_H
