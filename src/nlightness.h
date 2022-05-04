#ifndef NLIGHTNESS_H
#define NLIGHTNESS_H

#include "nodeitem.h"
#include <QColor>
#include <QSpinBox>

class NLightness : public NodeItem
{
public:
    NLightness(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NLightness();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;

private:
    QSpinBox *_box;
    QSlider *_slider;
};

#endif // NLIGHTNESS_H
