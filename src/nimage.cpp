#include "nimage.h"
#include <QDebug>

NImage::NImage(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent){
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

NImage::~NImage(){
    delete _label;
    delete _edit;
    delete _buttonOpenFile;
}

void NImage::initializeNode(){
    _title = QString("Image");
    _nodetype = inputNode;
    _in = QList<InPort *>();
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "Image", this)};
}

void NImage::execute(){
    qDebug() << _title << ":" << _fileName;
    if(!_fileName.isEmpty()){
        QImage *image = new QImage(_fileName);
        _dimension->setText(QString::number(image->size().width()) + "x" + QString::number(image->size().height()));
        exportData(0, new NodeData(image));
    }
}

void NImage::initializeMenu(){
    _label = new QLabel(tr("Open Image File"));
    _dimension = new QLabel();
    _edit = new QLineEdit();
    _edit->setReadOnly(true);
    _layout->addWidget(_label, 0, 0);
    _layout->addWidget(_edit, 0, 1);
    _buttonOpenFile = new QPushButton("Open...");
    _layout->addWidget(_buttonOpenFile, 1, 0, 1, 2);
    _layout->addWidget(_dimension, 2, 0, 1, 2);
    connect(_buttonOpenFile, &QPushButton::clicked, this, &NImage::openImageFile);
    _scene->_menus->addWidget(_menu);
    updateMenu();
}

void NImage::openImageFile(){
    //open file dialog
    _fileName = QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "D:/", tr("Image Files(*.jpg *.png *.jpeg *.bmp)"));
    _edit->setText(_fileName);
}
