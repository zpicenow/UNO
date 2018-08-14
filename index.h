#ifndef INDEX_H
#define INDEX_H


#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QEvent>

namespace Ui {
class Index;
}

class Index : public QWidget
{
    Q_OBJECT

public:
    explicit Index(QWidget *parent = 0);
    ~Index();

private:
    Ui::Index *ui;
    void originWindow();                            //初始化窗体
    void paintEvent(QPaintEvent * event);           //绘图事件
    void originStartButton();                       //初始化 进入单击模式按钮
    void originHelpButton();                      //初始化 进入联机模式按钮
    bool eventFilter(QObject * obj, QEvent * event);//事件过滤器
    QPushButton * start;  //单机按钮
    QPushButton * help; //联机按钮
    //非ui成员:
    bool canStart;        //是否可以点击单机按钮(为了防止多次点击)
    bool canHelp;       //是否可以点击联机按钮(为了防止多次点击)
};

#endif // INDEX_H
