#include "processnode.h"
#include <QFontMetrics>
#include<QPainter>
#include <QPainterPath>

QColor color_list[ND_NR]={
  Qt::gray,
  Qt::lightGray,
  Qt::blue,
  Qt::green
};

ProcessNode::ProcessNode(int x,int y,LinkingNodes *nodes,NodeType type)
    :QGraphicsRectItem(x,y,20,10)
{
    m_type=type;
    binding_node=nodes;
    int m=std::max(nodes->GetInputNums(),nodes->GetOutputNums())*LINKING_POINT_SZ;
    setRect(x,y,binding_node->RequireLeftWidth+binding_node->RequireMidWidth+binding_node->RequireRightWidth+LINKING_POINT_W+4,m+binding_node->UnitHeight+2);
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsMovable);
    QGraphicsItem::setFlag(QGraphicsItem::ItemIsSelectable);
}

void ProcessNode::SetSelectedPort(int idx, bool is_left)
{
    if(!is_left)idx+=4;
    select_idx=idx;
    update();
}

QRect ProcessNode::GetPortRect(int idx)
{
    int flg=0;
    int sx=this->x()+2;
    if(idx>=4)
    {
        flg=1;
        idx-=4;
        sx=this->x()+rect().width()-2-LINKING_POINT_W;
    }

    int sy=rect().y()+binding_node->TitleHeight+2+LINKING_POINT_SZ*idx;
    return QRect(sx,sy,LINKING_POINT_W+binding_node->RequireLeftWidth+1,LINKING_POINT_H);
}

void ProcessNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter->save();
    QFontMetrics fm=painter->fontMetrics();
    //int title_w=fm.width(binding_node->GetTitle());
    //int desc_w=fm.width(binding_node->GetDesc());
    //int max_w=std::max(title_w,desc_w);
    int l=boundingRect().x()+2;
    int m=std::max(binding_node->GetInputNums(),binding_node->GetOutputNums());
    //QRectF ori=boundingRect();
    QPainterPath path;
    path.addRoundedRect(boundingRect(), 20, 20);
    //setRect(QGraphicsItem::x(),QGraphicsItem::y(),+LINKING_POINT_W+20,m*LINKING_POINT_SZ+fm.height()+5);
    painter->fillPath(path,color_list[m_type]);
    painter->drawPath(path);
    painter->restore();
    int left_max=binding_node->GetInputNums();
    for(int i=binding_node->TitleHeight+2;i<boundingRect().height()-5 && left_max;i+=LINKING_POINT_SZ,--left_max)
    {
        int px=l;
        int py=rect().y()+i;
        QColor c=Qt::black;
        if(select_idx==binding_node->GetInputNums()-left_max)
            c=Qt::darkBlue;
        painter->fillRect(px,py,LINKING_POINT_W,binding_node->UnitHeight,c);
        painter->setFont(*binding_node->port_font);
        painter->drawText(px+LINKING_POINT_W+1,py+binding_node->UnitHeight, binding_node->m_tags[binding_node->GetInputNums()-left_max][0].tag);
    }
    painter->setFont(*binding_node->title_font);
    QPen p=painter->pen();
    painter->drawText(rect().x()+2+LINKING_POINT_W,rect().y()+binding_node->TitleHeight,binding_node->GetTitle());
    painter->setFont(*binding_node->desc_font);
    QRect desc_rect(rect().x()+4+LINKING_POINT_W+binding_node->RequireLeftWidth,rect().y()+binding_node->TitleHeight+5,binding_node->RequireMidWidth,rect().height()-binding_node->TitleHeight-6);
    painter->drawText(desc_rect,Qt::AlignLeft,binding_node->GetDesc());
    p.setColor(Qt::white);
    p.setStyle(Qt::PenStyle::DashLine);
    p.setWidth(3);
    painter->setPen(p);
    painter->drawLine(rect().x()+4+LINKING_POINT_W,rect().y()+binding_node->TitleHeight+2,rect().x()+binding_node->RequireMidWidth,rect().y()+binding_node->TitleHeight+2);
    /*[] 绘制选中外框*/
    if (this->isSelected()) {
        /*[1]: 绘制外围的矩形框 */
        QPainterPath path2;
        path2.addRoundedRect(boundingRect().adjusted(3,3,-3,-3), 20, 20);
        QPen old=painter->pen();
        QPen p(Qt::GlobalColor::white,3);
        painter->setPen(p);
        painter->drawPath(path2);
        painter->setPen(old);
    }
}
