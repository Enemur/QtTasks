#include "graphicscene.h"

GraphicScene::GraphicScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

void GraphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    auto point = event->scenePos();
    emit mouseMoved(point.toPoint());
}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    auto point = mouseEvent->scenePos();
    emit mousePressed(point.toPoint(), mouseEvent->screenPos(), mouseEvent->button());
}

void GraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseReleased();
    Q_UNUSED(event);
}

GraphicScene::~GraphicScene()
{

}
