#include "appmodel.h"

AppModel::AppModel()
    : _vertices(QVector<Vertex>()),
      _edges(QVector<Edge>())
{

}

void AppModel::createVertex()
{
    _vertices.append(Vertex(_point));
    emit sceneChanged(_vertices, _edges);
}

void AppModel::removeVertex()
{
    if (_selectedVertex != nullptr)
    {
        _vertices.removeOne(*_selectedVertex);
        emit sceneChanged(_vertices, _edges);
    }
}

void AppModel::clearVertices()
{
    _vertices.clear();
    emit sceneChanged(_vertices, _edges);
}

void AppModel::createEdge()
{
    Edge edge;

    _edges.append(edge);
    _selectedEdge = &edge;
}

void AppModel::removeEdge(Edge edge)
{
    _edges.removeOne(edge);
    _selectedVertex = nullptr;
}

const QVector<Vertex> &AppModel::getVertices()
{
    return _vertices;
}

void AppModel::setSelectedVertexLabel(const QString& label)
{
    if (_selectedVertex != nullptr)
    {
        _selectedVertex->setLabel(label);
        emit sceneChanged(_vertices, _edges);
    }
}

void AppModel::setClickPoint(const QPoint &point)
{
    _point = point;
}

void AppModel::selectVertex(const QPoint &point)
{
    bool alreadySelected = false;
    for (auto &vertex : _vertices)
        if (vertex.isPointInVertex(point) && !alreadySelected)
        {
            vertex.setSelected(true);
            _selectedVertex = &vertex;
            alreadySelected = true;
        }
        else
            vertex.setSelected(false);

    if (!alreadySelected)
        _selectedVertex = nullptr;

    emit sceneChanged(_vertices, _edges);
}

void AppModel::moveSelectedVertex(const QPoint &point)
{
    if (_selectedVertex != nullptr)
    {
        _selectedVertex->setCenter(point);
        emit sceneChanged(_vertices, _edges);
    }
}

AppModel::~AppModel()
{

}
