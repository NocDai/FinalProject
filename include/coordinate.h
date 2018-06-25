#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
//#include "map.h"
using namespace std;
class Coordinate{
    public:
	Coordinate()
	{
		x=y=-1;
	}
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
	bool operator==(const Coordinate& cor) const{
        if(this->x==cor.x&&this->y==cor.y)
            return true;
        return false;
	}
    protected:
        int x;
        int y;
};

#endif
