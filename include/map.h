#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include "coordinate.h"
using namespace std;

class map{
    public:
        map(ifstream &file):dim(5){
            place = new char *[dim];
            for (int i = 0; i < dim; i++)
                place[i] = new char [dim];
                
            char next;
            for(int i=0; i<5; i++){
                for(int j=0; j<5; j++){
                    file >> next;
                    place[i][j] = next;
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
                    cout << place[i][j] << " ";
                }
                cout << "\r\n";
            }
        }
        void setPlace(int x, int y, char obj){
            place[x][y] = obj;
        }
    protected:
        int dim;
        char **place;
};

#endif