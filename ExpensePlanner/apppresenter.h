#ifndef APPPRESENTER_H
#define APPPRESENTER_H

#include "appmodel.h"

#include <QDialog>
#include <QLabel>
#include <QObject>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QListWidget>
#include "ui_dialog.h"
#include <QFileDialog>

class AppPresenter : public QObject
{
    Q_OBJECT
private:
    AppModel* _model;

    QLabel* _remainderLabel;
    QLineEdit* _budgetEdit;
    QListWidget* _list;

    QDialog* _dialog;
    Ui_Dialog* _ui;
private:
    void setConnections();
    void createDialog();
    void showDialog();

    bool checkSumm();
    bool checkLabel();
    void chechDialogValues();
public:
    AppPresenter();

    void setRemainderLabel(QLabel* remainderLabel);
    void setBudgetEdit(QLineEdit* budgetEdit);
    void setListWidget(QListWidget* list);

    void addRate();
    void updateBudget();
    void save();
    void open();

    ~AppPresenter();
private slots:
    void onRemainderChanged(double remainder);
    void onItemsChanged(const QVector<ItemPlanner>& items);
    void onBudgetChanged(double budget);
};

#endif // APPPRESENTER_H
