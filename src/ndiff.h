#ifndef NDIFF_H
#define NDIFF_H

#include "nodeitem.h"
#include <QColor>
#include <QSpinBox>
#include <QSlider>

class NDiff : public NodeItem
{
public:
    NDiff(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NDiff();
    void initializeNode() override;
    void initializeMenu() override;
    void execute() override;
    QColor difference(QColor a, QColor b, float mul);

private:
    QLabel *_label;
    QSpinBox *_box;
    QSlider *_slider;
};

#endif // NDIFF_H
