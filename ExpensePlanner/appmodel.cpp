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
AppModel::~AppModel()
{

}
