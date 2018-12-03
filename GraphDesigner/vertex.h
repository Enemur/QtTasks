#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsObject>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <qmath.h>

class Vertex : public QObject
{
    Q_OBJECT
private:
    QPoint _point;
    QPoint _center;
    bool _isSelected;

    QString _label;
public:
    static const int Radius = 15;
    static const int Diameter = 2 * Radius;

    Vertex();
    explicit Vertex(QPoint point, QObject *parent = nullptr);
    Vertex(const Vertex &edge);
    Vertex operator=(const Vertex &edge);
    bool operator==(const Vertex &edge);

    bool isPointInVertex(const QPoint &point) const;

    void setCenter(QPoint point);
    void setLabel(QString label);

    QPoint getPoint();
    QPoint getCenter();
    QString getLabel();

    void draw(QPainter &painter) const;

    void setSelected(bool isSelected);
    bool getSelected();

    ~Vertex();
};

#endif // VERTEX_H
