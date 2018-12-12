#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apppresenter.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void about();
    void setConnections();

    void budgetChanged();
private:
    Ui::MainWindow *ui;

    AppPresenter* _presenter;
};

#endif // MAINWINDOW_H
