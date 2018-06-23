#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
//=======================
#include <vector>
//=======================
//#include "map.h"
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

//================================
struct Point{  
    //行与列
    int row;  
    int col;  

    //默认构造函数
    Point(){
        row=col=-1;
    }

    Point(int x,int y){
        this->row=x;
        this->col=y;
    }

    bool operator==(const Point& rhs) const{
        if(this->row==rhs.row&&this->col==rhs.col)
            return true;
        return false;
    }
};

void mazePath(void* ,int ,int , Point& , Point ,vector<Point>& );
//==================================

#endif