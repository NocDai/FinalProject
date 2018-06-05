#ifndef COORDINATE_H
#define COORDINATE_H

class coordinate{
    public:
        coordinate(int xpos, int ypos):x(xpos),y(ypos){}
        ~coordinate(){}
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
    protected:
        int x;
        int y;
};

#endif