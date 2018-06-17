#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"
#include "map.h"
#include <vector>
class Player: private Coordinate{
    public:
        Player(int x, int y, Map& m, int _mode);
        Player(Coordinate , Map& , int );
        void walk(char com, Map& m){
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
            if(m.isfree(Coordinate(x,y))){
                m.setPlace(Coordinate(pre_x,pre_y), Non);
                m.setPlace(*this, player);
            }
            else{
                x = pre_x;
                y = pre_y;
            }
        }
    private:
        int mode;
        int sight[3][3];
        vector<int> mapping;
        bool isdead;
        bool have_key;
        void remember();
        void find_path();
        
        void walk(){}
};

#endif