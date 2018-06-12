#include "map.h"

Map:: Map(ifstream &file):dim(5){
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

Map::~Map(){
    for(int i=0; i<dim; i++)
        delete []place[i];
    delete []place;
    place = NULL;
}

void Map::printMap(){
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

void Map::setPlace(int x, int y, OBJ obj){
    place[y][x] = obj;
}
