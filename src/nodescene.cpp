#include "nodescene.h"
#include <QDebug>

NodeScene::NodeScene(QStackedWidget *menus, QWidget *parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(QRectF(0, 0, 3000, 3000));
    _hangingConnection = nullptr;
    _menus = menus;
}

void NodeScene::_clearSelected(){
    for(int i = 0; i < this->selectedItems().length(); i++){
        this->selectedItems()[i]->setSelected(false);
    }
}

void NodeScene::dehangConnection(){
    //remove current hangingConnection
    removeItem(_hangingConnection);
    delete _hangingConnection;
    _hangingConnection = nullptr;
}

void NodeScene::hangConnection(Connection *connection){
    //handle connection to hangingConnection
    connection->_out = nullptr;
    connection->_outType = unknownData;
    _hangingConnection = connection;
}

void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if(_hangingConnection){
        _hangingConnection->redrawHanging(mouseEvent->scenePos());
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

QGraphicsItem* getFirstPortItem(QList<QGraphicsItem *> &mouseItems){
    //get the first port (InPort/OutPort) item in QGraphicsItem list
    for(int i = 0;i < mouseItems.size(); i++){
        if(mouseItems[i]->type() == OutPort::Type || mouseItems[i]->type() == InPort::Type){
            return mouseItems[i];
        }
    }
    return nullptr;
}

void NodeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(_hangingConnection){
        QList<QGraphicsItem *>mouseItems = items(event->scenePos());
        QGraphicsItem *topItem = getFirstPortItem(mouseItems);
        if(topItem){
            if(_hangingConnection->_in && topItem->type() == InPort::Type){
                InPort *inPortItem = static_cast<InPort *>(topItem);
                if(_hangingConnection->_in->_parent != inPortItem->_parent && inPortItem->_connections.isEmpty()){
                    //not the same node and inport has no connection
                    //connect to port
                    _hangingConnection->_in->_connections.push_back(_hangingConnection);
                    inPortItem->_connections.push_back(_hangingConnection);
                    _hangingConnection->_out = inPortItem;
                    _hangingConnection->_outType = inPortItem->_datatype;
                    _hangingConnection->redraw();
                    _hangingConnection = nullptr;
                }else{
                    //no port to cennect, remove current hangingConnection
                    dehangConnection();
                }
            }else if(_hangingConnection->_out && topItem->type() == OutPort::Type){
                OutPort *outPortItem = static_cast<OutPort *>(topItem);
                if(_hangingConnection->_out->_parent != outPortItem->_parent){
                    //not the same node
                    //connect to port
                    _hangingConnection->_out->_connections.push_back(_hangingConnection);
                    outPortItem->_connections.push_back(_hangingConnection);
                    _hangingConnection->_in = outPortItem;
                    _hangingConnection->_inType = outPortItem->_datatype;
                    _hangingConnection->redraw();
                    _hangingConnection = nullptr;
                }else{
                    //no port to cennect, remove current hangingConnection
                    dehangConnection();
                }
            }else{
                //no port to cennect, remove current hangingConnection
                dehangConnection();
            }
        }else{
            dehangConnection();
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QList<QGraphicsItem *>mouseItems = items(event->scenePos());
    QGraphicsItem *topItem = getFirstPortItem(mouseItems);
    if(topItem){
        if(topItem->type() == OutPort::Type){
            //new connection
            OutPort *outPortItem = static_cast<OutPort *>(topItem);
            _hangingConnection = new Connection(outPortItem, nullptr, outPortItem->getDatatype(), unknownData);
            addItem(_hangingConnection);
        }else if(topItem->type() == InPort::Type){
            InPort *inPortItem = static_cast<InPort *>(topItem);
            if(!inPortItem->_connections.isEmpty()){
                //reconnect connection
                hangConnection(inPortItem->_connections[0]);
                inPortItem->_connections.removeFirst();
            }else{
                //new connection
                _hangingConnection = new Connection(nullptr, inPortItem, unknownData, inPortItem->getDatatype());
                addItem(_hangingConnection);
            }
        }else{
            QGraphicsScene::mousePressEvent(event);
        }
    }else{
        QGraphicsScene::mousePressEvent(event);
    }
}

void NodeScene::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete){
        //delete selected item(s)
        QList<QGraphicsItem *>selectedItems = this->selectedItems();
        for(QGraphicsItem *item : selectedItems){
            if(item->type() == 65550){
                continue;
            }
            if(item->type() == NodeItem::Type){
                _items->removeOne(static_cast<NodeItem *>(item));
            }
            removeItem(item);
            delete item;
        }
    }
}


void NodeScene::syncItems(QList<NodeItem *> *items){
    _items = items;
}
