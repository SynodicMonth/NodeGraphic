#ifndef NGRAYSCALE_H
#define NGRAYSCALE_H

#include "nodeitem.h"
#include <QColor>
#include <QSpinBox>

class NGrayscale : public NodeItem
{
public:
    NGrayscale(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NGrayscale();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;

private:
    QSpinBox *_box;
    QSlider *_slider;
};

#endif // NGRAYSCALE_H
