#ifndef ITEMPLANNER_H
#define ITEMPLANNER_H

#include <QObject>
#include <QDateTime>

class ItemPlanner : public QObject
{
    Q_OBJECT
private:
    QDateTime _time;
    double _summ;
    QString _label;
public:
    ItemPlanner();
    ItemPlanner(QDateTime time, double summ, QString label);

    ItemPlanner(const ItemPlanner& item);

    ItemPlanner& operator=(const ItemPlanner& item);
    bool operator==(const ItemPlanner& item) const;

    template<typename Stream>
    friend Stream& operator>>(Stream& stream, ItemPlanner &planer)
    {
        stream >> planer._time >> planer._summ >> planer._label;
        return stream;
    }

    template<typename Stream>
    friend Stream& operator<<(Stream& stream, const ItemPlanner &planer)
    {
        stream << planer._time << planer._summ << planer._label;
        return stream;
    }

    double getSumm() const;
    QDateTime getDate() const;
    QString getLabel() const;

    ~ItemPlanner();
};

#endif // ITEMPLANNER_H
