#include "nodescene.h"

NodeScene::NodeScene(QWidget *parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(QRectF(0, 0, 3000, 3000));
}

void NodeScene::_clearSelected(){
    for(int i = 0; i < this->selectedItems().length(); i++){
        this->selectedItems()[i]->setSelected(false);
    }
}
