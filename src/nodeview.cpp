#include "nodeview.h"

NodeView::NodeView(NodeScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setAcceptDrops(true);
    setDragMode(RubberBandDrag);
    _nodeScene = scene;
}

NodeView::~NodeView(){
}

void NodeView::wheelEvent(QWheelEvent *event){
    if(event->modifiers() == Qt::AltModifier){
        // 获取当前鼠标相对于view的位置;
        QPointF cursorPoint = event->pos();
        // 获取当前鼠标相对于scene的位置;
        QPointF scenePos = this->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));
        // 获取view的宽高;
        qreal viewWidth = this->viewport()->width();
        qreal viewHeight = this->viewport()->height();
        // 获取当前鼠标位置相当于view大小的横纵比例;
        qreal hScale = cursorPoint.x() / viewWidth;
        qreal vScale = cursorPoint.y() / viewHeight;
        // 当前放缩倍数;
        //qreal scaleFactor = this->matrix().m11();
        int wheelDeltaValue = event->delta();
        // 向上滚动，放大;
        if (wheelDeltaValue > 0){
            this->scale(1.2, 1.2);
        }else{
            this->scale(1.0 / 1.2, 1.0 / 1.2);
        }
        // 将scene坐标转换为放大缩小后的坐标;
        QPointF viewPoint = this->matrix().map(scenePos);
        // 通过滚动条控制view放大缩小后的展示scene的位置;
        horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
        verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));
    }
}

void NodeView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton){
        _centerAnchor = mapToScene(QPoint(viewport()->width() / 2.0, viewport()->height() / 2.0));
        _posAnchor = event->pos();
        _isMousePressed = true;
    }else{
        QGraphicsView::mousePressEvent(event);
    }
}

void NodeView::mouseMoveEvent(QMouseEvent *event)
{
    if(_isMousePressed){
        QPointF offsetPos = QPointF(event->pos() - _posAnchor);
        offsetPos /= matrix().m11();
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        //setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        centerOn(_centerAnchor - offsetPos);
    }else{
        QGraphicsView::mouseMoveEvent(event);
    }
}

void NodeView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton){
        _isMousePressed = false;
    }else{
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void NodeView::dropEvent(QDropEvent *event){
    QByteArray data = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
    int startPos = 26;
    QString itemName;
    for(;startPos < data.length(); startPos += 2){
        itemName.append(data.at(startPos));
    }
    //items.append(new NodeItem(itemName, nodeScene));
    appendNode(itemName, event);
}

void NodeView::dragEnterEvent(QDragEnterEvent *event){
//    if(!(event->mimeData()->text().isEmpty())){
//        event->accept();
//    }
    event->accept();
}

void NodeView::dragMoveEvent(QDragMoveEvent *event){
    event->accept();
}

void NodeView::appendNode(QString name, QDropEvent *event){
    if(name.compare(QString("Image")) == 0){
        _items.append(new NodeItem(QString("Image"), _nodeScene));
        _nodeScene->addItem(_items.last());
        _items.last()->setPos(mapToScene(event->pos()));
    }
}
