#include <iostream>
#include <fstream>
//=========================
//#include <queue>
//#include <vector>
//#include <stdio.h>
#include "BFS.h"
//=========================
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
    int dim=17;
    cout << dim << endl;
    Map map(infile,dim);
    //Map originalmap=map;
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
    //=====================
    vector<Coordinate> keyPath;
    vector<Coordinate> endPath;
    //=====================
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
            delay();
        }
        if(mode == 2){
            g_speed++;
            system("clear");
            P.walk(map);
            if(g_speed==10){
                g_speed =0;
                G.walk(P,map);
                //P.walk(map);
            }
            //system("clear");
            map.printMap();
            Over = Update(P, K, PS, map);
            delay();
        }
    }
    if(P.pass_check()==1){
    ifstream infile2(argv[2]);
    dim=25;
    Map map2(infile2,dim);
    map2.printMap();
    cout<<"Please choose the mode."<<endl
        <<"input 1 for manual."<<endl
        <<"input 2 for auto."<<endl;
    int mode2;
    cin >>mode2;
    Player P2(map2.GetFreeplace(), map2, mode2);
    Key K2(map2.GetFreeplace(), map2);
    PassSpot PS2(map2.GetFreeplace(), map2);
    Ghost G2(map2.GetFreeplace(),map2);
    map2.printMap();
    char command2 = '\0';
    Over = false;
    g_speed=0;
    while(!Over){
        if(mode2 == 1){
            g_speed++;
            command2='\0';
            if(kbhit())
                command2 = getchar();
            system("clear");
            P2.walk(command2, map2);
            if(g_speed==10){
                g_speed =0;
                G2.walk(P2,map2);
            }
            //system("clear");
            map2.printMap();
            Over = Update(P2, K2, PS2, map2);
            G2.show();
            delay();
        }
        else if(mode2 == 2){
            g_speed++;
            system("clear");
            P2.walk(map2);
            if(g_speed==10){
                g_speed =0;
                G2.walk(P2,map2);
                //P.walk(map);
            }
            //system("clear");
            map2.printMap();
            Over = Update(P2, K2, PS2, map2);
            G2.show();
            delay();
        }
    }
    }
    
    if(P.pass_check()==1){
    ifstream infile2(argv[2]);
    dim=25;
    Map map2(infile2,dim);
    map2.printMap();
    cout<<"Please choose the mode."<<endl
        <<"input 1 for manual."<<endl
        <<"input 2 for auto."<<endl;
    int mode2;
    cin >>mode2;
    Player P2(map2.GetFreeplace(), map2, mode2);
    Key K2(map2.GetFreeplace(), map2);
    PassSpot PS2(map2.GetFreeplace(), map2);
    Ghost G2(map2.GetFreeplace(),map2);
    map2.printMap();
    char command2 = '\0';
    Over = false;
    g_speed=0;
    while(!Over){
        if(mode2 == 1){
            g_speed++;
            command2='\0';
            if(kbhit())
                command2 = getchar();
            system("clear");
            P2.walk(command2, map2);
            if(g_speed==10){
                g_speed =0;
                G2.walk(P2,map2);
            }
            //system("clear");
            map2.printMap();
            Over = Update(P2, K2, PS2, map2);
            G2.show();
            delay();
        }
        else if(mode2 == 2){
            g_speed++;
            system("clear");
            P2.walk(map2);
            if(g_speed==10){
                g_speed =0;
                G2.walk(P2,map2);
                //P.walk(map);
            }
            //system("clear");
            map2.printMap();
            Over = Update(P2, K2, PS2, map2);
            G2.show();
            delay();
        }
    }
    }
    
    return 0;
}
