#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"
#include "map.h"
#include <vector>
class Player: public Coordinate{
    public:
        Player(int x, int y, Map& m, int _mode);
        Player(Coordinate , Map& , int);
        void walk(char , Map&);
        void be_killed();
        bool dead_check();
        bool key_check();
        bool pass_check();
    private:
        int mode;
        int sight[3][3];
        vector<int> mapping;
        bool isdead;
        bool have_key;
        bool pass;
        void remember();
        void find_path();
        bool set(Coordinate, Map&);
        
        void walk();
};

#endif