#include "card.h"

card::card(){

}

card::card(card_point p, card_color c){
    point = p;
    color = c;
}

card::card(int num){
    if(num<=56){
        point = card_point(num%14);
        color = card_color(num/14);
    }
    else{
        point = card_point((num-56)%13+1);
        color = card_color((num-56)/13);
    }
}

void card::setPoint(card_point p){
    point =p;
}

void card::setColor(card_color c){
    color =c;
}

card_point card::getPoint(){
    return point;
}

card_color card::getColor(){
    return color;
}
