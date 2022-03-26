#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _scene = new NodeScene(this);
    _tree = new NodeTree();
    _layout = new QHBoxLayout();
    _layout->addWidget(_tree);
    _tree->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    _tree->setMinimumWidth(200);
    _view = new NodeView(_scene);
    _layout->addWidget(_view);
    _widget = new QWidget;
    _widget->setLayout(_layout);
    setCentralWidget(_widget);
    setWindowTitle(tr("NodeEdit"));
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{
    delete _ui;
    delete _scene;
    delete _tree;
    delete _layout;
    delete _widget;
    //delete _view;
}
