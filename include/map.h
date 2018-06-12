#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include "coordinate.h"
using namespace std;
enum OBJ {Non,Wall,player,Ghost,Key,Spot};
class Map{
    public:
        Map(ifstream &file);
        ~Map();
        void printMap();
        void setPlace(int x, int y, OBJ obj);
    protected:
        int dim;
        OBJ **place;
};

#endif