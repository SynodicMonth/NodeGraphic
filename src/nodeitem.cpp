#include "nodeitem.h"
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
    //_id = NodeItem::count++;
    initializeNode();
    QFontMetrics fontMetrics = QFontMetrics(_font);
    int titleWidth = fontMetrics.width(_title);
    int inPortWidth = 0, outPortWidth = 0;
    for(int i = 0; i < _in.size(); i++){
        inPortWidth = qMax(inPortWidth, fontMetrics.width(_in[i]->getName()));
    }
    for(int i = 0; i < _out.size(); i++){
        outPortWidth = qMax(outPortWidth, fontMetrics.width((_out[i]->getName())));
    }
    int nodeWidth = qMax(titleWidth + 20, inPortWidth + outPortWidth + 40);
    int nodeHeight = qMax(_in.size(), _out.size()) * LINEHEIGHT + LINEHEIGHT;
    _boundingRect = QRectF(0, 0, nodeWidth, nodeHeight);
    for(int i = 0; i < _in.size(); i++){
        _in[i]->setPos(5, (i + 1.5) * LINEHEIGHT - 5);
    }
    for(int i = 0; i < _out.size(); i++){
        _out[i]->setPos(_boundingRect.width() - 15, (i + 1.5) * LINEHEIGHT - 5);
    }

}

NodeItem::~NodeItem(){
    foreach (InPort *i, _in) {
        delete i;
    }
    foreach (OutPort *i, _out) {
        delete i;
    }
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
        //painter->setPen(Qt::black);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(_boundingRect.adjusted(pen.width() / 2, pen.width() / 2, -pen.width() / 2, -pen.width() / 2));
    }
}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        setSelected(true);
        //qDebug() << "selected";
        if(event->modifiers() != Qt::ShiftModifier){
            emit clearSelected();
        }
    }
    QGraphicsItem::mousePressEvent(event);
}

void NodeItem::initializeNode(){
    //TODO: OVERWRITE THIS
    _title = QString("TestNode");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "inNode1", this), new InPort(_scene, imageData, "inNode2", this), new InPort(_scene, imageData, "inNode333333333333333", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "outNode1", this), new OutPort(_scene, imageData, "outNode2", this)};
}
