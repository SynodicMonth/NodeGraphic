#ifndef CONNECTION_H
#define CONNECTION_H

#include "port.h"
#include "nodedata.h"

class InPort;
class OutPort;

class Connection : public QGraphicsPathItem
{
public:
    Connection(OutPort *in, InPort *out, Datatype inType, Datatype outType, QGraphicsItem *parent = nullptr);
    ~Connection();
    void redrawHanging(QPointF mousePos);
    void redraw();
    QPointF getPosInScene();
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    OutPort *_in;
    InPort *_out;
    Datatype _inType, _outType;
    enum { Type = 65543 };
    int type() const{
        return Type;
    }

private:
    QRectF _boundingRect;
    QGraphicsItem *_parent;
};

#endif // CONNECTION_H
