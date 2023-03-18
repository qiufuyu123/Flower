#ifndef PROCESSNODE_H
#define PROCESSNODE_H

#include"linkingnodes.h"
#include <QGraphicsRectItem>

#define LINKING_POINT_SZ 50
#define LINKING_POINT_H 35
#define LINKING_POINT_W 20
typedef enum
{
    ND_INPUT,
    ND_OUTPUT,
    ND_PROCESS,
    ND_OPERATION,
    ND_NR
}NodeType;
class ProcessNode : public QGraphicsRectItem
{
private:
    QRect m_rect;
    NodeType m_type;
    LinkingNodes *binding_node;
    int select_idx=-1;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
public:
    ProcessNode(int x,int y,LinkingNodes *nodes, NodeType type=NodeType::ND_INPUT);
    void SetSelectedPort(int idx,bool is_left=true);
    QRect GetPortRect(int idx);
};

#endif // PROCESSNODE_H
