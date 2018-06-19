#ifndef KEYANDPASS_H
#define KEYANDPASS_H

#include "map.h"
#include "coordinate.h"

class PassSpot: public Coordinate{
    friend class Key;
    public:
        PassSpot(int, int, Map&);
        PassSpot(Coordinate, Map&);
        void appear(Map &);
        void setPlace();
    private:
        bool is_hidden;
};

class Key: public Coordinate{
    public:
        Key(int, int, Map&);
        Key(Coordinate, Map&);
        void taken(Map&, PassSpot&);
        void setPlace();
    private:
        bool is_taken;
};

#endif