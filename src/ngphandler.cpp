#include "ngphandler.h"
#include <QDebug>

NGPHandler::NGPHandler(NodeScene *scene, NodeView *view)
{
    _scene = scene;
    _view = view;
}

void NGPHandler::save(QString filename){
    if(!filename.isNull()){
        QFile file(filename);
        bool isReady = file.open(QIODevice::WriteOnly);
        if(isReady){
            QList<QGraphicsItem *> itemList = _scene->items();
            QList<NodeItem *> nodeitems;
            QList<Connection *> connections;
            NOutput *output;
            for(QGraphicsItem *item : itemList){
                if(item->type() == NodeItem::Type){
                    nodeitems.push_back(static_cast<NodeItem *>(item));
                }else if(item->type() == Connection::Type){
                    connections.push_back(static_cast<Connection *>(item));
                }else if(item->type() == NOutput::Type){
                    output = static_cast<NOutput *>(item);
                }
            }
            QTextStream filestream(&file);
            filestream << output->_title << ' ' << output->pos().x() << ' ' << output->pos().y() << endl;
            filestream << nodeitems.size() << endl;
            for(NodeItem *item : nodeitems){
                filestream << item->_title << ' ' << item->pos().x() << ' ' << item->pos().y() << endl;
            }
            filestream << connections.size() << endl;
            for(Connection *con : connections){
                filestream << nodeitems.indexOf(con->_in->_parent) << ' '
                           << con->_in->_parent->_out.indexOf(con->_in) << ' '
                           << nodeitems.indexOf(con->_out->_parent) << ' '
                           << con->_out->_parent->_in.indexOf(con->_out) << endl;
            }
        }
    file.close();
    }
}

void NGPHandler::open(QString filename){
    if(!filename.isNull()){
        QFile file(filename);
        bool isReady = file.open(QIODevice::ReadOnly);
        if(isReady){
            QTextStream filestream(&file);
            QString title;
            int x, y;
            filestream >> title >> x >> y;
            _view->_outNode->setPos(x, y);
            int nItems, nConnections;
            filestream >> nItems;
            for(int i = 0; i < nItems; i++){
                filestream >> title >> x >> y;
                _view->appendNode(title, QPointF(x, y));
                qDebug() << _view->_items.size();
            }
            filestream >> nConnections;
            int fromNode, fromPort, toNode, toPort;
            qDebug() << _view->_items.size();
            for(int i = 0; i < nConnections; i++){
                filestream >> fromNode >> fromPort >> toNode >> toPort;
                if(toNode >= 0){
                    Connection *con = new Connection(_view->_items[fromNode+1]->_out[fromPort], _view->_items[toNode+1]->_in[toPort], unknownData, unknownData);
                    _scene->addItem(con);
                    con->_in->_connections.push_back(con);
                    con->_out->_connections.push_back(con);
                    con->redraw();
                }else{
                    Connection *con = new Connection(_view->_items[fromNode+1]->_out[fromPort], _view->_outNode->_in[0], unknownData, unknownData);
                    _scene->addItem(con);
                    con->_in->_connections.push_back(con);
                    con->_out->_connections.push_back(con);
                    con->redraw();
                }
            }
        }
    file.close();
    }
}
