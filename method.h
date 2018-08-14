#ifndef METHOD_H
#define METHOD_H


#include <QWidget>
#include "player.h"
#include "hand.h"
#include <QMap>

class method
{
public:
    method(Player* player,QList<card> cards);
    card makeDecision();
    card_color setColor();


protected:
    Player* m_player;
    QList<card> m_cards;
};

#endif // METHOD_H
