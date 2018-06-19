#include "player.h"

Player::Player(int x, int y, Map& m, int _mode)
        :Coordinate(x, y)
{
    this->set(*this, m);
    mode = _mode;
    isdead = false;
    have_key = false;
}

Player::Player(Coordinate coord, Map& m, int _mode)
        :Coordinate(coord)
{
    m.setPlace(*this , player);
    mode = _mode;
    isdead = false;
    have_key = false;
    pass = false;
}

void Player::walk(char com, Map& m){
    int pre_x = x;
    int pre_y = y;
    if(com == 's')  y++;
    else if(com == 'a') x--;
    else if(com == 'w') y--;
    else if(com == 'd') x++;
    if(x>6) x=6;
    else if (x<0)   x=0;
    if(y>6) y=6;
    else if (y<0)   y=0;
    /*if(m.isfree(Coordinate(x,y))){
        m.setPlace(Coordinate(pre_x,pre_y), Non);
        m.setPlace(*this, player);
    }
    else{
        x = pre_x;
        y = pre_y;
    }*/
    if(! (set(Coordinate(pre_x, pre_y), m))){
        x = pre_x;
        y = pre_y;
    }
}

bool Player::set(Coordinate pre, Map& m){
    OBJ obj = m.collision(*this);
    if(obj == Non){
        m.setPlace(pre, Non);
        m.setPlace(*this , player);
        return true;
    }
    else if(obj == Wall){
        return false;
    }
    else if(obj == key){
        m.setPlace(pre, Non);
        m.setPlace(*this , player);
        have_key = true;
    }
    else if(obj == spot){
        m.setPlace(pre, Non);
        m.setPlace(*this , player);
        pass = true;
    }
    else if(obj == ghost){
        m.setPlace(pre,Non);
        isdead =true;
    }
    return true;
}

bool Player::dead_check(){
    return isdead;
}

bool Player::key_check(){
    return have_key;
}

bool Player::pass_check(){
    return pass;
}

void Player::be_killed(){
    isdead = true;
}
