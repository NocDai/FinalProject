#include "keyandpass.h"

Key::Key(int x, int y, Map& m):Coordinate(x,y){
    m.setPlace(*this , key);
    is_taken = false;
}

Key::Key(Coordinate coord, Map& m):Coordinate(coord){
    m.setPlace(*this , key);
    is_taken = false;
}

void Key::taken(Map& m, PassSpot& ps){
    m.setPlace(*this, Non);
    ps.appear(m);
    ps.is_hidden = false;
}

PassSpot::PassSpot(int x, int y, Map& m):Coordinate(x,y){
    is_hidden = true;
}

PassSpot::PassSpot(Coordinate coord, Map& m):Coordinate(coord){
    is_hidden = true;
}

void PassSpot::appear(Map& m){
    if(is_hidden==true){
        Coordinate c = m.GetFreeplace();
        x =c.getX();
        y =c.getY();
        m.setPlace(*this, spot);
    }
}
