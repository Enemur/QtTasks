#include "edge.h"

Edge::Edge(QPoint firstPoint, QPoint secondPoint, EdgeTypes edgeType)
    : QObject(),
      _firstPoint(firstPoint),
      _secondPoint(secondPoint),
      _edgeType(edgeType)
{

}

Edge::Edge(EdgeTypes edgeType)
    : QObject(),
      _firstPoint(QPoint()),
      _secondPoint(QPoint()),
      _edgeType(edgeType)
{

}

Edge::Edge(const Edge &edge)
{
    _firstPoint = edge._firstPoint;
    _secondPoint = edge._secondPoint;
    _edgeType = edge._edgeType;
}

void Edge::draw(QPainter &painter) const
{
    QLineF line(_firstPoint, _secondPoint);
    painter.drawLine(_firstPoint, _secondPoint);
}

void Edge::setEdgeType(EdgeTypes edgeType)
{
    _edgeType = edgeType;
}

Edge Edge::operator=(const Edge &edge)
{
    if (this != &edge)
    {
        _firstPoint = edge._firstPoint;
        _secondPoint = edge._secondPoint;
        _edgeType = edge._edgeType;
    }
    return *this;
}

bool Edge::operator==(const Edge &edge)
{
    auto isEqualPoints = _firstPoint == edge._firstPoint &&
                         _secondPoint == edge._secondPoint;
    return isEqualPoints;
}

Edge::~Edge()
{

}
