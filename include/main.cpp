#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "map.h"
#include "player.h"
//#include "coordinate.h"
using namespace std;

int main(int argc, char *argv[]){
    ifstream infile(argv[1]);
    map Map(infile);
    Player P(0, 0, Map);
    WINDOW *w=initscr();
    char c;
    while(1){
        while((c = getch())!='w')   cout<<"flag.";
        if(c=='w')      cout<<'^'<<endl;
        else if(c=='a') cout<<'<'<<endl;
        else if(c=='s') cout<<'v'<<endl;
        else if(c=='d') cout<<'>'<<endl;
        //system("clear");
        Map.printMap();
    }
    endwin();
    cout<<"flag."<<endl;
    
    return 0;
}