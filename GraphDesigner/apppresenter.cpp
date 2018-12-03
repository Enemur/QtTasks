#include "apppresenter.h"


AppPresenter::AppPresenter()
    :_model(new AppModel()),
     _scene(new GraphicScene()),
     _menu(new QMenu()),
     _addVertex(new QAction("Create edge")),
     _menuOfVertex(new QMenu()),
     _removeVertex(new QAction("Remove edge")),
     _isClicked(false)
{
    _menu->addAction(_addVertex);

    _menuOfVertex->addAction(_removeVertex);
    setConnections();
}

void AppPresenter::setConnections()
{
    QObject::connect(_scene, &GraphicScene::mousePressed, this, &AppPresenter::onMousePressed);
    QObject::connect(_scene, &GraphicScene::mouseMoved, this, &AppPresenter::onMouseMoved);
    QObject::connect(_scene, &GraphicScene::mouseReleased, this, &AppPresenter::onMouseReleased);

    QObject::connect(_model, &AppModel::sceneChanged, this, &AppPresenter::onSceneChanged);

    QObject::connect(_addVertex, &QAction::triggered, _model, &AppModel::createVertex);

    QObject::connect(_removeVertex, &QAction::triggered, _model, &AppModel::removeVertex);
}

void AppPresenter::setVertexLabelEdit(QLineEdit *lineEdit)
{
    _vertexLabel = lineEdit;
}

void AppPresenter::setGraphicsView(QGraphicsView *graphics)
{
    _graphics = graphics;
    _graphics->setScene(_scene);

    QPixmap pixmap(_graphics->size());
    QPainter painter(&pixmap);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(_graphics->rect());
    painter.end();
    _scene->addPixmap(pixmap);
}

void AppPresenter::setVertexLabel()
{
    auto str = _vertexLabel->text();
    if (str != "")
        _model->setSelectedVertexLabel(str);
}

void AppPresenter::onSceneChanged(const QVector<Vertex>& vertices, const QVector<Edge>& edges)
{
    _scene->clear();
    QPixmap pixmap(_graphics->size());
    QPainter painter(&pixmap);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(_graphics->rect());
    painter.setBrush(QBrush(Qt::red));

    for (auto &vertex : vertices)
        vertex.draw(painter);

   for (auto &edge : edges)
       edge.draw(painter);

    painter.end();
    _scene->addPixmap(pixmap);
    _scene->update();
}

void AppPresenter::onMousePressed(QPoint point, QPoint globalPoint, Qt::MouseButton button)
{
    if (button == Qt::MouseButton::RightButton)
    {
        bool isSelected = false;
        for (const auto &vertex : _model->getVertices())
        {
            if (vertex.isPointInVertex(point))
                isSelected = true;
        }

        if (isSelected)
        {
            _model->selectVertex(point);
            _menuOfVertex->popup(globalPoint);
        }
        else
        {
            _menu->popup(globalPoint);
            _model->setClickPoint(point);
        }
    }
    else if (button == Qt::MouseButton::LeftButton)
    {
        _model->selectVertex(point);
        _isClicked = true;
    }

}

void AppPresenter::onMouseReleased()
{
    _isClicked = false;
}

AppPresenter::~AppPresenter()
{
    delete _model;
    delete _menu;
    delete _addVertex;
    delete _removeVertex;
}

void AppPresenter::onMouseMoved(QPoint point)
{
    auto isPointOnField = point.x() - Vertex::Radius > 0 && point.x() + Vertex::Radius < _graphics->width() &&
                          point.y() - Vertex::Radius > 0 && point.y() + Vertex::Radius < _graphics->height();

    if (_isClicked && isPointOnField)
        _model->moveSelectedVertex(point);
}
