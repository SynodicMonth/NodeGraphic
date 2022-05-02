#include "nadd.h"
#include <QDebug>

NAdd::NAdd(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent)
{
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

NAdd::~NAdd(){
    delete _sliderA;
    delete _sliderB;
    delete _boxA;
    delete _boxB;
    delete _labelCombo;
    delete _combo;
}

void NAdd::initializeNode(){
    _title = QString("Add");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in1", this),
                          new InPort(_scene, imageData, "in2", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
}

QColor NAdd::normal(QColor a, QColor b, int mixA, int mixB){
    //add rgb using Linear Dodage
    QColor r;
    double rationalA = double(mixA) / 100.0;
    double rationalB = double(mixB) / 100.0;
    int red = a.red() * rationalA * a.alphaF() + b.red() * rationalB * b.alphaF() * (1.0 - a.alphaF() * rationalA);
    if(red > 255) red = 255;
    int green = a.green() * rationalA * a.alphaF() + b.green() * rationalB * b.alphaF() * (1.0 - a.alphaF() * rationalA);
    if(green > 255) green = 255;
    int blue = a.blue() * rationalA * a.alphaF() + b.blue() * rationalB * b.alphaF() * (1.0 - a.alphaF() * rationalA);
    if(blue > 255) blue = 255;
    r.setRgb(red, green, blue);
    return r;
}

QColor NAdd::linearDodage(QColor a, QColor b, int mixA, int mixB){
    //add rgb using Normal
    QColor r;
    double rationalA = double(mixA) / 100.0;
    double rationalB = double(mixB) / 100.0;
    int red = a.red() * rationalA * a.alphaF() + b.red() * rationalB * b.alphaF();
    if(red > 255) red = 255;
    int green = a.green() * rationalA * a.alphaF() + b.green() * rationalB * b.alphaF();
    if(green > 255) green = 255;
    int blue = a.blue() * rationalA * a.alphaF() + b.blue() * rationalB * b.alphaF();
    if(blue > 255) blue = 255;
    r.setRgb(red, green, blue);
    return r;
}

QColor NAdd::multiply(QColor a, QColor b, int mixA, int mixB){
    //add rgb using Multiply
    QColor r;
    double rationalA = double(mixA) / 100.0;
    double rationalB = double(mixB) / 100.0;
    int red = a.red() * rationalA * b.red() * rationalB / 255.0;
    if(red > 255) red = 255;
    int green = a.green() * rationalA * b.green() * rationalB / 255.0;
    if(green > 255) green = 255;
    int blue = a.blue() * rationalA * b.blue() * rationalB / 255.0;
    if(blue > 255) blue = 255;
    r.setRgb(red, green, blue);
    return r;
}

void NAdd::execute(){
    QRect rectA, rectB;
    QImage *imageA = nullptr, *imageB = nullptr;
    NodeData *dataA, *dataB;
    dataA = importData(0);
    dataB = importData(1);
    if(dataA)   imageA = dataA->_image;
    if(dataB)   imageB = dataB->_image;
    if(imageA){
        rectA = QRect(0, 0, imageA->size().width(), imageA->size().height());
    }
    if(imageB){
        rectB = QRect(0, 0, imageB->size().width(), imageB->size().height());
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
                switch(_combo->currentIndex()){
                case 0:
                    //Normal
                    result->setPixel(i, j, normal(colorA, colorB, _boxA->value(), _boxB->value()).rgb());
                    break;
                case 1:
                    //Multiply
                    result->setPixel(i, j, multiply(colorA, colorB, _boxA->value(), _boxB->value()).rgb());
                    break;
                case 2:
                    //Linear Dodage
                    result->setPixel(i, j, linearDodage(colorA, colorB, _boxA->value(), _boxB->value()).rgb());
                    break;
                }
            }
        }
        exportData(0, new NodeData(result));
    }
    qDebug() << _title;
}

void NAdd::initializeMenu(){
    _labelCombo = new QLabel(tr("Blend Method"));
    _combo = new QComboBox();
    _combo->addItem(tr("Normal"));
    _combo->addItem(tr("Multiply"));
    _combo->addItem(tr("Linear Dodage"));
    _boxA = new QSpinBox();
    _boxB = new QSpinBox();
    _boxA->setRange(0, 100);
    _boxB->setRange(0, 100);
    _sliderA = new QSlider(Qt::Horizontal);
    _sliderB = new QSlider(Qt::Horizontal);
    _sliderA->setRange(0, 100);
    _sliderB->setRange(0, 100);
    _layout->addWidget(_labelCombo, 0, 0);
    _layout->addWidget(_combo, 0, 1);
    _layout->addWidget(_boxA, 1, 0);
    _layout->addWidget(_sliderA, 1, 1);
    _layout->addWidget(_boxB, 2, 0);
    _layout->addWidget(_sliderB, 2, 1);
    connect(_sliderA, &QSlider::valueChanged, _boxA, &QSpinBox::setValue);
    connect(_sliderB, &QSlider::valueChanged, _boxB, &QSpinBox::setValue);
    connect(_boxA, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), _sliderA, &QSlider::setValue);
    connect(_boxB, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), _sliderB, &QSlider::setValue);
    _sliderA->setValue(100);
    _sliderB->setValue(100);
    updateMenu();
}
