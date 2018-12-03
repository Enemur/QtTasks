#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include <QVector>
#include "vertex.h"
#include "edgetype.h"
#include "edge.h"

class AppModel : public QObject
{
    Q_OBJECT
private:
    QVector<Vertex> _vertices;
    QVector<Edge> _edges;

    Vertex* _selectedVertex;
    Edge* _selectedEdge;

    QPoint _point;
public:
    AppModel();

    void createVertex();
    void removeVertex();
    void clearVertices();

    void selectVertex(const QPoint &point);
    void moveSelectedVertex(const QPoint& point);

    void createEdge();
    void removeEdge(Edge edge);

    const QVector<Vertex>& getVertices();

    void setSelectedVertexLabel(const QString& label);
    void setClickPoint(const QPoint& point);

    ~AppModel();
private slots:
signals:
     void sceneChanged(const QVector<Vertex> &, const QVector<Edge>&);
};

#endif // APPMODEL_H
