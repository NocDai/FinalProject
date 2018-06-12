#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "map.h"
#include "player.h"
#include "controller.h"
//#include "coordinate.h"
using namespace std;

int main(int argc, char *argv[]){
    ifstream infile(argv[1]);
    map Map(infile);
    Player P(0, 0, Map);
    Map.printMap();
    while(1){
        if(kbhit()){
            if(getchar()=='w'){
                Map.setPlace(0,0,Non);
            }
        }
        Map.printMap();
        delay();
        system("clear");
    }
    cout<<"flag."<<endl;
    
    return 0;
}