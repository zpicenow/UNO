#ifndef HAND_H
#define HAND_H


#include<card.h>
#include<QVector>

class hand
{
public:
    hand();
    hand(card out_card);
    bool defeat(hand &hand);
    card_color getColor();
    card_point getPoint();

private:
    card try_out;
};

#endif // HAND_H
