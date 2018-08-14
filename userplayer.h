#ifndef USERPLAYER_H
#define USERPLAYER_H


#include <QWidget>
#include "player.h"

class userPlayer: public Player
{
public:
    userPlayer(QWidget* parent);
    void beginPlayingHand();
    void beginPickingCard();
};


#endif // USERPLAYER_H
