#include "flowerview.h"

#include <QWheelEvent>
#include<QRect>
#include<QGraphicsItem>
#include"processnode.h"
void FlowerView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        is_pressed=true;
        now_pos=event->pos();
    }else if(event->button()==Qt::LeftButton)
    {
        for (QGraphicsItem *i:m_scene->items()) {
            if(i->type()==QGraphicsLineItem::Type)
                continue;
            ProcessNode *n=(ProcessNode*)i;
            for (int j=0;j<4 ;j++ ) {
                QRect r=n->GetPortRect(j);
                r.setX(r.x()+n->x());
                r.setY(r.y()+n->y());
                //r=r.adjusted(-1,-1,)
                QPointF mp=mapToScene(event->localPos().toPoint());
                if(r.contains(mp.toPoint()))
                {
                    if(is_selecting)
                    {

                    }
                    else
                    {
                        n->SetSelectedPort(j);
                        is_selecting=true;
                        selecting_from=mp.toPoint();
                    }
                }
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void FlowerView::mouseReleaseEvent(QMouseEvent *event)
{

//    if(is_selecting)
//    {
//        if(temp_item)
//            scene()->removeItem(temp_item);
//        temp_item=nullptr;
//        is_selecting=false;
//    }
    is_pressed=false;
    now_pos=(event->pos());
    QGraphicsView::mouseReleaseEvent(event);
}

void FlowerView::mouseMoveEvent(QMouseEvent *event)
{
    if(is_pressed)
    {
        QPointF cur_pos=(event->pos())-now_pos;
        //rect=QGraphicsView::frameRect();
        int nx=rect.x()+cur_pos.x();
        int ny=rect.y()+cur_pos.y();

        rect.setX(nx);
        rect.setY(ny);
        //rect.setWidth(nx+800);
        //rect.setHeight(ny+600);
        //QGraphicsView::setFrameRect(rect);
        for (QGraphicsItem *i:m_scene->items()) {
            i->setX(i->x()+ cur_pos.x());
            i->setY(i->y()+cur_pos.y());
        }
        //scene()->setSceneRect(rect);
        //scene()->setFocusOnTouch(true);
        now_pos=(event->pos());
        qDebug("x:%d,y:%d\n",nx,ny);
    }
    if(is_selecting)
    {
        QPoint n=mapToScene(event->localPos().toPoint()).toPoint();
        if(!temp_item)
            temp_item=scene()->addLine(selecting_from.x(),selecting_from.y(),n.x(),n.y());
        else
            temp_item->setLine(selecting_from.x(),selecting_from.y(),n.x(),n.y());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void FlowerView::wheelEvent(QWheelEvent *event)
{


    if(event->delta()>0)
    {
        this->scale(1.1, 1.1);
        m_scalnum *= 1.1;
    }
    else
    {
        this->scale(1/1.1, 1/1.1);
        m_scalnum /= 1.1;
    }

    QGraphicsView::wheelEvent(event);

}

FlowerView::FlowerView(QWidget *parent)
    :QGraphicsView(parent)
{
    rect.setX(-400);
    rect.setY(-600);
    rect.setWidth(800);
    rect.setHeight(600);
    m_scene=new QGraphicsScene(rect);
    QGraphicsView::setScene(m_scene);
    is_pressed=false;
    setMouseTracking(true);
}
