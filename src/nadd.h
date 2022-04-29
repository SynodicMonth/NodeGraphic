#ifndef NADD_H
#define NADD_H

#include "nodeitem.h"
#include <QSpinBox>
#include <QSlider>
#include <QComboBox>

class NAdd : public NodeItem
{
public:
    NAdd(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NAdd();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;
    QColor linearDodage(QColor a, QColor b, int mixA, int mixB);
    QColor normal(QColor a, QColor b, int mixA, int mixB);
    QColor multiply(QColor a, QColor b, int mixA, int mixB);

private:
    QLabel *_labelCombo;
    QComboBox *_combo;
    QSpinBox *_boxA;
    QSlider *_sliderA;
    QSpinBox *_boxB;
    QSlider *_sliderB;
};

#endif // NADD_H
