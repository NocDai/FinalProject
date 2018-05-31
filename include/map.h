#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
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
            for(int i=0; i<5; i++){
                for(int j=0; j<5; j++){
                    cout << place[i][j] << " ";
                }
                cout << endl;
            }
        }
    protected:
        int dim;
        char **place;
};

#endif