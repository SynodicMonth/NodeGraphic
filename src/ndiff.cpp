#include "ndiff.h"
#include <QDebug>

NDiff::NDiff(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent)
{
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

NDiff::~NDiff(){
    delete _label;
    delete _box;
    delete _slider;
}

void NDiff::initializeNode(){
    _title = QString("Diff");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in1", this),
                          new InPort(_scene, imageData, "in2", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
}

QColor NDiff::difference(QColor a, QColor b, float mul){
    QColor r;
    int red = abs(a.red() * a.alphaF() - b.red() * b.alphaF()) * mul;
    if(red > 255) red = 255;
    int green = abs(a.green() * a.alphaF() - b.green() * b.alphaF()) * mul;
    if(green > 255) green = 255;
    int blue = abs(a.blue() * a.alphaF() - b.blue() * b.alphaF()) * mul;
    if(blue > 255) blue = 255;
    r.setRgb(red, green, blue);
    return r;
}

void NDiff::execute(){
    QRect rectA, rectB;
    QImage *imageA = nullptr, *imageB = nullptr;
    NodeData *dataA, *dataB;
    dataA = importData(0);
    dataB = importData(1);
    if(dataA)   imageA = dataA->_image;
    if(dataB)   imageB = dataB->_image;
    if(!dataA && !dataB)    exportData(0, new NodeData());
    if(imageA){
        rectA = imageA->rect();
    }
    if(imageB){
        rectB = imageB->rect();
    }
    QRect rectR = rectA | rectB;
    QImage *result = nullptr;
    if(!rectR.isEmpty()){
        result = new QImage(rectR.width(), rectR.height(), QImage::Format_RGBA8888);
        result->fill(QColor(0, 0, 0, 0));
        for(int i = 0; i < rectR.width(); i++){
            for(int j = 0; j < rectR.height(); j++){
                QColor colorA, colorB;
                if(rectA.contains(i, j)){
                    colorA = imageA->pixelColor(i, j);
                }else{
                    colorA = QColor(0, 0, 0, 0);
                }
                if(rectB.contains(i, j)){
                    colorB = imageB->pixelColor(i, j);
                }else{
                    colorB = QColor(0, 0, 0, 0);
                }
                result->setPixel(i, j, difference(colorA, colorB, _box->value()).rgb());
            }
        }
        exportData(0, new NodeData(result));
    }
    qDebug() << _title;
}

void NDiff::initializeMenu(){
    _label = new QLabel(tr("Multiply value"));
    _box = new QSpinBox();
    _slider = new QSlider(Qt::Horizontal);
    _slider->setRange(0, 255);
    _layout->addWidget(_label, 0, 0, 1, 2);
    _layout->addWidget(_box, 1, 0);
    _layout->addWidget(_slider, 1, 1);
    connect(_slider, &QSlider::valueChanged, _box, &QSpinBox::setValue);
    connect(_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), _slider, &QSlider::setValue);
    _slider->setValue(10);
}
