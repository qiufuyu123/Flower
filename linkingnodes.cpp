#include "linkingnodes.h"
#include <QFont>
#include<QString>
#include <QFontMetrics>
QFont* LinkingNodes::title_font=nullptr;
QFont* LinkingNodes::desc_font=nullptr;
QFont* LinkingNodes::port_font=nullptr;
void LinkingNodes::PrepareFont()
{
    title_font=new QFont(QString::fromLocal8Bit("宋体"),14);
    port_font=new QFont(QString::fromLocal8Bit("宋体"),12);
    desc_font=port_font;

}

void LinkingNodes::CalcSize()
{
    QFontMetrics fm(*title_font);
    QFontMetrics fm2(*desc_font);
    QFontMetrics fm3(*port_font);
    UnitHeight=fm2.height();
    TitleHeight=fm.height();
    RequireMidWidth= std::max(fm.width(GetTitle()),fm2.width(GetDesc()));
    for(int i=0;i<4;i++)
    {
        int w=fm3.width(m_tags[i][0].tag);
        if(w>RequireLeftWidth)
            RequireLeftWidth=w;
    }
    for(int i=0;i<4;i++)
    {
        int w=fm3.width(m_tags[i][1].tag);
        if(w>RequireRightWidth)
            RequireRightWidth=w;
    }

}

LinkingNodes::LinkingNodes(int left_ports,int right_ports,QObject *parent) : QObject(parent)
{
    m_input_num=left_ports;
    m_output_num=right_ports;
    if(!title_font)
        PrepareFont();
    CalcSize();
}

LinkingNodes::LinkingNodes(int template_type, QObject *parent)
{
    title=default_title_trans[template_type][0];
    desc=default_title_trans[template_type][1];
    if(template_type <= LK_OPER_NR)
    {
        m_input_num=2;
        m_output_num=1;
        m_tags[0][0].tag="A";
        m_tags[1][0].tag="B";
        m_tags[0][1].tag="C";
    }
    if(!title_font)
        PrepareFont();
    CalcSize();
}

int LinkingNodes::GetInputNums()
{
    return  m_input_num;;
}

int LinkingNodes::GetOutputNums()
{
    return  m_output_num;;
}

LinkingNodes *LinkingNodes::GetInputNodes(int idx)
{
    if(idx>3)
        return nullptr;
    return m_left_nodes[idx];
}

LinkingNodes *LinkingNodes::GetOutputNodes(int idx)
{
    if(idx>3)
        return nullptr;
    return m_right_nodes[idx];
}

void LinkingNodes::SetInputLink(int idx, LinkingNodes *next)
{
    if(idx>3)
        return;
    m_left_nodes[idx]=next;
}

void LinkingNodes::SetOutputLink(int idx, LinkingNodes *next)
{
    if(idx>3)
        return;
    m_right_nodes[idx]=next;
}

QString LinkingNodes::GetTitle()
{
    return title;
}

QString LinkingNodes::GetDesc()
{
    return desc;
}
