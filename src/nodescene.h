#ifndef NODESCENE_H
#define NODESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "connection.h"

class Connection;
class Port;

class NodeScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit NodeScene(QWidget *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dehangConnection();
    void keyPressEvent(QKeyEvent *event);
    Connection *_hangingConnection;

private slots:
    void _clearSelected();
};

#endif // NODESCENE_H