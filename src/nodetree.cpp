#include "nodetree.h"

NodeTree::NodeTree(QWidget *parent)
    : QTreeWidget(parent)
{
    setSelectionMode((QAbstractItemView::SingleSelection));
    setDragEnabled(true);
    setMouseTracking(true);
    setColumnCount(1);
    setIndentation(20);
    _items.append(new QTreeWidgetItem(QStringList(QString("Input"))));
    _items.append(new QTreeWidgetItem(QStringList(QString("Function"))));
    _items.append(new QTreeWidgetItem(QStringList(QString("Output"))));
    _items[0]->addChild(new QTreeWidgetItem(QStringList(QString("Image"))));
    insertTopLevelItems(0, _items);
    setHeaderLabel(tr("Select Nodes"));
    expandAll();
}

//NodeTree::~NodeTree(){
//}
