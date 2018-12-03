#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>



class GraphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicScene(QObject *parent = nullptr);
    ~GraphicScene();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void mouseMoved(QPoint point);
    void mousePressed(QPoint point, QPoint globalPoint, Qt::MouseButton button);
    void mouseReleased();
};

#endif // GRAPHICSCENE_H
