#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _presenter(new AppPresenter())
{
    ui->setupUi(this);

    setConnections();

    _presenter->setBudgetEdit(ui->budgetEdit);
    _presenter->setRemainderLabel(ui->remainderLabel);
    _presenter->setListWidget(ui->listWidget);
}

void MainWindow::setConnections()
{
    QObject::connect(ui->budgetEdit, &QLineEdit::textChanged, this, &MainWindow::budgetChanged);

    QObject::connect(ui->addRateBtn, &QPushButton::clicked, _presenter, &AppPresenter::addRate);
    QObject::connect(ui->updateBudgetBtn, &QPushButton::clicked, _presenter, &AppPresenter::updateBudget);

    QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    QObject::connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);

    QObject::connect(ui->actionOpen, &QAction::triggered, _presenter, &AppPresenter::open);
    QObject::connect(ui->actionSave, &QAction::triggered, _presenter, &AppPresenter::save);
}

void MainWindow::budgetChanged()
{
    QPalette palete;

    bool isOk;
    ui->budgetEdit->text().toDouble(&isOk);
    if (isOk)
        palete.setColor(ui->budgetEdit->foregroundRole(), Qt::black);
    else
        palete.setColor(ui->budgetEdit->foregroundRole(), Qt::red);

    ui->budgetEdit->setPalette(palete);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About", "Ametov Pavel Sergeevich\n8-t3O-302B-16");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _presenter;
}
