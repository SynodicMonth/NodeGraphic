#include "nthreshold.h"
#include <QDebug>

NThreshold::NThreshold(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent)
{
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

NThreshold::~NThreshold(){
    delete _box;
    delete _slider;
}

void NThreshold::initializeNode(){
    _title = QString("Threshold");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
}

void NThreshold::execute(){
    NodeData *data = importData(0);
    QImage *image = nullptr;
    QRect rect;
    if(data)    image = data->_image;
    else    exportData(0, new NodeData());
    if(image){
        rect = image->rect();
    }
    QImage *result = nullptr;
    if(!rect.isEmpty()){
        result = new QImage(image->size(), QImage::Format_RGBA8888);
        int val = _box->value();
        for(int i = 0; i < rect.width(); i++){
            for(int j = 0; j < rect.height(); j++){
                QColor color = image->pixelColor(i, j);
                int l = 0;
                if(color.lightness() > val) l = 255;
                result->setPixel(i, j, QColor(l, l, l).rgb());
            }
        }
        exportData(0, new NodeData(result));
    }
    qDebug() << _title;
}

void NThreshold::initializeMenu(){
    _box = new QSpinBox();
    _box->setRange(0, 255);
    _slider = new QSlider(Qt::Horizontal);
    _slider->setRange(0, 255);
    _layout->addWidget(_box, 0, 0);
    _layout->addWidget(_slider, 0, 1);
    connect(_slider, &QSlider::valueChanged, _box, &QSpinBox::setValue);
    connect(_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), _slider, &QSlider::setValue);
    _slider->setValue(127);
    updateMenu();
}
