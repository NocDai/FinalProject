#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include "coordinate.h"
using namespace std;
enum OBJ {Non,Wall,player,Ghost,Key,Spot};
class map{
    public:
        map(ifstream &file):dim(5){
            place = new OBJ *[dim];
            for (int i = 0; i < dim; i++)
                place[i] = new OBJ [dim];
                
            int next;
            for(int i=0; i<5; i++){
                for(int j=0; j<5; j++){
                    file >> next;
                    place[i][j] = (OBJ)next;
                }
            }
        }
        ~map(){
            for(int i=0; i<dim; i++)
                delete []place[i];
            delete []place;
            place = NULL;
        }
        void printMap(){
            cout << "\r\n";
            for(int i=0; i<5; i++){
                for(int j=0; j<5; j++){
                    if(place[i][j]==0)  cout<<' ';
                    else if(place[i][j]==1) cout<<"■";
                    else if(place[i][j]==2) cout<<'P';
                    else if(place[i][j]==3) cout<<'G';
                    else if(place[i][j]==4) cout<<'K';
                    else if(place[i][j]==5) cout<<"●";
                    cout << " ";
                }
                cout << "\r\n";
            }
        }
        void setPlace(int x, int y, OBJ obj){
            place[x][y] = obj;
        }
    protected:
        int dim;
        OBJ **place;
};

#endif