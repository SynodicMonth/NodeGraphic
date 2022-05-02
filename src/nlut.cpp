#include "nlut.h"

NLut::NLut(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent)
{
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

NLut::~NLut(){
    delete _label;
    delete _edit;
    delete _buttonOpenFile;
    delete _box;
    delete _slider;
}

void NLut::openImageFile(){
    //open file dialog
    _fileName = QFileDialog::getOpenFileName(nullptr, tr("Open LUT"), "D:/", tr("LUT Files(*.cube)"));
    _edit->setText(_fileName);
}


void NLut::initializeNode(){
    _title = QString("LUT");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
}

void NLut::execute(){

}

void NLut::initializeMenu(){
    _label = new QLabel(tr("Open LUT File"));
    _edit = new QLineEdit();
    _edit->setReadOnly(true);
    _layout->addWidget(_label, 0, 0);
    _layout->addWidget(_edit, 0, 1);
    _buttonOpenFile = new QPushButton("Open...");
    _layout->addWidget(_buttonOpenFile, 1, 0, 1, 2);
    _box = new QSpinBox();
    _slider = new QSlider(Qt::Horizontal);
    _slider->setRange(0, 100);
    _layout->addWidget(_box, 2, 0);
    _layout->addWidget(_slider, 2, 1);
    connect(_buttonOpenFile, &QPushButton::clicked, this, &NLut::openImageFile);
    connect(_slider, &QSlider::valueChanged, _box, &QSpinBox::setValue);
    connect(_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), _slider, &QSlider::setValue);
    updateMenu();
}
