#ifndef NODETREE_H
#define NODETREE_H
#include <QTreeWidget>

class NodeTree : public QTreeWidget
{
public:
    explicit NodeTree(QWidget *parent = nullptr);
    //~NodeTree();
private:
    QList<QTreeWidgetItem *> _items;
};

#endif // NODETREE_H
