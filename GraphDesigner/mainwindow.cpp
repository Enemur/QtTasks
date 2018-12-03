#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _presenter(new AppPresenter())
{
    ui->setupUi(this);
    setConnection();

    ui->graficArea->setMouseTracking(true);

    _presenter->setGraphicsView(ui->graficArea);
    _presenter->setVertexLabelEdit(ui->setVertexLabel);
}

void MainWindow::setConnection()
{
    QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    QObject::connect(ui->actionExit, &QAction::triggered, QApplication::instance(), &QApplication::quit);

    QObject::connect(ui->setVertexLabelBtn, &QPushButton::clicked, _presenter, &AppPresenter::setVertexLabel);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About", "Ametov Pavel Sergeevich\n8-T3O-302B-16");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _presenter;
}
