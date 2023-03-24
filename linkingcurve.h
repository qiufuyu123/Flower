#ifndef LINKINGCURVE_H
#define LINKINGCURVE_H

#include <QGraphicsItem>
#include"processnode.h"
#define LKCURVE_TYPE 100
class LinkingCurve : public QGraphicsItem
{
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QPoint m_start,m_mid,m_end;
    QRectF b_rect;
    ProcessNode *from_node=nullptr;
    int from_port_id;
    ProcessNode *end_node=nullptr;
    int end_port_id;
public:
    QRectF boundingRect() const;
    int type() const;
    LinkingCurve(QPoint p1,QPoint p2,QPoint p3);
    void SetCurve(QPoint p1,QPoint p2,QPoint p3);
    void BindNode(ProcessNode *from,int from_id,ProcessNode *end,int end_id);
    void BindingUpdate();
};

#endif // LINKINGCURVE_H
