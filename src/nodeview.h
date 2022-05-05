#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMimeData>
#include <QPixmap>
#include <QScrollBar>
#include <QList>
#include "nodescene.h"
#include "nodeitem.h"
#include "graphsolver.h"
#include "noutput.h"
#include "nimage.h"
#include "nadd.h"
#include "ndiff.h"
#include "nlut.h"
#include "ncontrast.h"
#include "nlightness.h"
#include "nsaturation.h"
#include "ngrayscale.h"
#include "nthreshold.h"

class GraphSolver;
class NOutput;

class NodeView : public QGraphicsView
{
public:
    explicit NodeView(NodeScene *scene, QLabel *imagePreview, QWidget *parent = nullptr);
    ~NodeView();
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
    void appendNode(QString name, QDropEvent *event);
    GraphSolver *_solver;
    NOutput *_outNode;
    QLabel *_imagePreview;
private:
    NodeScene *_nodeScene;
    QPointF _centerAnchor;
    QPoint _posAnchor;
    bool _isMousePressed = false;
    QList<NodeItem *> _items;
//signals:
//    void updateImage(QString image);
};

#endif // NODEVIEW_H
