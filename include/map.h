#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "coordinate.h"
using namespace std;
enum OBJ {Non,Wall,player,ghost,key,spot};
class Map{
    public:
        Map(ifstream &file);
        ~Map();
        void printMap();
        bool setPlace(Coordinate, OBJ);
        bool isfree(Coordinate);
        OBJ collision(Coordinate);
        Coordinate GetFreeplace();
    protected:
        int dim;
        OBJ **place;
};

#endif