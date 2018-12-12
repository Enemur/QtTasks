#ifndef APPMODEL_H
#define APPMODEL_H

#include "itemplanner.h"

#include <QObject>
#include <QVector>


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

    ~AppModel();

signals:
    void itemsChanged(const QVector<ItemPlanner>&);
    void remainderChanged(double);
};

#endif // APPMODEL_H
