#include <iostream>
#include <fstream>
#include "map.h"
//#include "coordinate.h"
using namespace std;

int main(int argc, char *argv[]){
    ifstream infile(argv[1]);
    map Map(infile);
    Map.printMap();
    
    return 0;
}