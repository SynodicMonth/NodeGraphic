#ifndef NIMAGE_H
#define NIMAGE_H

#include "nodeitem.h"
#include <QPushButton>
#include "nodedata.h"
#include <QFileDialog>

class NImage : public NodeItem
{
public:
    NImage(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NImage();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;
    void openImageFile();

private:
    QString _fileName;
    QLabel *_label;
    QLineEdit *_edit;
    QPushButton *_buttonOpenFile;
};

#endif // NIMAGE_H
