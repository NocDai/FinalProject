#include <iostream>
#include <fstream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <curses.h>
#include "map.h"
#include "player.h"
#include "ghost.h"
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
    Ghost G(map.GetFreeplace(),map);
    map.printMap();
    char command = '\0';
    bool Over = false;
    int g_speed=0;
    while(!Over){
        if(mode == 1){
            g_speed++;
            command='\0';
            if(kbhit())
                command = getchar();
            system("clear");
            P.walk(command, map);
            if(g_speed==10){
                g_speed =0;
                G.walk(P,map);
            }
            //system("clear");
            map.printMap();
            Over = Update(P, K, PS, map);
            G.show();
            delay();
        }
        else if(mode==2){
            
        }
    }
    
    return 0;
}