#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "app_presenter.h"
#include "encrypting_algorithm.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QMainWindow>
#include <QLabel>
#include "QMessageBox"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void setConnections();
    void showKey();
    void about();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    AppPresenter* _presenter;
};

#endif // MAINWINDOW_H
