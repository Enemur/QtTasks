#ifndef EDGE_H
#define EDGE_H

#include <QObject>
#include <QPainter>
#include <QPoint>
#include "edgetype.h"

class Edge : public QObject
{
    Q_OBJECT
private:
    QPoint _firstPoint;
    QPoint _secondPoint;

    EdgeTypes _edgeType;
public:
    Edge(EdgeTypes edgeType = EdgeTypes::Undirected);
    Edge(QPoint firstPoint, QPoint secondPoint, EdgeTypes edgeType = EdgeTypes::Undirected);
    Edge(const Edge &edge);

    void draw(QPainter &painter) const;
    void setEdgeType(EdgeTypes edgeType);

    Edge operator=(const Edge& edge);
    bool operator==(const Edge& edge);

    ~Edge();
};

#endif // EDGE_H
