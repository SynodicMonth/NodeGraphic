#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QStackedWidget>
#include "nodescene.h"
#include "nodetree.h"
#include "nodeview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    NodeScene *_scene;
    NodeTree *_tree;
    QVBoxLayout *_rightLayout;
    QHBoxLayout *_layout;
    QWidget *_widget;
    NodeView *_view;
    QStackedWidget *_menus;
    QLabel *_imagePreview;
};

#endif // MAINWINDOW_H
