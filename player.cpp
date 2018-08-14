#include "player.h"
#include<QtAlgorithms>
Player::Player(QWidget *parent) : QWidget(parent)
{
    m_hitPlayer=NULL;
    m_hitCard.setPoint(card_point_begain);
    m_cardToPlay.setPoint(card_point_begain);
}

Player::Player(int id, QString name, int score, int level)
{
    m_id=id;
    m_name=name;
    m_score=score;
    m_level=level;
    m_hitPlayer=NULL;
    m_hitCard.setPoint(card_point_begain);
    m_cardToPlay.setPoint(card_point_begain);
}

void Player::setName(QString name)
{
    m_name=name;
}

QString Player::getName()
{
    return m_name;
}

void Player::setLevel(int level)
{
    m_level=level;
}

int Player::getLevel()
{
    return m_level;
}

void Player::setScore(int s)
{
    m_score=s;
}

int Player::getScore()
{
    return m_score;
}

void Player::setId(int id)
{
    m_id=id;
}

int Player::getId()
{
    return m_id;
}

void Player::addCard(card c)
{
    m_cards.append(c);
    return;
}

void Player::removeCard(card c)
{
    m_cards.removeOne(c);
    return;
}

void Player::removeCard(QList<card> &c)
{
    for(int i=0;i<c.size();i++)
        m_cards.removeOne(c[i]);
    return;
}

QList<card>& Player::getCards()
{
    return m_cards;
}

QList<int>& Player::getCardsIntList()
{
    return m_CardsIntList;
}

card &Player::getCardToPlay()
{
    return m_cardToPlay;
}

void Player::sortCard()
{
   qSort(m_cards.begin(),m_cards.end(),qGreater<card>());
   return;
}

void Player::playHand(card out)
{
    if(out.getPoint()!=card_point_begain&&out.getPoint()!=card_end)  m_cards.removeOne(out);    //从牌组中清除
    emit tellPlayingHand(this,out);           //发送信号
}

void Player::addCardToPlay(card out)
{
    m_cardToPlay = out;
}

Player* Player::getHitPlayer()
{
    return m_hitPlayer;
}

void Player::setHitPlayer(Player *player, card out)
{
    m_hitPlayer=player;
    m_hitCard=out;
}

Player* Player::getNextPlayer()
{
    return m_nextPlayer;
}

void Player::setNextPlayer(Player *player)
{
    m_nextPlayer=player;
}

card Player::getHitCard()
{
    return m_hitCard;
}

void Player::beginPickingCard()
{}

void Player::beginPlayingHand()
{}
