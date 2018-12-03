#ifndef APPPRESENTER_H
#define APPPRESENTER_H

#include "appmodel.h"
#include "graphicscene.h"
#include <QLabel>
#include <QGraphicsView>
#include <QLineEdit>
#include "vertex.h"
#include <QMenu>
#include <QMessageBox>


class AppPresenter : public QObject
{
    Q_OBJECT
private:
    AppModel* _model;

    QLineEdit* _vertexLabel;

    QGraphicsView* _graphics;
    GraphicScene* _scene;

    QMenu* _menu;
    QAction* _addVertex;

    QMenu* _menuOfVertex;
    QAction* _removeVertex;
    bool _isClicked;

    void setConnections();
public:
    AppPresenter();

    void setVertexLabelEdit(QLineEdit* lineEdit);
    void setGraphicsView(QGraphicsView* graphics);
    void createEdge();

    void setVertexLabel();

    ~AppPresenter();
private slots:
    void onMouseMoved(QPoint point);
    void onMousePressed(QPoint point, QPoint globalPoint, Qt::MouseButton button);
    void onMouseReleased();

    void onSceneChanged(const QVector<Vertex>& vertices, const QVector<Edge>& edges);
};

#endif // APPPRESENTER_H
