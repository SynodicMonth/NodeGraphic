#ifndef NODESCENE_H
#define NODESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

class NodeScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit NodeScene(QWidget *parent = nullptr);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

private slots:
    void _clearSelected();
};

#endif // NODESCENE_H
