#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"processnode.h"

#include <QGraphicsView>
QGraphicsRectItem *n ;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FlowerView *view=ui->graphicsView;

    int x = -200,y = -200;
    int w = 400,h=400;
    scene_rect.setX(x);
    scene_rect.setY(y);
    scene_rect.setWidth(w);
    scene_rect.setHeight(h);
    scene=view->scene();
    scene->setBackgroundBrush (QBrush(qRgb (173,241,174)));

    QPen pen(qRgb (140,159,141));
    pen.setWidth (0);

    auto  *gi = new ProcessNode(0,0,new LinkingNodes(LK_ADD,nullptr));
    gi->setFlag (QGraphicsItem::ItemIsMovable);


    //QLinearGradient gLg(rect.topLeft (),rect.bottomRight ());
    //gLg.setColorAt (0,qRgb (221,180,68));
    //gLg.setColorAt (1,qRgb (221,240,68));
    gi->setPen (pen);
    //4gi->setBrush (gLg);
    gi->setOpacity (0.8);

    gi->moveBy (-80,-60);

    scene->addItem (gi);
    gi = new ProcessNode(10,10,new LinkingNodes(LK_ADD,nullptr),NodeType::ND_OPERATION);
    gi->setFlag(QGraphicsItem::ItemIsMovable);
    gi->setFlag(QGraphicsItem::ItemIsSelectable);

    scene->addItem (gi);
    //view->setScene (scene);
//    view->setRenderHint (QPainter::Antialiasing);
//    view->setWindowFlag (Qt::WindowMinMaxButtonsHint,false);
//    view->show ();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    scene->setSceneRect(0,0,20,20);
}

