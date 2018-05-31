#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"
#include <vector>
class Player: private coordinate{
    public:
        Player(int x, int y):coordinate(x, y);
        
        void remember();
        void find_path;
        void walk();
        void set_state();
    private:
        int sight[3][3];
        vector<int> mapping;
        bool isdead;
        bool have_key;
};

#endif