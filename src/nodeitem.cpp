#include "nodeitem.h"
#include <QDebug>
#define LINEHEIGHT 50

NodeItem::NodeItem(NodeScene *nodeScene, QGraphicsItem *parent)
    : QGraphicsItem(parent){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);
    _scene = nodeScene;
    _title = "N/A";
    _font.setFamily("Microsoft YaHei");
    _font.setPointSize(20);
    connect(this, SIGNAL(clearSelected()), nodeScene, SLOT(_clearSelected()));
    _menu = new QWidget();
    _layout = new QGridLayout();
    _layout->setColumnStretch(0, 1);
    _layout->setColumnStretch(1, 3);
    _layout->setAlignment(Qt::AlignTop);
    _menu->setLayout(_layout);
    _isReady = false;
    //_id = NodeItem::count++;
}

NodeItem::~NodeItem(){
    foreach (InPort *i, _in) {
        delete i;
    }
    foreach (OutPort *i, _out) {
        delete i;
    }
    delete _layout;
    delete _menu;
}

QRectF NodeItem::boundingRect() const{
    return _boundingRect;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(_boundingRect);
    painter->setFont(_font);
    painter->setPen(Qt::black);
    painter->drawText(QRect(0, 0, _boundingRect.width(), LINEHEIGHT), Qt::AlignCenter, _title);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawLine(0, LINEHEIGHT, _boundingRect.width(), LINEHEIGHT);
    for(int i = 0; i < _in.size(); i++){
        painter->drawText(QRect(20, (i + 1) * LINEHEIGHT, _boundingRect.width() - 40, LINEHEIGHT), Qt::AlignVCenter | Qt::AlignLeft, _in[i]->getName());
    }
    for(int i = 0; i < _out.size(); i++){
        painter->drawText(QRect(20, (i + 1) * LINEHEIGHT, _boundingRect.width() - 40, LINEHEIGHT), Qt::AlignVCenter | Qt::AlignRight, _out[i]->getName());
    }
    if (option->state & QStyle::State_Selected){
        //item is selected
        //painter->setPen(Qt::black);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(_boundingRect.adjusted(pen.width() / 2, pen.width() / 2, -pen.width() / 2, -pen.width() / 2));
    }
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        setSelected(true);
        if(event->modifiers() != Qt::ShiftModifier){
            emit clearSelected();
        }
    }
    updateMenu();
    QGraphicsItem::mousePressEvent(event);
}

void NodeItem::initializeNode(){
    //TODO: OVERWRITE THIS
    _title = QString("TestNode");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "inNode1", this), new InPort(_scene, imageData, "inNode2", this), new InPort(_scene, imageData, "inNode3", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "outNode1", this), new OutPort(_scene, imageData, "outNode2", this)};
}

void NodeItem::initializeBoundingRect(){
    QFontMetrics fontMetrics = QFontMetrics(_font);
    int titleWidth = fontMetrics.width(_title);
    int inPortWidth = 0, outPortWidth = 0;
    for(int i = 0; i < _in.size(); i++){
        inPortWidth = qMax(inPortWidth, fontMetrics.width(_in[i]->getName()));
    }
    for(int i = 0; i < _out.size(); i++){
        outPortWidth = qMax(outPortWidth, fontMetrics.width((_out[i]->getName())));
    }
    int nodeWidth = qMax(titleWidth + 20, inPortWidth + outPortWidth + 40 + 5);
    int nodeHeight = qMax(_in.size(), _out.size()) * LINEHEIGHT + LINEHEIGHT;
    _boundingRect = QRectF(0, 0, nodeWidth, nodeHeight);
}

void NodeItem::initializePort(){
    for(int i = 0; i < _in.size(); i++){
        _in[i]->setPos(5, (i + 1.5) * LINEHEIGHT - 5);
    }
    for(int i = 0; i < _out.size(); i++){
        _out[i]->setPos(_boundingRect.width() - 15, (i + 1.5) * LINEHEIGHT - 5);
    }
}

void NodeItem::execute(){
    if(_nodetype != inputNode){
        for(int i = 0; i < _in.size(); i++){
            qDebug() << _in[i]->_connections[0]->_in->_data;
        }
    }
    qDebug() << _title;
    for(int i = 0; i < _out.size(); i++){
        for(int j = 0; j < _out[i]->_connections.size(); j++){
            _out[i]->_data = new NodeData(_title);
        }
        qDebug() << _out[i]->_data;
    }
}

void NodeItem::initializeMenu(){
    _scene->_menus->addWidget(_menu);
    updateMenu();
}

void NodeItem::updateMenu() const{
    _scene->_menus->addWidget(_menu);
    _scene->_menus->setCurrentWidget(_menu);
}

NodeData* NodeItem::importData(int nodeNum){
    if(!_in[nodeNum]->_connections.isEmpty() && _in[nodeNum]->_connections[0]->_in->_data){
        return _in[nodeNum]->_connections[0]->_in->_data;
    }else{
        return nullptr;
    }
}

void NodeItem::exportData(int nodeNum, NodeData* data){
    _out[nodeNum]->_data = data;
}
