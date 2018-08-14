#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H


#include <QWidget>
#include <QTime>
#include <QMap>
#include "card.h"
#include "rebot.h"
#include "userplayer.h"


class gameProcess:public QWidget
{
    Q_OBJECT
public:
    enum gameStatus{
        pickingCard,
        started,
        playingCard
    };
    gameProcess(QWidget *parent = 0);
    void getCards(Player *player,int n);//添加牌到玩家的牌组
    void setCurrentPlayer(Player* player);
    Player* getLeftPlayer();
    Player* getUpPlayer();
    Player* getRightPlayer();
    Player* getDownPlayer();
    Player* getCurrentPlayer();
    Player* getNextPlayer();
    Player* getPrePlayer();
    Player* getHitPlayer();
    void setHidPlayer(Player* player);
    gameStatus m_gamestatus;
    void beginPlayerHand();
    card getHitCard();
    void setHitCard(card out);
    void initCards();
    QList<card> getAllCards();
    void restart();
    bool getClockwise();
    void setClockwise(bool w);
    void start();
signals:
    /*告知MainInterface的信号*/
    void tellGameProcess(gameProcess::gameStatus);
    void tellPlayerStatus(Player* player,Player::playerStatus status);
    void tellPlayerPlayHand(Player* player,card out);
    void changeClockwise();
    void twoCards();
    void fourCards();
    /*告知Player的信号*/
    void tellHitPlayer(Player* player,card out);

public slots:
    void playerPlayHand(Player* player,card out);
private:
    rebot* m_LeftPlayer;
    rebot* m_UpPlayer;
    rebot* m_RightPlayer;
    userPlayer* m_DownPlayer;

    Player* m_currentPlayer;        //当前玩家
    Player* m_hitPlayer;            //当前最大牌的玩家
    QList<card> m_allCards;         //所有牌的card
    bool clockwise;
    card m_hitCard;         //当前最大牌
};

#endif // GAMEPROCESS_H
