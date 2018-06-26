#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>
#include"coordinate.h"
using namespace std;
int maze[7][7]={
    {1,1,1,1,1,1,1},
    {1,0,1,1,1,0,1},
    {1,0,0,1,0,0,1},
    {1,0,1,0,0,0,1},
    {1,0,0,0,1,1,1},
    {1,1,0,0,0,0,1},
    {1,1,1,1,1,1,1}
};

void mazePath(void* maze,int m,int n,Coordinate& startP, Coordinate endP,vector<Coordinate>& shortestPath){
    int** maze2d=new int*[m];
    for(int i=0;i<m;i++){
        maze2d[i]=(int*)maze+i*n;
    }

    if(maze2d[startP.getX()][startP.getY()]==1||maze2d[startP.getX()][startP.getY()]==1) return ; //输入错误

    if(startP==endP){ //起点即终点
        shortestPath.push_back(startP);
        return;
    }

    //mark标记每一个节点的前驱节点，如果没有则为（-1，-1），如果有，则表示已经被访问
    Coordinate** mark=new Coordinate*[m];
    for(int i=0;i<m;i++){
        mark[i]=new Coordinate[n];
    }

    queue<Coordinate> queueCoordinate;
    queueCoordinate.push(startP);
    //将起点的前驱节点设置为自己
    mark[startP.getX()][startP.getY()]=startP;

    while(queueCoordinate.empty()==false){
        Coordinate CoordinateFront=queueCoordinate.front();    //現在位置
        queueCoordinate.pop();

        
        if(CoordinateFront.getX()-1>=0 && maze2d[CoordinateFront.getX()-1][CoordinateFront.getY()]==0){//上节点连通
            if(mark[CoordinateFront.getX()-1][CoordinateFront.getY()]==Coordinate()){//上节点未被访问，满足条件，如队列
                mark[CoordinateFront.getX()-1][CoordinateFront.getY()]=CoordinateFront;  //標記已走過此處
                queueCoordinate.push(Coordinate(CoordinateFront.getX()-1,CoordinateFront.getY())); //入栈
                if(Coordinate(CoordinateFront.getX()-1,CoordinateFront.getY())==endP){ //找到终点
                    break;
                }
            }
        }

        if(CoordinateFront.getY()+1<n && maze2d[CoordinateFront.getX()][CoordinateFront.getY()+1]==0){//右节点连通
            if(mark[CoordinateFront.getX()][CoordinateFront.getY()+1]==Coordinate()){//右节点未被访问，满足条件，如队列
                mark[CoordinateFront.getX()][CoordinateFront.getY()+1]=CoordinateFront;
                queueCoordinate.push(Coordinate(CoordinateFront.getX(),CoordinateFront.getY()+1));    //入栈
                if(Coordinate(CoordinateFront.getX(),CoordinateFront.getY()+1)==endP){ //找到终点
                    break;
                }
            }
        }

	if(CoordinateFront.getX()+1<m && maze2d[CoordinateFront.getX()+1][CoordinateFront.getY()]==0){//下节点连通
            if(mark[CoordinateFront.getX()+1][CoordinateFront.getY()]==Coordinate()){//下节点未被访问，满足条件，如队列
                mark[CoordinateFront.getX()+1][CoordinateFront.getY()]=CoordinateFront;
                queueCoordinate.push(Coordinate(CoordinateFront.getX()+1,CoordinateFront.getY()));    //入栈
                if(Coordinate(CoordinateFront.getX()+1,CoordinateFront.getY())==endP){ //找到终点
                    break;
                }
            }
        }	

        if(CoordinateFront.getY()-1>=0 && maze2d[CoordinateFront.getX()][CoordinateFront.getY()-1]==0){//左节点连通
            if(mark[CoordinateFront.getX()][CoordinateFront.getY()-1]==Coordinate()){//上节点未被访问，满足条件，如队列
                mark[CoordinateFront.getX()][CoordinateFront.getY()-1]=CoordinateFront;
                queueCoordinate.push(Coordinate(CoordinateFront.getX(),CoordinateFront.getY()-1));    //入栈
                if(Coordinate(CoordinateFront.getX(),CoordinateFront.getY()-1)==endP){ //找到终点
                    break;
                }
            }
        }
    }
    //
    if(queueCoordinate.empty()==false){
        int x=endP.getX();
        int y=endP.getY();
        shortestPath.push_back(endP);   //倒推, 放入shortestPath裡面
        while(!(mark[x][y]==startP)){
            shortestPath.push_back(mark[x][y]);
            int tx=mark[x][y].getX();
            int ty=mark[x][y].getY();
            x = tx;
            y = ty;
        }
        shortestPath.push_back(startP);
    }
}
