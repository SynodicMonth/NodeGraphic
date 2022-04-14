#ifndef NADD_H
#define NADD_H

#include "nodeitem.h"

class NAdd : public NodeItem
{
public:
    NAdd(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    void initializeNode() override;
    void execute() override;
};

#endif // NADD_H
