#include "itemplanner.h"

ItemPlanner::ItemPlanner()
    : _time(QDateTime()),
      _summ(0),
      _label("")
{

}

ItemPlanner::ItemPlanner(QDateTime time, double summ, QString label)
{
    _time = time;
    _label = label;
    _summ = summ;
}

ItemPlanner::ItemPlanner(const ItemPlanner &item)
{
    _time = item._time;
    _label = item._label;
    _summ = item._summ;
}

ItemPlanner &ItemPlanner::operator=(const ItemPlanner &item)
{
    if (this != &item)
    {
        _time = item._time;
        _label = item._label;
        _summ = item._summ;
    }
    return *this;
}

bool ItemPlanner::operator==(const ItemPlanner &item) const
{
    auto isEqual = _time == item._time &&
                   _label == item._label &&
                   _summ == item._summ;
    return isEqual;
}

double ItemPlanner::getSumm() const
{
    return _summ;
}

QDateTime ItemPlanner::getDate() const
{
    return _time;
}

QString ItemPlanner::getLabel() const
{
    return _label;
}

ItemPlanner::~ItemPlanner()
{

}
