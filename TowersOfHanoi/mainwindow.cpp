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
    QPixmap pixmap(ui->label->width(), ui->label->height());
    QPainter painter(&pixmap);

    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(0,0, ui->label->width(), ui->label->height());
    painter.setBrush(QBrush(Qt::red));

    int height = 20;
    int _x = 0;
    int minWidth = 20;

    for (auto kernel : towers)
    {
        int y = ui->label->height();
        int x = _x;

        for(int i = 0; i < kernel.size(); i++)
        {
            int width = minWidth * (kernel[i] + 1);
            painter.drawRect(x, y, width, height);
            y -= height;
            width -= minWidth;

            if (i < kernel.size() - 1)
                x += width - minWidth * (kernel[i] + 2) / 2;
        }

        int tmp = 0;
        if (kernel.size() != 0)
            tmp += (kernel[0] + 1) * minWidth;

        _x = 50 + tmp;
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
    slider->setTickPosition(QSlider::TicksBothSides);

    auto *label = new QLabel(&dlg);

    QObject::connect(slider,
                     &QSlider::valueChanged,
                     this,
                     [=](){label->setText(std::to_string(slider->value()).c_str());});

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
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete presenter;
}
