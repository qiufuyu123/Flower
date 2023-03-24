#ifndef FLOWERVIEW_H
#define FLOWERVIEW_H

#include <QGraphicsView>
#include"processnode.h"
#include"linkingcurve.h"


class FlowerView : public QGraphicsView
{
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);
private:
    QRect rect;
    QGraphicsScene *m_scene;
    bool is_pressed;
    bool is_selecting=false;
    ProcessNode *node_from,*node_to;
    int port_from,port_to;
    QVector<LinkingCurve*> linking_lines;
    LinkingCurve *temp_item=nullptr;
    QPointF now_pos;
    double m_scalnum;

public:
    FlowerView(QWidget *parent=nullptr);
};

#endif // FLOWERVIEW_H
