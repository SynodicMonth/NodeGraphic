#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    //_ui->setupUi(this);
    setWindowTitle(tr("NodeGraphic -- working"));
    setWindowIcon(QIcon(":/tex/icon.png"));
    _menubar = new QMenuBar(this);
    _menuFile = new QMenu("File", _menubar);
    _menuHelp = new QMenu("Help", _menubar);
    _menuView = new QMenu("View", _menubar);
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
    _menubar->addMenu(_menuView);
    _menubar->addMenu(_menuHelp);
    _menubar->setStyleSheet("font-family : Consolas; font-size : 18px");
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
//    _layout = new QHBoxLayout();
//    _layout->addWidget(_tree);
    _tree->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _tree->setMinimumWidth(200);
    _tree->setStyleSheet("font-family : Consolas; font-size : 20px");
    _imagePreview = new QLabel();
    _imagePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _imagePreview->setMinimumSize(600, 600);
    QScrollArea *_preview = new QScrollArea();
    _preview->setWidget(_imagePreview);
    _view = new NodeView(_scene, _imagePreview);
    _scene->syncItems(&_view->_items);
//    _rightLayout = new QVBoxLayout();
//    _layout->addWidget(_view);
//    _rightLayout->addWidget(_imagePreview);
//    _rightLayout->addWidget(_menus);
//    _layout->addLayout(_rightLayout);
    // _menus->addWidget()
    //_widget = new QWidget();
    //_widget->setLayout(_layout);
    setCentralWidget(_view);
    _treeDock = new QDockWidget(tr("NodeTree"), this);
    _treeDock->setWidget(_tree);
    _treeDock->setStyleSheet("font-family : Consolas; font-size : 18px");
    addDockWidget(Qt::LeftDockWidgetArea, _treeDock);
    _previewDock = new QDockWidget(tr("Output Preview Press E to refresh!!!!!!!!!!!!!!"), this);
    _previewDock->setWidget(_preview);
    _previewDock->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _previewDock->setStyleSheet("font-family : Consolas; font-size : 18px");
    _previewDock->setMaximumHeight(620);
    addDockWidget(Qt::RightDockWidgetArea, _previewDock);
    _menuDock = new QDockWidget(tr("Menu"), this);
    _menuDock->setWidget(_menus);
    _menuDock->setStyleSheet("font-family : Consolas; font-size : 18px");
    addDockWidget(Qt::RightDockWidgetArea, _menuDock);
    _menuView->addAction(_treeDock->toggleViewAction());
    _menuView->addAction(_previewDock->toggleViewAction());
    _menuView->addAction(_menuDock->toggleViewAction());
    setWindowTitle(tr("NodeEdit"));
    setUnifiedTitleAndToolBarOnMac(true);
    setFocusPolicy(Qt::StrongFocus);
    _handler = new NGPHandler(_scene, _view);
    this->setMenuBar(_menubar);
}

MainWindow::~MainWindow()
{
    //qDebug() << "deconstructor1";
    delete _ui;
    //qDebug() << "deconstructor1";
    delete _scene;
    //qDebug() << "deconstructor1";
    delete _tree;
    //qDebug() << "deconstructor1";
    //delete _layout;
    //delete _widget;
//    qDebug() << "deconstructor1";
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
        _scene->_items->removeOne(static_cast<NodeItem *>(item));
        delete item;
    }
    qDebug() << _scene->_items->size();
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
    QUrl url(QString("https://github.com/SynodicMonth/NodeGraphic"));
    QDesktopServices::openUrl(url);
}

void MainWindow::showAbout(){
    QMessageBox msg(this);
    msg.setText("<font size='+2' face='Consolas'>BUG Reporting:<a href='https://github.com/SynodicMonth/NodeGraphic'>Github</a><br>Video:<a href='https://space.bilibili.com/26738256'>Bilibili</a><br>21-计网-郭大玮-2112052</font>");
    msg.exec();
}
