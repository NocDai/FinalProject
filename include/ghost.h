#ifndef GHOST_H
#define GHOST_H

#include "map.h"
#include "coordinate.h"
#include "player.h"
#include <iostream>
class Ghost:public Coordinate{
    public:
        Ghost(Coordinate, Map&);
        void walk(Player&, Map&);
    private:
        OBJ sight[3][3];
        void look_around(Map&);
        char find_path();
        void kill(Player&);
};

#endif