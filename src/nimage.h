#ifndef NIMAGE_H
#define NIMAGE_H

#include "nodeitem.h"

class NImage : public NodeItem
{
public:
    NImage(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    void initializeNode() override;
    void execute() override;
};

#endif // NIMAGE_H
