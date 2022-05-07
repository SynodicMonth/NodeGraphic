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
    delete _dimension;
}

void NImage::initializeNode(){
    _title = QString("Image");
    _nodetype = inputNode;
    _in = QList<InPort *>();
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "Image", this)};
}

void NImage::execute(){
    qDebug() << _title << ":" << _fileName;
    if(_image && !_image->isNull()){
        _dimension->setText(QString::number(_image->size().width()) + "x" + QString::number(_image->size().height()));
        exportData(0, new NodeData(_image));
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
    _image = new QImage();
    connect(_buttonOpenFile, &QPushButton::clicked, this, &NImage::openImageFile);
    updateMenu();
}

void NImage::openImageFile(){
    //open file dialog restrict to jpg
    _fileName = QFileDialog::getOpenFileName(nullptr, tr("Open Image"), "D:/", tr("Image Files(*.jpg *.jpeg *.png)"));
    _edit->setText(_fileName);
    if(!_fileName.isEmpty()){
        delete _image;
        _image = new QImage(_fileName);
        if(_image->size().width() * _image->size().height() > 1920 * 1080){
            QMessageBox::warning(nullptr, tr("Warnig"), tr("<font size='+2' face='Consolas'>Image is too big, may slow down the program</font>"));
        }
    }
}
