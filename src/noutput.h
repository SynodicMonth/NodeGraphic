#ifndef NOUTPUT_H
#define NOUTPUT_H

#include "nodeitem.h"

class NOutput : public NodeItem{
public:
    NOutput(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;
    NodeData *_result;
private:
    QLabel *_label;
    QLabel *_dimension;
    QLineEdit *_edit;
    QImage *_nullImage;
    NodeData *_nullData;
};

#endif // NOUTPUT_H
