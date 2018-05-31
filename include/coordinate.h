#ifndef COORDINATE_H
#define COORDINATE_H

class coordinate{
    public:
        coordinate(int xpos, int ypos):x(xpos),y(ypos){}
        ~coordinate(){}
    protected:
        int x;
        int y;
}

#endif