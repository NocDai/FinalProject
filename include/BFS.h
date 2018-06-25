#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>
using namespace std;

struct Point{  
    //行与列
    int row;  
    int col;  

    //默认构造函数
    Point(){
        row=col=-1;
    }

    Point(int x,int y){
        this->row=x;
        this->col=y;
    }

    bool operator==(const Point& rhs) const{
        if(this->row==rhs.row&&this->col==rhs.col)
            return true;
        return false;
    }
};

int maze[7][7]={
    {1,1,1,1,1,1,1},
    {1,0,1,1,1,0,1},
    {1,0,0,1,0,0,1},
    {1,0,1,0,0,0,1},
    {1,0,0,0,1,1,1},
    {1,1,0,0,0,0,1},
    {1,1,1,1,1,1,1}
};

//find
void mazePath(void* maze,int m,int n, Point& startP, Point endP,vector<Point>& shortestPath){
    int** maze2d=new int*[m];
    for(int i=0;i<m;i++){
        maze2d[i]=(int*)maze+i*n;
    }

    if(maze2d[startP.row][startP.col]==1||maze2d[startP.row][startP.col]==1) return ; //输入错误

    if(startP==endP){ //起点即终点
        shortestPath.push_back(startP);
        return;
    }

    //mark标记每一个节点的前驱节点，如果没有则为（-1，-1），如果有，则表示已经被访问
    Point** mark=new Point*[m];
    for(int i=0;i<m;i++){
        mark[i]=new Point[n];
    }

    queue<Point> queuePoint;
    queuePoint.push(startP);
    //将起点的前驱节点设置为自己
    mark[startP.row][startP.col]=startP;

    while(queuePoint.empty()==false){
        Point pointFront=queuePoint.front();    //現在位置
        queuePoint.pop();

        
        if(pointFront.row-1>=0 && maze2d[pointFront.row-1][pointFront.col]==0){//上节点连通
            if(mark[pointFront.row-1][pointFront.col]==Point()){//上节点未被访问，满足条件，如队列
                mark[pointFront.row-1][pointFront.col]=pointFront;  //標記已走過此處
                queuePoint.push(Point(pointFront.row-1,pointFront.col)); //入栈
                if(Point(pointFront.row-1,pointFront.col)==endP){ //找到终点
                    break;
                }
            }
        }

        if(pointFront.col+1<n && maze2d[pointFront.row][pointFront.col+1]==0){//右节点连通
            if(mark[pointFront.row][pointFront.col+1]==Point()){//右节点未被访问，满足条件，如队列
                mark[pointFront.row][pointFront.col+1]=pointFront;
                queuePoint.push(Point(pointFront.row,pointFront.col+1));    //入栈
                if(Point(pointFront.row,pointFront.col+1)==endP){ //找到终点
                    break;
                }
            }
        }

        if(pointFront.row+1<m && maze2d[pointFront.row+1][pointFront.col]==0){//下节点连通
            if(mark[pointFront.row+1][pointFront.col]==Point()){//下节点未被访问，满足条件，如队列
                mark[pointFront.row+1][pointFront.col]=pointFront;
                queuePoint.push(Point(pointFront.row+1,pointFront.col));    //入栈
                if(Point(pointFront.row+1,pointFront.col)==endP){ //找到终点
                    break;
                }
            }
        }

        if(pointFront.col-1>=0 && maze2d[pointFront.row][pointFront.col-1]==0){//左节点连通
            if(mark[pointFront.row][pointFront.col-1]==Point()){//上节点未被访问，满足条件，如队列
                mark[pointFront.row][pointFront.col-1]=pointFront;
                queuePoint.push(Point(pointFront.row,pointFront.col-1));    //入栈
                if(Point(pointFront.row,pointFront.col-1)==endP){ //找到终点
                    break;
                }
            }
        }
    }
    //
    if(queuePoint.empty()==false){
        int row=endP.row;
        int col=endP.col;
        shortestPath.push_back(endP);   //倒推, 放入shortestPath裡面
        while(!(mark[row][col]==startP)){
            shortestPath.push_back(mark[row][col]);
            int trow=mark[row][col].row;
            int tcol=mark[row][col].col;
            row =  trow;
            col = tcol;
        }
        shortestPath.push_back(startP);
    }
}
