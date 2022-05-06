#ifndef NOUTPUT_H
#define NOUTPUT_H

#include "nodeitem.h"
#include <QPushButton>
#include <QFileDialog>

class NOutput : public NodeItem{
public:
    NOutput(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;
    void saveImageFile();
    NodeData *_result;
    enum { Type = 65550 };
    int type() const{
        return Type;
    }
private:
    QLabel *_label;
    QLabel *_dimension;
    QLineEdit *_edit;
    QImage *_nullImage;
    NodeData *_nullData;
    QPushButton *_saveButton;
};

#endif // NOUTPUT_H
