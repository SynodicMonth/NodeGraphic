#ifndef NODEITEM_H
#define NODEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyle>
#include "nodescene.h"

class NodeItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    NodeItem(QString title, NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    QRectF _boundingRect;
    QString _title;
    QFont _font;

signals:
    void clearSelected();
};

#endif // NODEITEM_H
