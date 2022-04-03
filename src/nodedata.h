#ifndef NODEDATA_H
#define NODEDATA_H

#include <QImage>
enum Datatype{
    imageData, intData, unknownData
};

class NodeData
{
public:
    NodeData(QImage *_image);
    NodeData(int i);
private:
    QImage *_image;
    int _int;
    Datatype _datatype;
};

#endif // NODEDATA_H
