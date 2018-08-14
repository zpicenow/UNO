#include "gameprocess.h"
#include<QDebug>

gameProcess::gameProcess(QWidget *parent) : QWidget(parent)
{
    m_LeftPlayer = new rebot(this);
    m_UpPlayer = new rebot(this);
    m_RightPlayer = new rebot(this);
    m_DownPlayer = new userPlayer(this);
    clockwise = true;
    m_currentPlayer = m_DownPlayer;
    m_hitPlayer = NULL;
    m_hitCard.setPoint(card_point_begain);
    initCards();
    m_LeftPlayer->setNextPlayer(m_DownPlayer);
    m_UpPlayer->setNextPlayer(m_LeftPlayer);
    m_DownPlayer->setNextPlayer(m_RightPlayer);
    m_RightPlayer->setNextPlayer(m_UpPlayer);
    //连接通知Player的信号
    connect(this,SIGNAL(tellHitPlayer(Player*,card)),m_DownPlayer,SLOT(setHitPlayer(Player*,card)));
    connect(this,SIGNAL(tellHitPlayer(Player*,card)),m_LeftPlayer,SLOT(setHitPlayer(Player*,card)));
    connect(this,SIGNAL(tellHitPlayer(Player*,card)),m_RightPlayer,SLOT(setHitPlayer(Player*,card)));
    connect(this,SIGNAL(tellHitPlayer(Player*,card)),m_UpPlayer,SLOT(setHitPlayer(Player*,card)));


    //出牌信号
    connect(m_DownPlayer,SIGNAL(tellPlayingHand(Player*,card)),this,SLOT(playerPlayHand(Player*,card)));
    connect(m_LeftPlayer,SIGNAL(tellPlayingHand(Player*,card)),this,SLOT(playerPlayHand(Player*,card)));
    connect(m_RightPlayer,SIGNAL(tellPlayingHand(Player*,card)),this,SLOT(playerPlayHand(Player*,card)));
    connect(m_UpPlayer,SIGNAL(tellPlayingHand(Player*,card)),this,SLOT(playerPlayHand(Player*,card)));
}

Player* gameProcess::getLeftPlayer(){
    return m_LeftPlayer;
}

Player* gameProcess::getUpPlayer(){
    return m_UpPlayer;
}

Player* gameProcess::getRightPlayer(){
    return m_RightPlayer;
}

Player* gameProcess::getDownPlayer(){
    return m_DownPlayer;
}

void gameProcess::setCurrentPlayer(Player *player){
    m_currentPlayer = player;
}

Player* gameProcess::getCurrentPlayer(){
    return m_currentPlayer;
}

Player* gameProcess::getHitPlayer(){
    return m_hitPlayer;
}

void gameProcess::setHidPlayer(Player *player){
    m_hitPlayer = player;
}

Player* gameProcess::getNextPlayer(){
    if(clockwise==true){
        if(m_currentPlayer == m_LeftPlayer){
            return m_DownPlayer;
        }
        else if(m_currentPlayer == m_DownPlayer){
            return m_RightPlayer;
        }
        else if(m_currentPlayer == m_RightPlayer){
            return m_UpPlayer;
        }
        else if(m_currentPlayer == m_UpPlayer){
            return m_LeftPlayer;
        }
    }
    else{
        if(m_currentPlayer == m_LeftPlayer){
            return m_UpPlayer;
        }
        else if(m_currentPlayer == m_UpPlayer){
            return m_RightPlayer;
        }
        else if(m_currentPlayer == m_RightPlayer){
            return m_DownPlayer;
        }
        else if(m_currentPlayer == m_DownPlayer){
            return m_LeftPlayer;
        }
    }
}

Player* gameProcess::getPrePlayer(){
    if(clockwise==false){
        if(m_currentPlayer == m_LeftPlayer){
            return m_DownPlayer;
        }
        else if(m_currentPlayer == m_DownPlayer){
            return m_RightPlayer;
        }
        else if(m_currentPlayer == m_RightPlayer){
            return m_UpPlayer;
        }
        else if(m_currentPlayer == m_UpPlayer){
            return m_LeftPlayer;
        }
    }
    else{
        if(m_currentPlayer == m_LeftPlayer){
            return m_UpPlayer;
        }
        else if(m_currentPlayer == m_UpPlayer){
            return m_RightPlayer;
        }
        else if(m_currentPlayer == m_RightPlayer){
            return m_DownPlayer;
        }
        else if(m_currentPlayer == m_DownPlayer){
            return m_LeftPlayer;
        }
    }
}

void gameProcess::getCards(Player *player, int n){
    QTime time;
    for(int j=0;j<n;++j){
        time = QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int i = qrand()% (m_allCards.size());
        player->getCards().append(m_allCards[i]);
        m_allCards.removeAt(i);
    }
}

void gameProcess::playerPlayHand(Player *player, card out){
    if(out.getPoint()!=card_point_begain&&out.getPoint()!=card_end){
        m_hitPlayer = player;
        m_hitCard = out;
        if(out.getPoint()==card_turn) {
            emit changeClockwise();
            clockwise = !clockwise;
        }
        if(out.getPoint()==card_addtwo){
            emit twoCards();
        }
        if(out.getPoint()==card_addfour){
            emit fourCards();
        }
        if(out.getPoint()==card_change){

        }
        emit tellHitPlayer(player,out);
    }
    emit tellPlayerPlayHand(player,out);
    if(player->getCards().isEmpty()){
        emit tellPlayerStatus(player,Player::winning);
        return;
    }
    m_currentPlayer->setNextPlayer(getNextPlayer());
    m_currentPlayer=player->getNextPlayer();
    emit tellPlayerStatus(m_currentPlayer,Player::waitingPlayingHand);
    m_currentPlayer->beginPlayingHand();
}

void gameProcess::beginPlayerHand(){
    emit tellPlayerStatus(m_currentPlayer,Player::waitingPlayingHand);
    m_currentPlayer->beginPlayingHand();
}

card gameProcess::getHitCard(){
    return m_hitCard;
}

void gameProcess::initCards(){
    for(int point = card_zero;point<=card_addtwo;++point){
        for(int color=red;color<red_1;++color){
            m_allCards.append(card((card_point)point,(card_color)color));
        }
    }
    for(int point = card_one;point<=card_addtwo;++point){
        for(int color=red_1;color<color_end;++color){
            m_allCards.append(card((card_point)point,(card_color)color));
        }
    }
    for(int i=0;i<8;++i){
        card c;
        if(i<4) m_allCards.append(card((card_point)card_change,(card_color)(i+1)));
        else m_allCards.append(card((card_point)card_addfour,(card_color)(i+1)));
    }
}

QList<card> gameProcess::getAllCards(){
    return m_allCards;
}

void gameProcess::restart(){
    m_hitPlayer=NULL;
    m_hitCard.setPoint(card_point_begain);
    m_allCards.clear();
    initCards();
}

bool gameProcess::getClockwise(){
    return clockwise;
}

void gameProcess::setClockwise(bool w){
    clockwise = w;
}

void gameProcess::start(){
    emit tellGameProcess(playingCard);
    beginPlayerHand();
}
 void gameProcess::setHitCard(card out){
     m_hitCard = out;
 }
