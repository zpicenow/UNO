#ifndef REBOT_H
#define REBOT_H


#include <QWidget>
#include <QThread>
#include "player.h"
#include  "method.h"

class rebot : public Player
{
public:
    rebot(QWidget* parent);
    void beginPlayingHand();
    void beginPickingCard();
};

#endif // REBOT_H
