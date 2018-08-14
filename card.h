#ifndef CARD_H
#define CARD_H


enum card_point{
    card_point_begain,
    card_zero,
    card_one,
    card_two,
    card_three,
    card_four,
    card_five,
    card_six,
    card_seven,
    card_eight,
    card_nine,
    card_skip,
    card_turn,
    card_addtwo,
    card_change,
    card_addfour,
    card_end
};

enum card_color{
    color_start,
    red,
    yellow,
    green,
    blue,
    red_1,
    yellow_1,
    green_1,
    blue_1,
    color_end
};

class card
{
private:
    card_point point;
    card_color color;
public:
    card();
    card(card_point p,card_color c);
    card(int num);
    void setPoint(card_point p);
    void setColor(card_color c);
    card_point getPoint();
    card_color getColor();
};

#endif // CARD_H
