#ifndef NTHRESHOLD_H
#define NTHRESHOLD_H

#include "nodeitem.h"
#include <QColor>
#include <QSpinBox>

class NThreshold : public NodeItem
{
public:
    NThreshold(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NThreshold();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;

private:
    QSpinBox *_box;
    QSlider *_slider;
};

#endif // NTHRESHOLD_H
