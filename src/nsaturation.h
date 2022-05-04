#ifndef NSATURATION_H
#define NSATURATION_H

#include "nodeitem.h"
#include <QColor>
#include <QSpinBox>

class NSaturation : public NodeItem
{
public:
    NSaturation(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NSaturation();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;

private:
    QSpinBox *_box;
    QSlider *_slider;
};

#endif // NSATURATION_H
