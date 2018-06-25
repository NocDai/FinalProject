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
    Map map(infile);
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
            G.show();
            delay();
        }
        //===========================================
        else if(mode==2){
		int maze[7][7]={
    		{1,1,1,1,1,1,1},
    		{1,0,1,1,1,0,1},
    		{1,0,0,1,0,0,1},
    		{1,0,1,0,0,0,1},
    		{1,0,0,0,1,1,1},
    		{1,1,0,0,0,0,1},
    		{1,1,1,1,1,1,1}
		};
		//int** omap=originalmap.getMap();	
		Coordinate SP(1,1);
		Coordinate KP(1,5);
		Coordinate EP(5,5);
        	mazePath(maze,7,7,SP,KP,keyPath);
                Over = Update(P, K, PS, map);   //BFS不能一直更新
                mazePath(maze,7,7,KP,EP,endPath);
		//Over = Update(P, K, PS, map);   //BFS不能一直更新
                cout<<"shortest path to key:";
                for(vector<Coordinate>::reverse_iterator i=keyPath.rbegin(); i!=keyPath.rend(); ++i){
                    printf("(%d,%d) ",i->getX(),i->getY());
                }
                cout << endl;
		//map.printMap();
		cout<<"shortest path from key to end:";
                for(vector<Coordinate>::reverse_iterator i=endPath.rbegin(); i!=endPath.rend(); ++i){
                    printf("(%d,%d) ",i->getX(),i->getY()); 
                }
		cout << endl;
		Over=true;
            	//Over = Update(P, K, PS, map);
	}
        
        //==================================================
    }
    
    return 0;
}
