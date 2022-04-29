#ifndef NODEITEM_H
#define NODEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QList>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QStackedWidget>
#include <QPainter>
#include <QLineEdit>
#include <QStyle>
#include <QLabel>
#include <QGridLayout>
#include "nodescene.h"
#include "port.h"

enum Nodetype{
    inputNode, functionNode, outputNode
};

class Port;
class InPort;
class OutPort;
class NodeScene;

class NodeItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    NodeItem(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NodeItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void updateMenu() const;
    NodeData* importData(int nodeNum);
    void exportData(int nodeNum, NodeData* data);
    virtual void initializeNode();
    virtual void initializeBoundingRect();
    virtual void initializePort();
    virtual void initializeMenu();
    virtual void execute();
    //static unsigned int count;

//protected:
    NodeScene *_scene;
    QRectF _boundingRect;
    QString _title;
    QFont _font;
    QList<InPort *> _in;
    QList<OutPort *> _out;
    int _id;
    Nodetype _nodetype;
    QWidget *_menu;
    QGridLayout *_layout;
    QStackedWidget *_pmenus;
    bool _isReady;

signals:
    void clearSelected();
};

//unsigned int NodeItem::count = 0;

#endif // NODEITEM_H
