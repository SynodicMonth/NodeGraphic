#include "ncontrast.h"
#include <QDebug>

NContrast::NContrast(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent)
{
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

NContrast::~NContrast(){
    delete _box;
    delete _slider;
}

void NContrast::initializeNode(){
    _title = QString("Contrast");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
}

void NContrast::execute(){
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
        qreal sumR = 0, sumG = 0, sumB = 0;
        for(int i = 0; i < rect.width(); i++){
            for(int j = 0; j < rect.height(); j++){
                QColor color = image->pixelColor(i, j);
                sumR += color.redF();
                sumG += color.greenF();
                sumB += color.blueF();
            }
        }
        int pixelNumber = rect.width() * rect.height();
        sumR /= pixelNumber;
        sumG /= pixelNumber;
        sumB /= pixelNumber;
        double val = double(_box->value()) / 100;
        for(int i = 0; i < rect.width(); i++){
            for(int j = 0; j < rect.height(); j++){
                QColor color = image->pixelColor(i, j);
                int red = 255 * ((color.redF() - sumR) * val + sumR);
                int green = 255 * ((color.greenF() - sumG) * val + sumG);
                int blue = 255 * ((color.blueF() - sumB) * val + sumB);
                if(red > 255) red = 255;
                if(red < 0) red = 0;
                if(green > 255) green = 255;
                if(green < 0) green = 0;
                if(blue > 255) blue = 255;
                if(blue < 0) blue = 0;
                result->setPixel(i, j, QColor(red, green, blue).rgb());
            }
        }
        exportData(0, new NodeData(result));
    }
    qDebug() << _title;
}

void NContrast::initializeMenu(){
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
