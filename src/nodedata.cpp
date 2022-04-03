#include "nodedata.h"

NodeData::NodeData(QImage *image){
    _image = image;
    _datatype = imageData;
}

NodeData::NodeData(int i){
    _int = i;
    _datatype = intData;
}
