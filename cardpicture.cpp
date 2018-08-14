#include "cardpicture.h"

cardPicture::cardPicture(QWidget *parent) : QWidget(parent)
{
    m_turn = false;
    m_selected = false;
    QPixmap pic(":/img/img/uno_back.png");
    m_back = pic.copy(0,0,85,105);
}

void cardPicture::setPic(QPixmap &pic){
    m_pic = pic;
    resize(pic.size());
}

void cardPicture::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    if(m_turn){
        painter.drawPixmap(this->rect(),m_pic);
    }
    else{
        painter.drawPixmap(this->rect(),m_back);
    }
}

void cardPicture::setCard(card &c){
    m_card = c;
}

card cardPicture::getCard(){
    return m_card;
}

void cardPicture::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        emit tellSelected();
    }
}

void cardPicture::setTurn(bool t){
    if(m_turn!=t){
        m_turn =  t;
    }

}

void cardPicture::setSelected(bool s){
    if(m_selected!=s){
        m_selected = s;
    }
    return;
}

bool cardPicture::getSelected(){
    return m_selected;
}

QPixmap &cardPicture::getPic(){
    return m_pic;
}

bool cardPicture::getTurn(){
    return m_turn;
}
