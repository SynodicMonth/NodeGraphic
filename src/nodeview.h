#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMimeData>
#include <QScrollBar>
#include <QList>
#include "nodescene.h"
#include "nodeitem.h"

class NodeView : public QGraphicsView
{
public:
    explicit NodeView(NodeScene *scene, QWidget *parent = nullptr);
    ~NodeView();
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void appendNode(QString name, QDropEvent *event);
private:
    NodeScene *_nodeScene;
    QPointF _centerAnchor;
    QPoint _posAnchor;
    bool _isMousePressed = false;
    QList<NodeItem *> _items;
};

#endif // NODEVIEW_H
