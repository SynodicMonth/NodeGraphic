#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QStackedWidget>
#include "ngphandler.h"
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
    void keyPressEvent(QKeyEvent *event);
    void newProject();
    void openProject();
    void saveProject();
    void showHelp();
    void showAbout();
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
    QMenuBar *_menubar;
    QMenu *_menuFile;
    QMenu *_menuHelp;
    QAction *_actionNew;
    QAction *_actionOpen;
    QAction *_actionSave;
    QAction *_actionHelp;
    QAction *_actionAbout;
    QString _fileName;
    NGPHandler *_handler;
};

#endif // MAINWINDOW_H
