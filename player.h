#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include "card.h"
#include <QLabel>

inline bool operator == (card c1,card c2)
{
    return (c1.getPoint()==c2.getPoint())&&(c1.getColor()==c2.getColor());
}

inline uint qHash(card& c)
{
    return c.getPoint()*100  + c.getColor();
}

inline bool operator <(card c1,card c2)
{
    if(c1.getPoint()==c2.getPoint())
        return c1.getColor()<c2.getColor();
    else
        return c1.getPoint()<c2.getPoint();
}


class Player : public QWidget
{
    Q_OBJECT

public:
    enum playerStatus
    {
       waitingCallingLord,
       waitingPlayingHand,
       winning,
    };

    Player(QWidget *parent = 0);
    Player(int id=0,QString name="Unknown", int score=0, int level=0);

    void setName(QString name);
    QString getName();
    void setScore(int s);
    int getScore();
    void setLevel(int l);
    int getLevel();
    void setId(int id);
    int getId();

    void sortCard();            //牌排序
    void addCard(card c);       //添加牌
    void removeCard(card c);    //清除牌
    void removeCard(QList<card> &c);

    void playHand(card out);
    QList<card>& getCards();
    QList<int>& getCardsIntList();
    card& getCardToPlay();

    void addCardToPlay(card out);
    Player* getHitPlayer();
    card getHitCard();
    Player* getNextPlayer();
    void setNextPlayer(Player* player);

    virtual void beginPlayingHand();
    virtual void beginPickingCard();

    QLabel* passLabel;

    int m_betOrder;
signals:
    void tellPlayingHand(Player* player,card out);

public slots:
    void setHitPlayer(Player* player,card out);

protected:
    int m_id;
    QString m_name;
    int m_score;
    int m_level;

    Player* m_nextPlayer;
    Player* m_hitPlayer;
    card m_hitCard;

    QList<card> m_cards;             //牌组
    QList<int> m_CardsIntList;       //整数数组

    card m_cardToPlay;       //要打出去的牌
    card m_lastPlayedCard;   //上次出牌
    playerStatus m_playerStatus;     //玩家状态

};
#endif // PLAYER_H
