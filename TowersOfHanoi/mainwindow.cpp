#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QMessageBox>
#include <QPainter>
#include <qlabel.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    presenter(new MainWindowPresenter)
{
    ui->setupUi(this);

    this->setWindowFlags(
                Qt::Dialog |
                Qt::MSWindowsFixedSizeDialogHint);

    presenter->setListView(ui->listView);

    QObject::connect(ui->saveLogButton, &QPushButton::released, this, [this](){buttonClick(Buttons::SaveLog);});
    QObject::connect(ui->actionExit, &QAction::triggered, QApplication::instance(), &QApplication::quit);
    QObject::connect(ui->startButton, &QPushButton::released, this, [this](){buttonClick(Buttons::Start);});
    QObject::connect(ui->stopButton, &QPushButton::released, this, [this](){buttonClick(Buttons::Stop);});
    QObject::connect(ui->prevStepButton, &QPushButton::released, this, [this](){buttonClick(Buttons::PrevStep);});
    QObject::connect(ui->nextStepButton, &QPushButton::released, [this](){buttonClick(Buttons::NextStep);});
    QObject::connect(ui->cleaLogButton, &QPushButton::released, [this](){buttonClick(Buttons::ClearLogs);});
    QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    QObject::connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newScene);
    QObject::connect(presenter, &MainWindowPresenter::towersChanged, this, &MainWindow::onTowersChanged);
}

void MainWindow::buttonClick(Buttons button)
{
    presenter->executeButtonAction(button);
}

void MainWindow::onTowersChanged(const QVector<QVector<int> > &towers)
{
    int minWidth = 20;
    int minHeight = 20;

    int n = 0;
    for(auto kernel: towers)
        n += kernel.size();

    int widthField = 4 * minWidth + n * minWidth * 3;
    int heightField = minHeight * n;

    if (ui->label->height() > heightField)
        heightField = ui->label->height();

    if (ui->label->width() > widthField)
        widthField = ui->label->width();

    ui->label->setMinimumSize(widthField, heightField);

    QPixmap pixmap(widthField, heightField);
    QPainter painter(&pixmap);

    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(0,0, widthField, heightField);
    painter.setBrush(QBrush(Qt::red));
    int _x = minWidth;

    for (auto kernel : towers)
    {
        int y = heightField - minHeight;
        int x = _x;

        for(int i = 0; i < kernel.size(); i++)
        {
            int width = minWidth * (kernel[i] + 1);
            painter.drawRect(x, y, width, minHeight);
            y -= minHeight;

            if (kernel[i] != kernel.back())
                x += (width - minWidth * (kernel[i + 1] + 1)) / 2;
        }

        _x += minHeight + n * minWidth;
    }

    painter.end();

    ui->label->setPixmap(pixmap);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About", "Ametov Pavel Sergeevich\nGroup: 8-T3O-302B-16");
}

void MainWindow::newScene()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("New project"));

    auto *layout = new QFormLayout();

    auto *slider = new QSlider(Qt::Orientation::Horizontal, &dlg);
    slider->setTickInterval(5);
    slider->setSingleStep(1);
    slider->setMinimum(2);
    slider->setMaximum(30);
    slider->setTickPosition(QSlider::TicksBothSides);

    auto *label = new QLabel(&dlg);

    label->setText(QString::number(slider->value()));
    QObject::connect(slider,
                     &QSlider::valueChanged,
                     this,
                     [=](){label->setText(QString::number(slider->value()));});

    auto *btnBox = new QDialogButtonBox(&dlg);
    btnBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btnBox, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    layout->addRow(label);
    layout->addRow(slider);
    layout->addRow(btnBox);

    dlg.setLayout(layout);

    if(dlg.exec() == QDialog::Accepted)
    {
        auto result = slider->value();
        presenter->setN(result);
        ui->nLabel->setText(QString::number(result));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete presenter;
}
