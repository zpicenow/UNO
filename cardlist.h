#ifndef CARDLIST_H
#define CARDLIST_H


#include <QWidget>
#include<QPixmap>
#include<QLabel>
#include<QVector>

namespace Ui {
class cardlist;
}

class cardlist : public QWidget
{
    Q_OBJECT

public:
    explicit cardlist(QWidget *parent = 0);
    ~cardlist();
    static const int _WCard=85; //单张牌的宽
    static const int _HCard=105;//单张牌的高
    QPixmap cardGet(int num);  //获取图片
    void addCard(int num);//增加一张牌
    void update(QVector<int> num);        //更新玩家的出牌区域
    void clearAll();//清空玩家的出牌区
    void originWindow();        //初始化窗体属性

private:
    Ui::cardlist *ui;
    int card_num;
    QVector<QLabel*> card_labels;
};

#endif // CARDLIST_H
