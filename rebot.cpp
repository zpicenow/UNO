#include "rebot.h"
#include <QThread>
#include <QTime>
#include <QCoreApplication>

rebot::rebot(QWidget* parent):Player(parent)
{

}

void rebot::beginPlayingHand(){
    method method(this,m_cards);
    card out = method.makeDecision();   //智能获取要出的牌

    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    m_cardToPlay = out;
    playHand(out);            //出牌
}

void rebot::beginPickingCard(){
}
