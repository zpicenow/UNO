#include "hand.h"

hand::hand()
{

}

hand::hand(card out_card){
    try_out = out_card;
}

bool hand::defeat(hand &hands){
    if(hands.getPoint()==card_addtwo||hands.getPoint()==card_addfour)
    {
        if(try_out.getPoint()==card_addfour||try_out.getPoint()==card_addtwo){
            return true;
        }
        else{
            return false;
        }
    }
    if(try_out.getPoint() == card_change || try_out.getPoint()==card_addfour){
        return true;
    }
    else if(try_out.getPoint()==hands.getPoint()) return true;
    else if((try_out.getColor()>4?try_out.getColor()-4:try_out.getColor())==(hands.getColor()>4?hands.getColor()-4:hands.getColor())) return true;
    return false;
}

card_color hand::getColor(){
    return try_out.getColor();
}

card_point hand::getPoint(){
    return try_out.getPoint();
}
