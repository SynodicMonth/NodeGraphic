#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    //_ui->setupUi(this);
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
    _tree->setStyleSheet("font-family : Consolas; font-size : 18px");
    _imagePreview = new QLabel();
    _imagePreview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _imagePreview->setMinimumSize(600, 600);
    _view = new NodeView(_scene, _imagePreview);
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
