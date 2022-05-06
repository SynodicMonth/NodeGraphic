#ifndef NGPHANDLER_H
#define NGPHANDLER_H

#include <QTextStream>
#include "nodeitem.h"
#include "nodedata.h"
#include "nodescene.h"
#include "port.h"
#include "noutput.h"
#include "nodeview.h"

class NGPHandler
{
public:
    NGPHandler(NodeScene *_scene, NodeView *view);
    void save(QString filename);
    void open(QString filename);

private:
    NodeScene *_scene;
    NodeView *_view;
    QString _filename;
};

#endif // NGPHANDLER_H
