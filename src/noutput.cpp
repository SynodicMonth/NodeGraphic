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
    if((!(_in[0]->_connections.isEmpty())) && _in[0]->_connections[0]){
        _result = _in[0]->_connections[0]->_in->_data;
        if(_result){
            qDebug() << _title << ": " << _result->_image;
        }else{
            _result = _nullData;
            qDebug() << _title << ": NULL";
        }
    }else{
        _result = _nullData;
        qDebug() << _title << ": NULL";
    }
}

void NOutput::initializeMenu(){
    _label = new QLabel(tr("Output int"));
    //_edit = new QLineEdit();
    _layout->addWidget(_label, 0, 0);
    //_layout->addWidget(_edit, 0, 1);
    //_layout->setAlignment(Qt::AlignTop);
    _scene->_menus->addWidget(_menu);
    updateMenu();
}
