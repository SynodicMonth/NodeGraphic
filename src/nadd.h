#ifndef NADD_H
#define NADD_H

#include "nodeitem.h"
#include <QSpinBox>
#include <QSlider>

class NAdd : public NodeItem
{
public:
    NAdd(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NAdd();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;
    QColor rgbAdd(QColor a, QColor b);

private:
    QSpinBox *_boxA;
    QSlider *_sliderA;
    QSpinBox *_boxB;
    QSlider *_sliderB;
};

#endif // NADD_H
