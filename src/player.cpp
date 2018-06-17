#include "player.h"

Player::Player(int x, int y, Map& m, int _mode)
        :Coordinate(x, y)
{
    m.setPlace(*this , player);
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
}