#include "mainwindowpresenter.h"

#include <QStringListModel>

MainWindowPresenter::MainWindowPresenter()
    :_model(new MainWindowModel),
      _listViewModel(new QStringListModel())
{
    QObject::connect(_model, &MainWindowModel::logsChanged, this, &MainWindowPresenter::onLogsChanged);
    QObject::connect(_model, &MainWindowModel::logsClear, this, &MainWindowPresenter::onLogsClear);
    QObject::connect(_model, &MainWindowModel::towersChanged, this, &MainWindowPresenter::onTowersChanged);
}

void MainWindowPresenter::executeButtonAction(Buttons button)
{
    _model->executeButtonAction(button);
}

void MainWindowPresenter::setListView(QListView *listView)
{
    _listView = listView;
    _listView->setModel(_listViewModel);
}

void MainWindowPresenter::setN(int n)
{
    _model->setN(n);
}

void MainWindowPresenter::onLogsChanged(const QString &message)
{
    auto row = _listViewModel->rowCount();
    _listViewModel->insertRows(row, 1);
    auto index = _listViewModel->index(row);
    _listViewModel->setData(index, message);
}

void MainWindowPresenter::onLogsClear()
{
    _listViewModel->removeRows(0, _listViewModel->rowCount());
}

void MainWindowPresenter::onTowersChanged(const QVector<QVector<int> > &towers)
{
    emit towersChanged(towers);
}

MainWindowPresenter::~MainWindowPresenter()
{
    delete _model;
    delete _listViewModel;
}
