#ifndef NODESCENE_H
#define NODESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "connection.h"

class Connection;
class Port;
class NodeItem;

class NodeScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit NodeScene(QStackedWidget *menus, QWidget *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dehangConnection();
    void hangConnection(Connection *connection);
    void keyPressEvent(QKeyEvent *event);
    void syncItems(QList<NodeItem *> *items);
    void drawBackground(QPainter *painter, const QRectF &rect);
    Connection *_hangingConnection;
    QStackedWidget *_menus;
    QList<NodeItem *> *_items;
private slots:
    void _clearSelected();
};

#endif // NODESCENE_H
