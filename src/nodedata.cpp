#include "nodedata.h"

NodeData::NodeData(QImage *image){
    _image = image;
    _datatype = imageData;
}

NodeData::NodeData(QString &string){
    _string = &string;
    _datatype = stringData;
}

NodeData::NodeData(int i){
    _int = i;
    _datatype = intData;
}

NodeData::NodeData(){
    _int = 0;
    _image = nullptr;
    _datatype = unknownData;
}
