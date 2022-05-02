#ifndef NLUT_H
#define NLUT_H

#include "nodeitem.h"
#include <QPushButton>
#include <QFileDialog>
#include <QSpinBox>

class NLut : public NodeItem
{
public:
    NLut(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NLut();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;
    void openImageFile();

private:
    QString _fileName;
    QLabel *_label;
    QLineEdit *_edit;
    QPushButton *_buttonOpenFile;
    QSpinBox *_box;
    QSlider *_slider;
};

#endif // NLUT_H
