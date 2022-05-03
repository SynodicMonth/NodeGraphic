#include "nodeview.h"
#include <QDebug>
NodeView::NodeView(NodeScene *scene, QLabel *imagePreview, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setAcceptDrops(true);
    setDragMode(NoDrag);
    _nodeScene = scene;
    _outNode = new NOutput(_nodeScene);
    _items.append(_outNode);
    _nodeScene->addItem(_outNode);
    _items.last()->setPos(mapToScene(1500, 1500));
    _solver = new GraphSolver(_outNode);
    _imagePreview = imagePreview;
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
    //QGraphicsItem * topitem = itemAt(event->pos());
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
    appendNode(itemName, event);
}

void NodeView::dragEnterEvent(QDragEnterEvent *event){
    event->accept();
}

void NodeView::dragMoveEvent(QDragMoveEvent *event){
    event->accept();
}

void NodeView::keyPressEvent(QKeyEvent *event){
    //excecute all
    if(event->key() == Qt::Key_E){
        _solver->solve();
        _imagePreview->setPixmap(QPixmap::fromImage(*(_outNode->_result->_image)).scaled(600, 600, Qt::KeepAspectRatio));
    }
    QGraphicsView::keyPressEvent(event);
}

void NodeView::appendNode(QString name, QDropEvent *event){
    //TODO: Extend this
    qDebug() << name;
    if(name.compare(QString("Image")) == 0){
        _items.append(new NImage(_nodeScene));
    }
//    else if(name.compare(QString("Output")) == 0){
//        _items.append(new NOutput(_nodeScene));
//    }
    else if(name.compare(QString("Add")) == 0){
        _items.append(new NAdd(_nodeScene));
    }else if(name.compare(QString("Diff")) == 0){
        _items.append(new NDiff(_nodeScene));
    }else if(name.compare(QString("Lut")) == 0){
        _items.append(new NLut(_nodeScene));
    }else if(name.compare(QString("Contrast")) == 0){
    _items.append(new NContrast(_nodeScene));
    }else{
        return;
    }
    _nodeScene->addItem(_items.last());
    _items.last()->setPos(mapToScene(event->pos()));
}
