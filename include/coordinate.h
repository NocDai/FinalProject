#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
using namespace std;
class Coordinate{
    public:
        Coordinate(int xpos, int ypos):x(xpos),y(ypos){}
        ~Coordinate(){}
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
        void show(){
            cout<<x<<','<<y<<endl;
        }
    protected:
        int x;
        int y;
};

#endif