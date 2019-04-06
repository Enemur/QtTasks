#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    UiElements uiElements;
    uiElements.window = this;
    uiElements.valueOfA = ui->valueOfA;
    uiElements.valueOfK = ui->valueOfK;
    uiElements.valueOfI = ui->valueOfI;
    uiElements.valueOfJ = ui->valueOfJ;
    uiElements.valueOfM = ui->valueOfM;
    uiElements.viewBit = ui->viewBit;
    uiElements.viewResetBits = ui->viewResetBits;
    uiElements.viewSwapBits = ui->viewSwapBits;
    uiElements.viewUpdatedBit = ui->viewUpdatedBit;
    uiElements.viewBinary = ui->viewBinary;
    uiElements.treeView = ui->treeView;

    uiElements.rbDecrypting = ui->rbDecrypting;
    uiElements.rbEncrypting = ui->rbEncrypting;

    uiElements.rbDES = ui->rbDES;
    uiElements.rbRC4 = ui->rbRC4;
    uiElements.rbMyAlgorithm = ui->rbMyAlgorithm;
    uiElements.rbVernam = ui->rbVernam;

    uiElements.lenLE = ui->lenLE;
    uiElements.glueBits = ui->glueBits;
    uiElements.middleBits = ui->middleBits;
    uiElements.resPer = ui->resPer;
    uiElements.per = ui->per;

    uiElements.maxPowLE = ui->maxPowLE;
    uiElements.pLE = ui->pLE;
    uiElements.xorLE = ui->xorLE;
    uiElements.leftShiftLE = ui->leftShiftLE;
    uiElements.rightShiftLE = ui->rightShiftLE;

    uiElements.gbDES = ui->gbDES;

    _presenter = new AppPresenter(uiElements);    

    ui->keyLE->setEchoMode(QLineEdit::EchoMode::Password);

    setConnections();
}

void MainWindow::setConnections()
{
    connect(ui->valueOfA, &QLineEdit::textChanged, _presenter, &AppPresenter::setA);
    connect(ui->valueOfK, &QLineEdit::textChanged, _presenter, &AppPresenter::setK);
    connect(ui->valueOfI, &QLineEdit::textChanged, _presenter, &AppPresenter::setI);
    connect(ui->valueOfJ, &QLineEdit::textChanged, _presenter, &AppPresenter::setJ);
    connect(ui->valueOfM, &QLineEdit::textChanged, _presenter, &AppPresenter::setM);
    connect(ui->lenLE, &QLineEdit::textChanged, _presenter, &AppPresenter::setLen);

    connect(ui->resPerBtn, &QPushButton::clicked, _presenter, &AppPresenter::setArray);

    connect(ui->treeView, &QTreeView::doubleClicked, _presenter, &AppPresenter::onFileSelected);

    connect(ui->rbDES, &QRadioButton::clicked, _presenter, [this](){_presenter->setAlgorithm(EncryptingAlgorithms::DES);});
    connect(ui->rbMyAlgorithm, &QRadioButton::clicked, _presenter, [this](){_presenter->setAlgorithm(EncryptingAlgorithms::MyAlgorithm);});
    connect(ui->rbRC4, &QRadioButton::clicked, _presenter, [this](){_presenter->setAlgorithm(EncryptingAlgorithms::RC4);});
    connect(ui->rbVernam, &QRadioButton::clicked, _presenter, [this](){_presenter->setAlgorithm(EncryptingAlgorithms::Vernam);});

    connect(ui->actionExit, &QAction::triggered, QApplication::instance(), &QApplication::quit);

    connect(ui->rbEncrypting, &QRadioButton::clicked, _presenter, [this](){_presenter->setEncrypt(true);});
    connect(ui->rbDecrypting, &QRadioButton::clicked, _presenter, [this](){_presenter->setEncrypt(false);});

    connect(ui->rbCBC, &QRadioButton::clicked, _presenter, [this](){_presenter->setDesMode(DESMode::CBC);});
    connect(ui->rbCFB, &QRadioButton::clicked, _presenter, [this](){_presenter->setDesMode(DESMode::CFB);});
    connect(ui->rbECB, &QRadioButton::clicked, _presenter, [this](){_presenter->setDesMode(DESMode::ECB);});
    connect(ui->rbOFB, &QRadioButton::clicked, _presenter, [this](){_presenter->setDesMode(DESMode::OFB);});

    connect(ui->setKeyBtn, &QPushButton::clicked, _presenter, [this](){_presenter->setKey(ui->keyLE->text());});
    connect(ui->setInitVector, &QPushButton::clicked, _presenter, [this](){_presenter->setInitialVector(ui->initVectorLE->text());});

    connect(ui->showKey, &QPushButton::clicked, this, &MainWindow::showKey);

    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::showKey()
{
    if (ui->keyLE->echoMode() == QLineEdit::EchoMode::Password)
    {
        ui->keyLE->setEchoMode(QLineEdit::EchoMode::Normal);
        ui->showKey->setText("Hide");
    }
    else
    {
        ui->keyLE->setEchoMode(QLineEdit::EchoMode::Password);
        ui->showKey->setText("Show");
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, "About", "Ametov Pavel\n 8-T3O-302B-16");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _presenter;
}
