#include "noutput.h"
#include <QDebug>

NOutput::NOutput(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent){
    initializeNode();
    initializeBoundingRect();
    initializePort();
}

void NOutput::initializeNode(){
    _title = QString("Output");
    _nodetype = outputNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "Out", this)};
    _out = QList<OutPort *>();
}

void NOutput::execute(){
    qDebug() << _in[0]->_connections[0]->_in->_data;
}
