#ifndef APPMODEL_H
#define APPMODEL_H

#include "itemplanner.h"

#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QObject>
#include <QVector>
#include <QDataStream>

class AppModel : public QObject
{
    Q_OBJECT
private:
    QVector<ItemPlanner> _items;
    double _budget;
    double _remainder;
private:
    void calculate();
public:
    AppModel();

    void setBuget(double buget);
    void addItem(ItemPlanner item);

    void open(QString filePath);
    void save(QString filePath);

    ~AppModel();

signals:
    void itemsChanged(const QVector<ItemPlanner>&);
    void remainderChanged(double);
    void budgetChanged(double);
};

#endif // APPMODEL_H
