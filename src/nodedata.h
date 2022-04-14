#ifndef NODEDATA_H
#define NODEDATA_H

#include <QImage>
enum Datatype{
    imageData, intData, stringData, unknownData
};

class NodeData
{
public:
    NodeData(QImage *image);
    NodeData(QString &string);
    NodeData(int i);
//private:
    QImage *_image;
    int _int;
    QString *_string;
    Datatype _datatype;
};

#endif // NODEDATA_H
