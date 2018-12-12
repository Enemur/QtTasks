#include "apppresenter.h"


AppPresenter::AppPresenter()
    : _model(new AppModel()),
      _dialog(new QDialog()),
      _ui(new Ui_Dialog())
{
    setConnections();
    createDialog();
}

void AppPresenter::setConnections()
{
    QObject::connect(_model, &AppModel::remainderChanged, this, &AppPresenter::onRemainderChanged);
    QObject::connect(_model, &AppModel::itemsChanged, this, &AppPresenter::onItemsChanged);
    QObject::connect(_model, &AppModel::budgetChanged, this, &AppPresenter::onBudgetChanged);
}

void AppPresenter::createDialog()
{
    _ui->setupUi(_dialog);

    QObject::connect(_ui->labelEdit, &QLineEdit::textChanged, this, &AppPresenter::checkLabel);
    QObject::connect(_ui->sumEdit, &QLineEdit::textChanged, this, &AppPresenter::checkSumm);

    QObject::connect(_ui->okBtn, &QPushButton::clicked, this, &AppPresenter::chechDialogValues);
    QObject::connect(_ui->cancelBtn, &QPushButton::clicked, _dialog, &QDialog::reject);
}

void AppPresenter::showDialog()
{
    _ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    _ui->dateEdit->setMinimumDateTime(QDateTime::currentDateTime());

    if(_dialog->exec() == QDialog::Accepted)
    {
        auto summ = _ui->sumEdit->text().toDouble();
        ItemPlanner item(_ui->dateEdit->dateTime(), summ, _ui->labelEdit->text());
        _model->addItem(item);
    }
}

void AppPresenter::setRemainderLabel(QLabel *remainderLabel)
{
    _remainderLabel = remainderLabel;
}

void AppPresenter::setBudgetEdit(QLineEdit* budgetEdit)
{
    _budgetEdit = budgetEdit;
}

void AppPresenter::setListWidget(QListWidget *list)
{
    _list = list;
}

bool AppPresenter::checkSumm()
{
    QPalette palet;

    auto str = _ui->sumEdit->text();
    bool isOk;
    auto number = str.toDouble(&isOk);

    if (number <= 0)
        isOk = false;

    if (isOk)
        palet.setColor(_ui->sumEdit->foregroundRole(), Qt::black);
    else
        palet.setColor(_ui->sumEdit->foregroundRole(), Qt::red);

    _ui->sumEdit->setPalette(palet);
    return isOk;
}

bool AppPresenter::checkLabel()
{
    QPalette palet;
    QRegExp rg("^ | $");
    auto labelEditStr = _ui->labelEdit->text();
    auto isOkLabel = rg.indexIn(labelEditStr) == -1;

    if (isOkLabel)
        palet.setColor(_ui->sumEdit->foregroundRole(), Qt::black);
    else
        palet.setColor(_ui->sumEdit->foregroundRole(), Qt::red);

    _ui->labelEdit->setPalette(palet);

    return isOkLabel;
}

void AppPresenter::chechDialogValues()
{
    auto isOkSumm = checkSumm();
    auto isOkLabel = checkLabel();

    if (isOkSumm && isOkLabel)
        _dialog->accept();
}

void AppPresenter::addRate()
{
    showDialog();
}

void AppPresenter::updateBudget()
{
    bool isOk;
    auto budget = _budgetEdit->text().toDouble(&isOk);
    if (isOk)
        _model->setBuget(budget);
}

void AppPresenter::save()
{
    auto filePath = QFileDialog::getSaveFileName();
    _model->save(filePath);
}

void AppPresenter::open()
{
    auto filePath = QFileDialog::getOpenFileName();
    _model->open(filePath);
}

void AppPresenter::onRemainderChanged(double remainder)
{
    QPalette palette;

    if (remainder < 0)
        palette.setColor(_remainderLabel->foregroundRole(), Qt::red);
    else
        palette.setColor(_remainderLabel->foregroundRole(), Qt::green);

    _remainderLabel->setPalette(palette);
    _remainderLabel->setText(QString::number(remainder));
}

void AppPresenter::onItemsChanged(const QVector<ItemPlanner> &items)
{
    _list->clear();

    for (auto &item : items)
        _list->addItem("Date: " + item.getDate().toString() + ", label" + item.getLabel() + ", summ: " +QString::number(item.getSumm()));
}

void AppPresenter::onBudgetChanged(double budget)
{
    _budgetEdit->setText(QString::number(budget));
}

AppPresenter::~AppPresenter()
{
    delete _model;
    delete _dialog;
    delete _ui;
}
