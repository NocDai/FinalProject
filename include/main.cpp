#include <iostream>
#include <fstream>
#include "map.h"
#include "player.h"
//#include "coordinate.h"
using namespace std;

int main(int argc, char *argv[]){
    ifstream infile(argv[1]);
    map Map(infile);
    Player P(0, 0, Map);
    Map.printMap();
    
    return 0;
}