#include "port.h"
#include <QDebug>

Port::Port(NodeScene *scene, Datatype datatype, QString name, NodeItem *parent) :
    QGraphicsItem(parent)
{
    _scene = scene;
    _datatype = datatype;
    _name = name;
    _parent = parent;
    _boundingRect = QRectF(0, 0, 10, 10);
    setZValue(10);
    setFlag(ItemSendsScenePositionChanges);
    //_hangingConnection = nullptr;
}

Port::~Port(){
    foreach (Connection *i, _connections) {
        delete i;
    }
}

QString Port::getName() const{
    return _name;
}
Datatype Port::getDatatype() const{
    return _datatype;
}
QRectF Port::boundingRect() const{
    return _boundingRect;
}

void Port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QBrush fillBlack;
    fillBlack.setColor(Qt::black);
    fillBlack.setStyle(Qt::SolidPattern);
    painter->setBrush(fillBlack);
    painter->drawEllipse(QPoint(5, 5), 5, 5);
}

void Port::redraw(){
    for(int i = 0; i < _connections.size(); i++){
        _connections[i]->redraw();
    }
}

QVariant Port::itemChange(GraphicsItemChange change, const QVariant &value){
    qDebug() << "changed" << value;
    if(change == QGraphicsItem::ItemScenePositionHasChanged){
        redraw();
    }
    return QGraphicsItem::itemChange(change, value);
}

//int Port::type() const{
//    return Type;
//}

//QPointF Port::getPosInScene(){
//    return mapToScene(pos());
//}

//void Port::mousePressEvent(QGraphicsSceneMouseEvent *event){
//    Connection *hangingConnection = new Connection(this, nullptr, )
//}

InPort::InPort(NodeScene *scene, Datatype datatype, QString name, NodeItem *parent)
    : Port(scene, datatype, name, parent)
{

}

InPort::~InPort(){

}

//int InPort::type() const{
//    return 65537;
//}
//void InPort::mousePressEvent(QGraphicsSceneMouseEvent *event){
//    _scene->_hangingConnection = new Connection(this, nullptr, _datatype, unknownData);
//    _scene->addItem(_scene->_hangingConnection);
//}

OutPort::OutPort(NodeScene *scene, Datatype datatype, QString name, NodeItem *parent)
    : Port(scene, datatype, name, parent)
{
    _data = nullptr;
}

OutPort::~OutPort(){
    if(_data) delete _data;
}
//int OutPort::type() const{
//    return 65538;
//}
//void OutPort::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
//    qDebug() << "Item";
//    if(_scene->_hangingConnection){
//        _scene->_hangingConnection->_in->_connections.push_back(_scene->_hangingConnection);
//        _connections.push_back(_scene->_hangingConnection);
//        _scene->_hangingConnection = nullptr;
//    }
//}
