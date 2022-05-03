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
    _items[1]->addChild(new QTreeWidgetItem(QStringList(QString("Add"))));
    _items[1]->addChild(new QTreeWidgetItem(QStringList(QString("Diff"))));
    _items[1]->addChild(new QTreeWidgetItem(QStringList(QString("Lut"))));
    _items[1]->addChild(new QTreeWidgetItem(QStringList(QString("Contrast"))));
    //_items[2]->addChild(new QTreeWidgetItem(QStringList(QString("Output"))));
    insertTopLevelItems(0, _items);
    setHeaderLabel(tr("Select Nodes"));
    expandAll();
}

//NodeTree::~NodeTree(){
//}
