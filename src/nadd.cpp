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
}

void NAdd::initializeNode(){
    _title = QString("Add");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in1", this),
                          new InPort(_scene, imageData, "in2", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
}

QColor NAdd::rgbAdd(QColor a, QColor b){
    QColor r;
    int red = a.red() + b.red();
    if(red > 255) red = 255;
    if(red < 0) red = 0;
    int green = a.green() + b.green();
    if(green > 255) green = 255;
    if(green < 0) green = 0;
    int blue = a.blue() + b.blue();
    if(blue > 255) blue = 255;
    if(blue < 0) blue = 0;
    r.setRgb(red, green, blue);
    return r;
}

void NAdd::execute(){
    QRect rectA, rectB;
    QImage *imageA, *imageB;
    if(!_in[0]->_connections.isEmpty() && _in[0]->_connections[0]->_in->_data){
        imageA = _in[0]->_connections[0]->_in->_data->_image;
        rectA = QRect(0, 0, imageA->size().width(), imageA->size().height());
    }
    if(!_in[1]->_connections.isEmpty() && _in[1]->_connections[0]->_in->_data){
        imageB = _in[1]->_connections[0]->_in->_data->_image;
        rectB = QRect(0, 0, imageB->size().width(), imageB->size().height());
    }
    QRect rectR = rectA | rectB;
    QImage *result = nullptr;
    if(!rectR.isEmpty()){
        result = new QImage(rectR.width(), rectR.height(), QImage::Format_RGBA8888);
        result->fill(QColor(255, 255, 255));
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
                //qDebug() << rgbAdd(colorA, colorB).rgb();
                result->setPixel(i, j, rgbAdd(colorA, colorB).rgb());
            }
        }
        _out[0]->_data = new NodeData(result);
    }else{
        _out[0]->_data = nullptr;
    }
    qDebug() << _title;
}

void NAdd::initializeMenu(){
    _boxA = new QSpinBox();
    _boxB = new QSpinBox();
    _sliderA = new QSlider(Qt::Horizontal);
    _sliderB = new QSlider(Qt::Horizontal);
    _layout->addWidget(_boxA, 0, 0);
    _layout->addWidget(_sliderA, 0, 1);
    _layout->addWidget(_boxB, 1, 0);
    _layout->addWidget(_sliderB, 1, 1);
    connect(_sliderA, &QSlider::valueChanged, _boxA, &QSpinBox::setValue);
    connect(_sliderB, &QSlider::valueChanged, _boxB, &QSpinBox::setValue);
    _scene->_menus->addWidget(_menu);
    updateMenu();
}
