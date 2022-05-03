#ifndef NLUT_H
#define NLUT_H

#include "nodeitem.h"
#include <QPushButton>
#include <QFileDialog>
#include <QSpinBox>
#include <QColor>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QStringList>

class NLut : public NodeItem
{
public:
    NLut(NodeScene *nodeScene, QGraphicsItem *parent = nullptr);
    ~NLut();
    void initializeNode() override;
    void execute() override;
    void initializeMenu() override;
    void openImageFile();
    QColor applyLut(QColor c);
    double mix(double a, double b, double c);

private:
    QString _fileName;
    QLabel *_label;
    QLineEdit *_edit;
    QPushButton *_buttonOpenFile;
    QSpinBox *_box;
    QSlider *_slider;
    QFile *_file;
    QTextStream _stream;
    int _lutSize;
    QVector<QVector<double>> _lutData;
    bool _dataIsReady;
};

#endif // NLUT_H
