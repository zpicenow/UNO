#include "method.h"
#include <QList>
#include<algorithm>

method::method(Player *player, QList<card> cards){
    m_player=player;
    m_cards = cards;
}
card method::makeDecision(){
    hand hands(m_player->getHitCard());
    QList<card> canPlay;
    for(QList<card>::iterator i = m_cards.begin();i!=m_cards.end();++i){
        hand r(*i);
        if(r.defeat(hands)) canPlay.push_back(*i);
    }
    if(canPlay.isEmpty()) return card(card_end,color_end);
    int color[5];
    for(QList<card>::iterator i = m_cards.begin();i!=m_cards.end();++i){
        if(i->getPoint()==card_addfour||i->getPoint()==card_change) {
            color[4]++;
            continue;
        }
        if(i->getColor()==red||i->getColor()==red_1) color[0]++;
        else if(i->getColor()==yellow||i->getColor()==yellow_1) color[1]++;
        else if(i->getColor()==green||i->getColor()==green_1) color[2]++;
        else if(i->getColor()==blue||i->getColor()==blue_1) color[3]++;
    }
    int m = *std::max(std::begin(color),std::end(color));
    for(int i=0;i<5;++i){
        if(color[i]==m){
            color[i]=0;
            if(i!=4){
                for(QList<card>::iterator j=canPlay.begin();j!=canPlay.end();++j){
                    if((j->getColor()>4?j->getColor()-4:j->getColor())==i) return *j;
                }
            }
            else{
                break;
            }
        }
    }
    m = *std::max(std::begin(color),std::end(color));
    if(m>=1)
        for(int i=0;i<5;++i){
        if(color[i]==m){
            for(QList<card>::iterator j=canPlay.begin();j!=canPlay.end();++j){
                if((j->getColor()>4?j->getColor()-4:j->getColor())==i) return *j;
                }
            }
        }
    else{
        for(QList<card>::iterator j=canPlay.begin();j!=canPlay.end();++j){
            if(j->getPoint()==card_addfour||j->getPoint()==card_change) return *j;
            }
    }
    return canPlay[0];
}

card_color method::setColor(){
    int color[4];
    for(QList<card>::iterator i = m_cards.begin();i!=m_cards.end();++i){
        if(i->getColor()==red||i->getColor()==red_1) color[0]++;
        else if(i->getColor()==yellow||i->getColor()==yellow_1) color[1]++;
        else if(i->getColor()==green||i->getColor()==green_1) color[2]++;
        else if(i->getColor()==blue||i->getColor()==blue_1) color[3]++;
    }
    int m = *std::max(std::begin(color),std::end(color));
    for(int i=0;i<4;++i){
        if(color[i]==m){
            return (card_color)i;
        }
    }
}
