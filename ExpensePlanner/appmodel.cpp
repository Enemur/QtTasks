#include "appmodel.h"




AppModel::AppModel()
    : _items(QVector<ItemPlanner>()),
      _budget(0),
      _remainder(0)
{

}

void AppModel::calculate()
{
    double sum = 0;
    for(auto &item : _items)
        sum += item.getSumm();

    _remainder = _budget - sum;
    emit remainderChanged(_remainder);
}

void AppModel::setBuget(double buget)
{
    _budget = buget;
    calculate();
}

void AppModel::addItem(ItemPlanner item)
{
    _items.append(item);
    calculate();

    emit itemsChanged(_items);
}

void AppModel::open(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    if (file.isOpen())
    {
        try
        {
            in >> _budget >> _remainder >> _items;
        }
        catch(...)
        {
            _budget = 0;
            _remainder = 0;
            _items.clear();
        }

        emit itemsChanged(_items);
        emit remainderChanged(_remainder);
        emit budgetChanged(_budget);
    }

    file.close();
}

void AppModel::save(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    if (file.isOpen())
    {
        try
        {
            out << _budget << _remainder << _items;
        }
        catch(...)
        {
        }
    }

    file.close();
}

AppModel::~AppModel()
{

}
