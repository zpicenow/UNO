#include "cardlist.h"
#include "ui_cardlist.h"

cardlist::cardlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cardlist)
{
    card_num = 0;
    originWindow();
    ui->setupUi(this);
}

cardlist::~cardlist()
{
    delete ui;
}

void cardlist::originWindow(){
    setFixedHeight(105);
}

QPixmap cardlist::cardGet(int num){
    int x,y;
    if(num>=56){
        x = num%14-1;
        y = num/14;
    }
    else{
        num-=56;
        x=num%13;
        y=num/13+3;
    }
    QPixmap pics(":/img/img/uno_card.png");
    QPixmap cardpic=pics.copy(x*_WCard,y*_HCard,_WCard,_HCard);
    return cardpic;
}

void cardlist::addCard(int num){
    QLabel *n = new QLabel;
    n->setPixmap(cardGet(num));
    card_labels.push_back(n);
    n->setVisible(true);
    n->setGeometry(14*card_num,0,_WCard,_HCard);
    card_num++;
    setFixedWidth(14*card_num+64);
}

void cardlist::clearAll(){
    for(int i=0;i<card_num;++i){
        card_labels[i]->hide();
    }
    card_num =0;
}

void cardlist::update(QVector<int> num){
    clearAll();
    int i =0;
    for(;i<num.size();++i){
        addCard(num[i]);
    }
}
