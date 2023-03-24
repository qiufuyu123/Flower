#include "flowerview.h"

#include <QWheelEvent>
#include<QRect>
#include<QGraphicsItem>
#include"processnode.h"
#include"linkingcurve.h"
#include<QVector>
void FlowerView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        is_pressed=true;
        now_pos=mapToScene(event->localPos().toPoint());
    }else if(event->button()==Qt::LeftButton)
    {
        for (QGraphicsItem *i:m_scene->items()) {
            ProcessNode *n=(ProcessNode*)i;
            if(i->type()==QGraphicsLineItem::Type || i->type()==LKCURVE_TYPE)
                continue;

            for (int j=0;j<4 ;j++ ) {
                QRect r=n->GetPortRect(j);
//                r.setTopLeft(n->mapToScene(r.x(),r.y()).toPoint());
//                r.setBottomRight(n->mapToScene(r.bottomRight()).toPoint());
                //r=r.adjusted(-1,-1,)
                QPointF mp=mapToScene(event->localPos().toPoint());
                if(r.contains(mp.toPoint()))
                {
                    qDebug("[%d %d]\n",mp.toPoint().x(),mp.toPoint().y());
                    if(is_selecting)
                    {
                        if(n==node_from&&j==port_from)
                            continue;
                        LinkingNodes *nxt=n->binding_node->GetInputNodes(j);
                        if(nxt)
                            continue;
                        node_from->binding_node->SetInputLink(port_from,n->binding_node);
                        temp_item->BindNode(node_from,port_from,n,j);
                        linking_lines.append(temp_item);
                        is_selecting=false;
                        temp_item=nullptr;
                        return;
                    }
                    else
                    {
                        n->SetSelectedPort(j);
                        is_selecting=true;
                        node_from=n;
                        port_from=j;
                        return;
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
    now_pos=mapToScene(event->localPos().toPoint());
    QGraphicsView::mouseReleaseEvent(event);
}

void FlowerView::mouseMoveEvent(QMouseEvent *event)
{
    if(is_pressed)
    {
        QPointF cur_pos=mapToScene(event->localPos().toPoint())-now_pos;
        for (QGraphicsItem *i:m_scene->items()) {
            i->setX(i->x()+ cur_pos.x());
            i->setY(i->y()+cur_pos.y());

        }
        //scene()->setSceneRect(rect);
        //scene()->setFocusOnTouch(true);
        now_pos=mapToScene(event->localPos().toPoint());
        qDebug("x:%d,y:%d\n",cur_pos.x(),cur_pos.y());
    }
    if(is_selecting)
    {
        QRect r=node_from->GetPortRect(port_from);
        QPoint n=mapToScene(event->localPos().toPoint()).toPoint();
        QPoint start_p(r.x()+node_from->x(),r.y()+node_from->y());
        QPoint end_p(n.x(),n.y());
        QPoint mid_p(0,start_p.y());
        if(port_from>=4)
            mid_p.setX(start_p.x()+100);
        else
            mid_p.setX(start_p.x()-100);
        if(!temp_item)
        {
            temp_item=new LinkingCurve(start_p,mid_p,end_p);
            scene()->addItem(temp_item);
        }
        else
            temp_item->SetCurve(start_p,mid_p,end_p);
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
