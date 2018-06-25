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
    int calc_flag=0;
    vector<Point> keyPath;
    vector<Point> endPath;
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
            /*
                g_speed++;
            //get_command from父子節點
            
            
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
            //Over = Update(P, K, PS, map);
            Over = true;
        }*/
        //==================================================
    }
    
    return 0;
}