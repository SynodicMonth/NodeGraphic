#include "nadd.h"
#include <QDebug>

NAdd::NAdd(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent)
{
    initializeNode();
    initializeBoundingRect();
    initializePort();
}

void NAdd::initializeNode(){
    _title = QString("Add");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in1", this),
                          new InPort(_scene, imageData, "in2", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
}

void NAdd::execute(){
    _out[0]->_data = new NodeData(_in[0]->_connections[0]->_in->_data->_int + _in[1]->_connections[0]->_in->_data->_int);
    qDebug() << _title << " : " << _in[0]->_connections[0]->_in->_data->_int + _in[1]->_connections[0]->_in->_data->_int;
}
