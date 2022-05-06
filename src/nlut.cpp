#include "nlut.h"
#include <QDebug>

NLut::NLut(NodeScene *nodeScene, QGraphicsItem *parent)
    : NodeItem(nodeScene, parent)
{
    initializeNode();
    initializeBoundingRect();
    initializePort();
    initializeMenu();
}

NLut::~NLut(){
    delete _file;
    delete _label;
    delete _edit;
    delete _buttonOpenFile;
//    delete _box;
//    delete _slider;
}

double NLut::mix(double a, double b, double c){
    return a + (b - a) * (c - floor(c));
}

void NLut::openImageFile(){
    //open file dialog
    _lutData.clear();
    _fileName = QFileDialog::getOpenFileName(nullptr, tr("Open LUT"), "D:/", tr("LUT Files(*.cube)"));
    _edit->setText(_fileName);
    _file->setFileName(_fileName);
    _file->open(QIODevice::ReadOnly | QIODevice::Text);
    //QTextStream stream = QTextStream(_file);
    QString s;
    bool startData = false;
    while(!_file->atEnd()){
        s = _file->readLine();
        if(startData){
            QStringList matlist = s.split(" ");
            if(matlist.length() == 3){
                QVector<double> mat(3);
                mat[0] = matlist[0].toDouble();
                mat[1] = matlist[1].toDouble();
                mat[2] = matlist[2].toDouble();
                _lutData.append(mat);
            }
        }else{
            if(s.contains("LUT_3D_SIZE", Qt::CaseInsensitive)){
                s.remove(0, 11);
                _lutSize = s.toInt();
                startData = true;
                _dataIsReady = 1;
            }
        }
    }
    if(_dataIsReady) qDebug() << _lutData.size();
    _file->close();
}

QColor NLut::applyLut(QColor c){
    if(_fileName.isEmpty() || !_dataIsReady)
        return c;
    double r = c.redF() * (_lutSize - 1);
    double g = c.greenF() * (_lutSize - 1);
    double b = c.blueF() * (_lutSize - 1);
    int rH = ceil(r);
    int rL = floor(r);
    int gH = ceil(g);
    int gL = floor(g);
    int bH = ceil(b);
    int bL = floor(b);
    double frH = _lutData[rH + gH * _lutSize + bH * _lutSize * _lutSize][0];
    double fgH = _lutData[rH + gH * _lutSize + bH * _lutSize * _lutSize][1];
    double fbH = _lutData[rH + gH * _lutSize + bH * _lutSize * _lutSize][2];
    double frL = _lutData[rL + gL * _lutSize + bL * _lutSize * _lutSize][0];
    double fgL = _lutData[rL + gL * _lutSize + bL * _lutSize * _lutSize][1];
    double fbL = _lutData[rL + gL * _lutSize + bL * _lutSize * _lutSize][2];
//    int fr = 255 * mix(frL, frH, r);
//    int fg = 255 * mix(fgL, fgH, g);
//    int fb = 255 * mix(fbL, fbH, b);
    int fr = 255 * (frL + (r - floor(r)) * (frH - frL));
    int fg = 255 * (fgL + (g - floor(g)) * (fgH - fgL));
    int fb = 255 * (fbL + (b - floor(b)) * (fbH - fbL));
    return QColor(fr, fg, fb);
}

void NLut::initializeNode(){
    _lutSize = 0;
    _dataIsReady = 0;
    _title = QString("LUT");
    _nodetype = functionNode;
    _in = QList<InPort *>{new InPort(_scene, imageData, "in", this)};
    _out = QList<OutPort *>{new OutPort(_scene, imageData, "out", this)};
    _file = new QFile();
}

void NLut::execute(){
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
        for(int i = 0; i < rect.width(); i++){
            for(int j = 0; j < rect.height(); j++){
                QColor color = image->pixelColor(i, j);
                result->setPixel(i, j, applyLut(color).rgb());
            }
        }
        exportData(0, new NodeData(result));
    }
    qDebug() << _title;
}

void NLut::initializeMenu(){
    _label = new QLabel(tr("Open LUT File"));
    _edit = new QLineEdit();
    _edit->setReadOnly(true);
    _layout->addWidget(_label, 0, 0);
    _layout->addWidget(_edit, 0, 1);
    _buttonOpenFile = new QPushButton("Open...");
    _layout->addWidget(_buttonOpenFile, 1, 0, 1, 2);
//    _box = new QSpinBox();
//    _slider = new QSlider(Qt::Horizontal);
//    _slider->setRange(0, 100);
//    _layout->addWidget(_box, 2, 0);
//    _layout->addWidget(_slider, 2, 1);
    connect(_buttonOpenFile, &QPushButton::clicked, this, &NLut::openImageFile);
//    connect(_slider, &QSlider::valueChanged, _box, &QSpinBox::setValue);
//    connect(_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), _slider, &QSlider::setValue);
    updateMenu();
}
