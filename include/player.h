#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"
#include "map.h"
#include <map>
#include <vector>
using namespace std;
class Player: public Coordinate{
    public:
        Player(int x, int y, Map& m, int _mode);
        Player(Coordinate , Map& , int);
        void walk(char , Map&);
        void walk(Map&);
        void be_killed();
        bool dead_check();
        bool key_check();
        bool pass_check();
    private:
        int mode;
        int sight[5][5];
        map<Coordinate,int> mapping;
        map<Coordinate,float> score; 
        bool isdead;
        bool have_key;
        bool pass;
        void look_around(Map&);
        void remember(Map &);
        char find_path(Map &);
        bool set(Coordinate, Map&);
        int repeat_command[4];
        char last_command;
        
};

#endif