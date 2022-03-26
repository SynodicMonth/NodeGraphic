#include "nodeitem.h"

NodeItem::NodeItem(QString title, NodeScene *nodeScene, QGraphicsItem *parent)
    : QGraphicsItem(parent){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);
    _title = title;
    _font.setFamily("Microsoft YaHei");
    _font.setPointSize(30);
    QFontMetrics fontMetrics = QFontMetrics(_font);
    int nFontWidth = fontMetrics.width(title);
    _boundingRect = QRectF(0, 0, nFontWidth, 100);
    connect(this, SIGNAL(clearSelected()), nodeScene, SLOT(_clearSelected()));
}

QRectF NodeItem::boundingRect() const{
    return _boundingRect;
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(_boundingRect);
    if(!_title.isEmpty()){
        painter->setFont(_font);
        painter->setPen(Qt::black);
        painter->drawText(_boundingRect, _title);
    }
    //qDebug() << "print";
    if (option->state & QStyle::State_Selected){
        painter->setPen(Qt::black);
        //qDebug() << "isselected";
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(_boundingRect);
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
