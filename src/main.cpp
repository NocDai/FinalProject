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
    int dim=15,level=0;
    cout << argv[1] << endl;
    
    /*
    if(argv[1]=="./include/map.txt"){
        dim=7;
    }
    else if(argv[1]=="./include/level3.txt"){
        dim = 16;
    }*/
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
            G.show();
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
            G.show();
            delay();
        }
        //===========================================
        else if(mode==3){
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
        }
        /*else if(mode==2){
            if(calc_flag==0){
                int maze[7][7]={
                    {1,1,1,1,1,1,1},
                    {1,0,1,1,1,0,1},
                    {1,0,0,1,0,0,1},
                    {1,0,1,0,0,0,1},
                    {1,0,0,0,1,1,1},
                    {1,1,0,0,0,0,1},
                    {1,1,1,1,1,1,1}
                    };
                
                Point startP(1,1);  //start coordinate, 先假設拿到
                Point keyP(1,5);    //key coordinate
                
                mazePath(maze,7,7,startP,keyP,keyPath);
                
                
                //Over = Update(P, K, PS, map);   //BFS不能一直更新
                Point endP(5,5);   //end coordinate
                
                mazePath(maze,7,7,keyP,endP,endPath);
                
                calc_flag++;
                
            }
            if(calc_flag==1){
                if(keyPath.empty()==true)
                    cout<<"no right path"<<endl;
                else{
                    cout<<"shortest path to key:";

                    for(vector<Point>::reverse_iterator i=keyPath.rbegin(); i!=keyPath.rend(); ++i){
                        printf("(%d,%d) ",i->row,i->col);   
            
                    }
                }
                cout << endl;
                if(endPath.empty()==true)
                    cout<<"no right path"<<endl;
                else{
                    cout<<"shortest path from key to end:";
                    for(vector<Point>::reverse_iterator i=endPath.rbegin(); i!=endPath.rend(); ++i){
                        printf("(%d,%d) ",i->row,i->col);  
            
                    }
                }
                cout << endl;
		//map.printMap();
		cout<<"shortest path from key to end:";
                for(vector<Coordinate>::reverse_iterator i=endPath.rbegin(); i!=endPath.rend(); ++i){
                    printf("(%d,%d) ",i->getX(),i->getY()); 
                }
	}
        
                //system("clear");
                map.printMap();
                Over = Update(P, K, PS, map);
                G.show();
                delay();
            
            }
            //Over = Update(P, K, PS, map);
            Over = true;
        }*/
        //==================================================
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
