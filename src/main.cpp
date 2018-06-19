#include <iostream>
#include <fstream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <curses.h>
#include "map.h"
#include "player.h"
#include "keyandpass.h"
#include "controller.h"
//#include "coordinate.h"
using namespace std;

int main(int argc, char *argv[]){
    ifstream infile(argv[1]);
    Map map(infile);
    map.printMap();
    
    cout<<"Please choose the mode."<<endl
        <<"input 1 for manual."<<endl
        <<"input 2 for auto."<<endl;
    int mode;
    cin >>mode;
    Player P(map.GetFreeplace(), map, mode);
    Key K(map.GetFreeplace(), map);
    PassSpot PS(map.GetFreeplace(), map);
    map.printMap();
    char command = '\0';
    bool Over = false;
    while(!Over){
        Over = Update(P, K, PS, map);
        command='\0';
        if(kbhit())
            command = getchar();
        
        P.walk(command, map);
        system("clear");
        map.printMap();
        delay();
    }
    
    return 0;
}