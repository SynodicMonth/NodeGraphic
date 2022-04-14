#include "nimage.h"
#include <QDebug>

NImage::NImage(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent){
    initializeNode();
    initializeBoundingRect();
    initializePort();
}

void NImage::initializeNode(){
    _title = QString("Image");
    _nodetype = inputNode;
    _in = QList<InPort *>();
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "Image", this)};
}

void NImage::execute(){
    qDebug() << _title << " : 1";
    _out[0]->_data = new NodeData(1);
}
