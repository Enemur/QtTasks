#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    UiElements uiElements;

    uiElements.window = this;
    uiElements.dirView = ui->dirView;
    uiElements.filesView = ui->filesView;
    uiElements.textView = ui->textView;
    uiElements.colors = ui->colors;

    uiElements.rbCp = ui->rbCp;
    uiElements.rbUTF8 = ui->rbUTF8;

    uiElements.cbBold = ui->cbBold;
    uiElements.cbItalic = ui->cbItalic;
    uiElements.cbUnderline = ui->cbUnderline;

    _presenter = new Presenter(uiElements);

    setConnections();
}

void MainWindow::setConnections()
{
    QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    QObject::connect(ui->actionExit, &QAction::triggered, QApplication::instance(), &QApplication::quit);

    QObject::connect(ui->dirView, &QTreeView::doubleClicked, _presenter, &Presenter::onDirViewDoubleClick);
    QObject::connect(ui->filesView, &QListView::doubleClicked, _presenter, &Presenter::onFileViewDoubleClick);

    QObject::connect(ui->resetBtn, &QPushButton::clicked, _presenter, &Presenter::reset);
    QObject::connect(ui->actionOpenDir, &QAction::triggered, _presenter, &Presenter::onOpenDirectoryClick);

    QObject::connect(ui->rbCp, &QRadioButton::clicked, _presenter, [&](){_presenter->setCodec(ui->rbCp->text());});
    QObject::connect(ui->rbUTF8, &QRadioButton::clicked, _presenter, [&](){_presenter->setCodec(ui->rbUTF8->text());});

    QObject::connect(ui->cbBold, &QCheckBox::stateChanged, _presenter, &Presenter::onSetBold);
    QObject::connect(ui->cbItalic, &QCheckBox::stateChanged, _presenter, &Presenter::onSetItalic);
    QObject::connect(ui->cbUnderline, &QCheckBox::stateChanged, _presenter, &Presenter::onSetUnderline);

    QObject::connect(ui->colors, SIGNAL(currentIndexChanged(int)), _presenter, SLOT(onSetColor(int)));
}

void MainWindow::about()
{
    QMessageBox::about(this, "About", "Ametov Pavel Sergeevich\n8-N3O-302B-16");
}

MainWindow::~MainWindow()
{
    delete ui;
}
