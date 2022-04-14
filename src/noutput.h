#ifndef NOUTPUT_H
#define NOUTPUT_H

#include "nodeitem.h"

class NOutput : public NodeItem{
public:
    NOutput(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    void initializeNode() override;
    void execute() override;
};

#endif // NOUTPUT_H
