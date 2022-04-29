#include "noutput.h"
#include <QDebug>

NOutput::NOutput(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent){
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

void NOutput::initializeNode(){
    _title = QString("Output");
    _nodetype = outputNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "Out", this)};
    _out = QList<OutPort *>();
    _nullImage = new QImage(":/tex/NullImage.png");
    _nullData = new NodeData(_nullImage);
}

void NOutput::execute(){
    //qDebug() << _in[0]->_connections;
    _result = importData(0);
    if(_result){
        qDebug() << _title << ": " << _result->_image;
        _dimension->setText(QString::number(_result->_image->size().width()) + "x" + QString::number(_result->_image->size().height()));
    }else{
        _result = _nullData;
        qDebug() << _title << ": NULL";
    }
}

void NOutput::initializeMenu(){
    _label = new QLabel(tr("Output Dimension"));
    _dimension = new QLabel();
    _layout->addWidget(_label, 0, 0);
    _layout->addWidget(_dimension, 0, 1);
    _scene->_menus->addWidget(_menu);
    updateMenu();
}
