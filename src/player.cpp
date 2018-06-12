#include "player.h"

Player::Player(int x, int y, Map& m, int _mode)
        :coordinate(x, y)
{
            m.setPlace(x, y , player);
            mode = _mode;
            isdead = false;
            have_key = false;
}