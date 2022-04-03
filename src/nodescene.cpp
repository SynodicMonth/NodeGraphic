#include "nodescene.h"
#include <QDebug>

NodeScene::NodeScene(QWidget *parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(QRectF(0, 0, 3000, 3000));
    _hangingConnection = nullptr;
}

void NodeScene::_clearSelected(){
    for(int i = 0; i < this->selectedItems().length(); i++){
        this->selectedItems()[i]->setSelected(false);
    }
}

void NodeScene::dehangConnection(){
    removeItem(_hangingConnection);
    delete _hangingConnection;
    _hangingConnection = nullptr;
}

void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if(_hangingConnection){
        _hangingConnection->redrawHanging(mouseEvent->scenePos());
        //qDebug() << mouseEvent->pos();
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void NodeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(_hangingConnection){
        QList<QGraphicsItem *>mouseItems = items(event->scenePos());
        QGraphicsItem *topItem = mouseItems.size() > 1 ? mouseItems[1] : nullptr;
        if(topItem){
            if(_hangingConnection->_in && topItem->type() == InPort::Type){
                InPort *inPortItem = static_cast<InPort *>(topItem);
                if(_hangingConnection->_in->_parent != inPortItem->_parent){
                    _hangingConnection->_in->_connections.push_back(_hangingConnection);
                    inPortItem->_connections.push_back(_hangingConnection);
                    _hangingConnection->_out = inPortItem;
                    _hangingConnection->_outType = inPortItem->_datatype;
                    _hangingConnection->redraw();
                    _hangingConnection = nullptr;
                }else{
                    dehangConnection();
                }
            }else if(_hangingConnection->_out && topItem->type() == OutPort::Type){
                OutPort *outPortItem = static_cast<OutPort *>(topItem);
                if(_hangingConnection->_out->_parent != outPortItem->_parent){
                    _hangingConnection->_out->_connections.push_back(_hangingConnection);
                    outPortItem->_connections.push_back(_hangingConnection);
                    _hangingConnection->_in = outPortItem;
                    _hangingConnection->_inType = outPortItem->_datatype;
                    _hangingConnection->redraw();
                    _hangingConnection = nullptr;
                }else{
                    dehangConnection();
                }
            }else{
                dehangConnection();
            }
        }else{
            dehangConnection();
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}


void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(!_hangingConnection){
        QGraphicsItem *topItem = itemAt(event->scenePos(), QTransform());
        //qDebug() << topItem->type();
        if(topItem){
            if(topItem->type() == OutPort::Type){
                OutPort *outPortItem = static_cast<OutPort *>(topItem);
                _hangingConnection = new Connection(outPortItem, nullptr, outPortItem->getDatatype(), unknownData);
                addItem(_hangingConnection);
            }else if(topItem->type() == InPort::Type){
                InPort *inPortItem = static_cast<InPort *>(topItem);
                _hangingConnection = new Connection(nullptr, inPortItem, unknownData, inPortItem->getDatatype());
                addItem(_hangingConnection);
            }else{
                QGraphicsScene::mousePressEvent(event);
            }
        }
    }else{
        QGraphicsScene::mousePressEvent(event);
    }
}

void NodeScene::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete) {
        //qDebug() << "selected items " << selectedItems().size();
        while(!selectedItems().isEmpty()){
            QGraphicsItem *itemToRemove = selectedItems().front();
            removeItem(itemToRemove);
            delete itemToRemove;
        }
    }else{
        QGraphicsScene::keyPressEvent(event);
    }
}
