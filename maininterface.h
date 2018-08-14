#ifndef MAININTERFACE_H
#define MAININTERFACE_H


#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QSound>
#include <QMap>
#include "cardpicture.h"
#include "gameprocess.h"
#include "hand.h"


namespace Ui {
class mainInterface;
}

class mainInterface : public QWidget
{
    Q_OBJECT

public:
    explicit mainInterface(QWidget *parent = 0);
    ~mainInterface();
    void init();
    void initCardsMap();//初始化m_Cards

    void cutCardPic(int x,int y,card c);
    void updateCards(Player* player);
    void pickingCardsAnimation(Player* player);
    void playerStartCallingLord();
    void playerStartPlayingHand();
    void paintEvent(QPaintEvent *);

    void reStart();
    void setColor();

public slots:
    void startProcess(gameProcess::gameStatus status);
    void pickingCards();
    void cardSelected();
    void playingHand(Player* player, card out);
    void setPlayerStatus(Player* player,Player::playerStatus status);
    void change();
    /*按钮槽*/
    void on_start_clicked();

    void on_playhand_clicked();
    void on_pass_clicked();
    void on_continue_clicked();
    void on_tip_clicked();
    void changeToRed();
    void changeToYellow();
    void changeToGreen();
    void changeToBlue();
    void addTwoCards();
    void addFourCards();
    void timeDisplay();         //倒数时间显示

private:
    Ui::mainInterface *ui;
    QMap<card,cardPicture *> m_Cards;
    cardPicture* m_Selected;

    QPixmap m_cardBackPic;
    QPixmap m_cardBasePic;
    QPixmap m_AllCardsPic;

    QLabel* m_rePickingCards;   //重新发牌标识
    QLabel* m_timeLabel;        //显示倒数时间
    int time;                   //倒数时间
    QTimer* timer;
    cardPicture* m_movingcard;
    cardPicture* m_basecard;
    int cardToGet;
    QPoint m_basecardPos;
    int moveDistance;                //移动的距离
    QTimer* m_pickingCardTimer;
    gameProcess* m_gameprocess;

    /*按钮*/
    QPushButton* m_start;
    QPushButton* m_playhand;
    QPushButton* m_pass;
    QPushButton* m_continue;
    QPushButton* m_tip;
    QPushButton* m_red;
    QPushButton* m_yellow;
    QPushButton* m_green;
    QPushButton* m_blue;

    /*音效*/
//    QSound* bkMusic;

};

#endif // MAININTERFACE_H
