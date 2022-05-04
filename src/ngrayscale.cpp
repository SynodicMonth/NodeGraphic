#include "ngrayscale.h"
#include <QDebug>

NGrayscale::NGrayscale(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent)
{
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

NGrayscale::~NGrayscale(){
    delete _box;
    delete _slider;
}

void NGrayscale::initializeNode(){
    _title = QString("Grayscale");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
}

void NGrayscale::execute(){
    NodeData *data = importData(0);
    QImage *image = nullptr;
    QRect rect;
    if(data)    image = data->_image;
    if(image){
        rect = image->rect();
    }
    QImage *result = nullptr;
    if(!rect.isEmpty()){
        result = new QImage(image->size(), QImage::Format_RGBA8888);
        double val = double(_box->value()) / 100;
        for(int i = 0; i < rect.width(); i++){
            for(int j = 0; j < rect.height(); j++){
                QColor color = image->pixelColor(i, j);
                int l = color.lightness() * val;
                if(l > 255) l = 255;
                result->setPixel(i, j, QColor(l, l, l).rgb());
            }
        }
        exportData(0, new NodeData(result));
    }
    qDebug() << _title;
}

void NGrayscale::initializeMenu(){
    _box = new QSpinBox();
    _box->setRange(0, 400);
    _slider = new QSlider(Qt::Horizontal);
    _slider->setRange(0, 400);
    _layout->addWidget(_box, 0, 0);
    _layout->addWidget(_slider, 0, 1);
    connect(_slider, &QSlider::valueChanged, _box, &QSpinBox::setValue);
    connect(_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), _slider, &QSlider::setValue);
    _slider->setValue(100);
    updateMenu();
}
