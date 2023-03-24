#ifndef LINKINGNODES_H
#define LINKINGNODES_H

#include <QObject>

typedef enum
{
    LK_ADD,
    LK_MINUS,
    LK_MUL,
    LK_DIV,
    LK_OPER_NR,

    LK_STRING,
    LK_INT,
    LK_FLOAT,
    LK_BOOL,
    LK_DECL_NR,
    LK_PRINT,
    LK_NR
}LinkingType;

typedef struct
{
    QString tag;
    int type;
}LinkingTag_t;
#define CN QString::fromLocal8Bit
class LinkingNodes : public QObject
{
    Q_OBJECT
private:
    QString default_title_trans[LK_NR][2]={
        {CN("加"),CN("将A+B的\n值输出给C")},
        {CN("减"),"将A-B的值输出给C"},
        {CN("乘"),"将A*B的值输出给C"},
        {"除","将A/B的值输出给C"},
        {"",""},
        {"字符串","定义一段字符串"},
        {"整数","定义一个整数"},
        {"逻辑","定义逻辑变量"},
        {"",""},
        {CN("打印文本"),CN("打印str的内容")}};
    int m_input_num,m_output_num;
    LinkingNodes *m_left_nodes[4]={nullptr,nullptr,nullptr,nullptr};
    LinkingNodes *m_right_nodes[4]={nullptr,nullptr,nullptr,nullptr};

    QString title,desc;



    void PrepareFont();
    void CalcSize();
public:
    explicit LinkingNodes(int left_ports=1,int right_ports=1,QObject *parent = nullptr);
    explicit LinkingNodes(int template_type, QObject *parent=nullptr);
    int GetInputNums();
    int GetOutputNums();
    LinkingNodes* GetInputNodes(int idx);
    LinkingNodes* GetOutputNodes(int idx);
    void SetInputLink(int idx,LinkingNodes *next);
    void SetOutputLink(int idx,LinkingNodes *next);
    QString GetTitle();
    QString GetDesc();
    int RequireMidWidth;
    int RequireLeftWidth;
    int RequireRightWidth;
    int UnitHeight;
    int TitleHeight;
    LinkingTag_t m_tags[4][2];
    static QFont *title_font,*desc_font,*port_font;
signals:

};

#endif // LINKINGNODES_H
