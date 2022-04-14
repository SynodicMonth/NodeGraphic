#include "connection.h"

Connection::Connection(OutPort *in, InPort *out, Datatype inType, Datatype outType, QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
{
    _in = in;
    _out = out;
    _inType = inType;
    _outType = outType;
    _parent = parent;
    setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setZValue(5);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

Connection::~Connection(){
    if(_in) _in->_connections.removeAll(this);
    if(_out) _out->_connections.removeAll(this);
}

void Connection::redrawHanging(QPointF mousePos){
    //redraw a hanging connection to mousePos
    prepareGeometryChange();
    QPainterPath path;
    if(_in){
        path.moveTo(QPointF(_in->scenePos().x() + 5, _in->scenePos().y() + 5));
    }else{
        path.moveTo(QPointF(_out->scenePos().x() + 5, _out->scenePos().y() + 5));
    }
    path.lineTo(mousePos);
    setPath(path);
}

void Connection::redraw(){
    //redraw a non-hanging connection
    prepareGeometryChange();
    QPainterPath path;
    path.moveTo(QPointF(_in->scenePos().x() + 5, _in->scenePos().y() + 5));
    path.lineTo(QPointF(_out->scenePos().x() + 5, _out->scenePos().y() + 5));
    setPath(path);
}
