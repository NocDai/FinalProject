#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"
#include "map.h"
#include <vector>
class Player: private coordinate{
    public:
        Player(int x, int y, Map& m, int _mode);
        
        void walk(char com, Map& m){
            int pre_x = x;
            int pre_y = y;
            if(com == 's'){
                if(y++ > 4)
                    y = pre_y;
            }
            else if(com == 'a'){
                if(x-- < 0)
                    x = pre_x;
            }
            else if(com == 'w'){
                if(y-- < 0)
                    y = pre_y;
            }
            else if(com == 'd'){
                if(x++ > 4)
                    x = pre_x;
            }
            m.setPlace(pre_x, pre_y, Non);
            m.setPlace(x, y, player);
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