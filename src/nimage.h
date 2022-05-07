#ifndef NIMAGE_H
#define NIMAGE_H

#include "nodeitem.h"
#include <QPushButton>
#include <QMessageBox>
#include "nodedata.h"
#include <QFileDialog>
#include <QCoreApplication>

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
    QLabel *_dimension;
    QImage *_image;
};

#endif // NIMAGE_H
