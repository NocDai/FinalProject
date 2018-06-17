#ifndef KEYANDPASS_H
#define KEYANDPASS_H

#include "map.h"
#include "coordinate.h"

class PassSpot: private Coordinate{
    friend class Key;
    public:
        PassSpot(int, int, Map&);
        PassSpot(Coordinate, Map&);
        void appear(Map &);
    private:
        bool is_hidden;
};

class Key:private Coordinate{
    public:
        Key(int, int, Map&);
        Key(Coordinate, Map&);
        void taken(Map&, PassSpot&);
    private:
        bool is_taken;
};

#endif