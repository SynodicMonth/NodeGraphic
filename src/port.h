#ifndef PORT_H
#define PORT_H

#include "nodedata.h"
#include "nodeitem.h"

class Connection;
class NodeItem;
class NodeScene;

class Port : public QGraphicsItem
{
public:
    Port(NodeScene *scene, Datatype datatype, QString name, NodeItem *parent = nullptr);
    ~Port();
    QString getName() const;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    Datatype getDatatype() const;
    void redraw();
    enum { Type = 65539 };
    int type() const{
        return Type;
    }

//protected:
    QList<Connection *> _connections;
    QRectF _boundingRect;
    NodeScene *_scene;
    NodeItem *_parent;
    Datatype _datatype;
    QString _name;
    //Connection *_hangingConnection;
};

class InPort : public Port
{
public:
    InPort(NodeScene *scene, Datatype datatype, QString name, NodeItem *parent = nullptr);
    ~InPort();
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    enum { Type = 65540 };
    int type() const{
        return Type;
    }
};

class OutPort : public Port
{
public:
    OutPort(NodeScene *scene, Datatype datatype, QString name, NodeItem *parent = nullptr);
    ~OutPort();
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    enum { Type = 65541 };
    int type() const{
        return Type;
    }
//private:
    NodeData *_data;
};



#endif // PORT_H
