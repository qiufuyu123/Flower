#include "linkingcurve.h"

#include <QPainter>

LinkingCurve::LinkingCurve(QPoint p1, QPoint p2, QPoint p3)
{
    SetCurve(p1,p2,p3);
    QPainterPath p(m_start);
    p.quadTo(m_mid,m_end);
    b_rect=p.boundingRect();
}

void LinkingCurve::SetCurve(QPoint p1, QPoint p2, QPoint p3)
{
    m_start=p1;
    m_mid=p2;
    m_end=p3;
    update();
}

void LinkingCurve::BindNode(ProcessNode *from, int from_id, ProcessNode *end, int end_id)
{
    from_node=from;
    from_port_id=from_id;
    end_node=end;
    end_port_id=end_id;
}

void LinkingCurve::BindingUpdate()
{
    if(from_node)
        update();
}
void LinkingCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen old=painter->pen();
    old.setWidth(3);
    painter->setPen(old);
    if(from_node)
    {
        m_start=from_node->GetPortRect(from_port_id).center();
        m_end=end_node->GetPortRect(end_port_id).center();
    }
    QPainterPath p(m_start);
    p.quadTo(m_mid,m_end);
    painter->drawPath(p);
    b_rect=p.boundingRect();
    old.setColor(Qt::black);
    old.setWidth(1);
    painter->setPen(old);
    QRectF box(m_mid.x(),m_mid.y(),20,20);
    QPainterPath p2;
    p2.addRoundedRect(box,10,10);
    painter->fillPath(p2,Qt::black);
    b_rect=b_rect.united(p2.boundingRect());
}

QRectF LinkingCurve::boundingRect() const
{
    return b_rect.adjusted(-5,-5,5,5);
}

int LinkingCurve::type() const
{
    return LKCURVE_TYPE;
}
