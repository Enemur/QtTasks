#include "vertex.h"

Vertex::Vertex()
    : QObject(),
      _point(QPoint()),
      _isSelected(false),
      _label("")
{

}

Vertex::Vertex(QPoint point, QObject *parent)
    : QObject(parent),
      _isSelected(false),
      _label("")
{
    setCenter(point);
}

Vertex::Vertex(const Vertex &edge)
{
    _center = edge._center;
    _point = edge._point;
    _label = edge._label;
    _isSelected = edge._isSelected;
}

Vertex Vertex::operator=(const Vertex &edge)
{
    if (this != &edge)
    {
        _center = edge._center;
        _point = edge._point;
        _isSelected = edge._isSelected;
    }

    return *this;
}

bool Vertex::operator==(const Vertex &edge)
{
    auto isEqualLabel = _label == edge._label;
    auto isEqualPoint = _point == edge._point;

    return isEqualLabel && isEqualPoint;
}

bool Vertex::isPointInVertex(const QPoint &point) const
{
    auto line = qSqrt(qPow(point.x() - _center.x(), 2) + qPow(point.y() - _center.y(), 2));
    return line <= Radius;
}

void Vertex::setCenter(QPoint point)
{
    _center = point;
    _point = QPoint(_center.x() - Radius, _center.y() - Radius);
}

void Vertex::setLabel(QString label)
{
    _label = label;
}

QPoint Vertex::getPoint()
{
    return _point;
}

QPoint Vertex::getCenter()
{
    return _center;
}

QString Vertex::getLabel()
{
    return _label;
}

void Vertex::draw(QPainter &painter) const
{
    auto color = painter.background().color();
    if (_isSelected)
        painter.setBrush(QBrush(Qt::red));
    else
       painter.setBrush(QBrush(Qt::white));

    painter.drawEllipse(_center, Radius, Radius);
    painter.drawText(_center, _label);

    painter.setBrush(QBrush(color));
}

void Vertex::setSelected(bool isSelected)
{
    _isSelected = isSelected;
}

bool Vertex::getSelected()
{
    return _isSelected;
}

Vertex::~Vertex()
{

}
