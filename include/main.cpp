#include <iostream>
#include <fstream>
#include <stdio.h>
#include <curses.h>
#include "map.h"
#include "player.h"
//#include "coordinate.h"
using namespace std;

int main(int argc, char *argv[]){
    ifstream infile(argv[1]);
    map Map(infile);
    Player P(0, 0, Map);
    //Map.printMap();
    WINDOW *w=initscr();
    while(1){
        char c;
        c = getch();
        if(c=='w')      cout<<'^'<<endl;
        else if(c=='a') cout<<'<'<<endl;
        else if(c=='s') cout<<'v'<<endl;
        else if(c=='d') cout<<'>'<<endl;
        Map.printMap();
    }
    endwin();
    cout<<"flag."<<endl;
    
    return 0;
}