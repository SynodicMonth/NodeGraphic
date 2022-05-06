#include "nsaturation.h"
#include <QDebug>

NSaturation::NSaturation(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent)
{
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

NSaturation::~NSaturation(){
    delete _box;
    delete _slider;
}

void NSaturation::initializeNode(){
    _title = QString("Saturation");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
}


void NSaturation::execute(){
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
        double val = double(_box->value()) / 100;
        for(int i = 0; i < rect.width(); i++){
            for(int j = 0; j < rect.height(); j++){
                QColor color = image->pixelColor(i, j);
                int s = 255 * color.hslSaturationF() * val;
                if(s > 255) s = 255;
                if(s < 0) s = 0;
                result->setPixel(i, j, QColor::fromHsl(color.hslHue(), s, color.lightness()).rgb());
            }
        }
        exportData(0, new NodeData(result));
    }
    qDebug() << _title;
}

void NSaturation::initializeMenu(){
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
