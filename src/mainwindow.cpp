#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    //_ui->setupUi(this);
    _menubar = new QMenuBar(this);
    _menuFile = new QMenu("File", _menubar);
    _menuHelp = new QMenu("Help", _menubar);
    _actionNew = new QAction("New", _menuFile);
    _actionOpen = new QAction("Open", _menuFile);
    _actionSave = new QAction("Save", _menuFile);
    _actionHelp = new QAction("Help", _menuHelp);
    _actionAbout = new QAction("About", _menuHelp);
    _menuFile->addAction(_actionNew);
    _menuFile->addAction(_actionOpen);
    _menuFile->addAction(_actionSave);
    _menuHelp->addAction(_actionHelp);
    _menuHelp->addAction(_actionAbout);
    _menubar->addMenu(_menuFile);
    _menubar->addMenu(_menuHelp);
    _menubar->setStyleSheet("font-family : Consolas; font-size : 18px");
    this->setMenuBar(_menubar);
    connect(_actionNew, &QAction::triggered, this, &MainWindow::newProject);
    connect(_actionOpen, &QAction::triggered, this, &MainWindow::openProject);
    connect(_actionSave, &QAction::triggered, this, &MainWindow::saveProject);
    connect(_actionHelp, &QAction::triggered, this, &MainWindow::showHelp);
    connect(_actionAbout, &QAction::triggered, this, &MainWindow::showAbout);
    _menus = new QStackedWidget();
    _menus->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _menus->setMinimumWidth(600);
    _menus->setStyleSheet("font-family : Consolas; font-size : 18px");
    _scene = new NodeScene(_menus, this);
    _tree = new NodeTree();
    _layout = new QHBoxLayout();
    _layout->addWidget(_tree);
    _tree->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _tree->setMinimumWidth(200);
    _tree->setStyleSheet("font-family : Consolas; font-size : 20px");
    _imagePreview = new QLabel();
    _imagePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _imagePreview->setMinimumSize(600, 600);
    _view = new NodeView(_scene, _imagePreview);
    _scene->syncItems(&_view->_items);
    _rightLayout = new QVBoxLayout();
    _layout->addWidget(_view);
    _rightLayout->addWidget(_imagePreview);
    _rightLayout->addWidget(_menus);
    _layout->addLayout(_rightLayout);
    // _menus->addWidget()
    _widget = new QWidget();
    _widget->setLayout(_layout);
    setCentralWidget(_widget);
    setWindowTitle(tr("NodeEdit"));
    setUnifiedTitleAndToolBarOnMac(true);
    setFocusPolicy(Qt::StrongFocus);
    _handler = new NGPHandler(_scene, _view);

}

MainWindow::~MainWindow()
{
    delete _ui;
    delete _scene;
    delete _tree;
    delete _layout;
    delete _widget;
    //delete _menus;
    //delete _view;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    //excecute all
    if(event->key() == Qt::Key_E){
        _view->_solver->solve();
        _imagePreview->setPixmap(QPixmap::fromImage(*(_view->_outNode->_result->_image)).scaled(600, 600, Qt::KeepAspectRatio));
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::newProject(){
    QList<QGraphicsItem *> items = _scene->items();
    QList<QGraphicsItem *> itemsToRemove;
    for(QGraphicsItem *item : items){
        if(item->type() == NodeItem::Type){
            itemsToRemove.push_back(item);
        }
    }
    for(QGraphicsItem *item : itemsToRemove){
        _scene->removeItem(item);
        delete item;
    }
}

void MainWindow::openProject(){
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open Project"), "D:/", tr("NodeGraph Project Files(*.ngp)"));
    if(!fileName.isNull()){
        newProject();
        _handler->open(fileName);
    }
}

void MainWindow::saveProject(){
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save Project"), "D:/", tr("NodeGraph Project Files(*.ngp)"));
    if(!fileName.isNull()){
        _handler->save(fileName);
    }
}

void MainWindow::showHelp(){
    QMessageBox::about(this, "Help", "This is a help box");
}

void MainWindow::showAbout(){
    QMessageBox::about(this, "Help", "This is a about box");
}
