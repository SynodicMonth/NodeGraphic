#ifndef NCONTRAST_H
#define NCONTRAST_H

#include "nodeitem.h"
#include <QColor>
#include <QSpinBox>

class NContrast : public NodeItem
{
public:
    NContrast(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NContrast();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;
    //QColor modifyContrast(QColor c, int value);

private:
    QSpinBox *_box;
    QSlider *_slider;
};

#endif // NCONTRAST_H
