#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;
#define m 23//row+2 = dim
#define n 23//column
#define down 1
#define right 2
#define left 4
#define up 8
vector <int> block_row;
vector <int> block_column;
vector <int> block_direct;
typedef struct point
{
    int x;
    int y;
}Point;
Point start,end;
int x_num=1;
int y_num=1;
int a[m+2][n+2];
void init(){//将地图全部置1=wall
    for(int i=0;i<=m+1;i++){
        for(int j=0;j<=n+1;j++){
            a[i][j]=1;//wall
        }
    }
}
void push(int x,int y,int direct){//把一组数据存放进三个vector容器中
    block_row.push_back(x);
    block_column.push_back(y);
    block_direct.push_back(direct);
}
int count(){//计算当前位置周围 墙的个数
    int cnt=0;
    if(x_num+1<=m){
        push(x_num+1,y_num,down);
        cnt++;
    } //down
    if(y_num+1<=n){
        push(x_num,y_num+1,right);
        cnt++;
    } //right
    if(x_num-1>=1){
        push(x_num-1,y_num,up);
        cnt++;
    } //up
    if(y_num-1>=1){
        push(x_num,y_num-1,left);
        cnt++;
    } //left
    return cnt;
}
int** gen_map(){
    //int **ret;
    int dim=m+2;
    int **ret;
    ret = new int *[dim];
            for (int i = 0; i < dim; i++)
                ret[i] = new int [dim];
    start.x=1;//定义起始点
    start.y=1;
    end.x=m;
    end.y=n;
    init();
    srand((unsigned)time(NULL));//随机数种子
    count();
    a[1][1]=2;
    while(block_row.size()){//第一步压入两堵墙（起点右边和起点下面）进入循环
        int num=block_row.size();
        int randnum=rand()%num;//生成0-num-1之间的随机数，同时也是vector里的下标
        x_num=block_row[randnum];//下面这两行可以不写
        y_num=block_column[randnum];
        switch(block_direct[randnum]){//选择一个方向进行后续操作，起始点 邻块 目标块 三块区域在同一直线上 随后移动到目标块的位置
            case down:{
                x_num=block_row[randnum]+1;
                y_num=block_column[randnum];
                break;
            }
            case right:{
                x_num=block_row[randnum];
                y_num=block_column[randnum]+1;
                break;  
            }
            case left:{
                x_num=block_row[randnum];
                y_num=block_column[randnum]-1;
                break;
            }
            case up:{
                x_num=block_row[randnum]-1;
                y_num=block_column[randnum];
                break;
            }
        }
        if(a[x_num][y_num]==1){//目标块如果是墙
            a[block_row[randnum]][block_column[randnum]]=2;//打通墙
            a[x_num][y_num]=2;//打通目标块
            count();//再次计算当前位置周围的邻墙个数并保存进vector
        }           
        block_row.erase(block_row.begin()+randnum);//删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
        block_column.erase(block_column.begin()+randnum);
        block_direct.erase(block_direct.begin()+randnum);
    }
    for(int i=0;i<=m+1;i++){
        for(int j=0;j<=n+1;j++){
            if(a[i][j]==2){
                //printf("0 ");
                ret[i][j]=0;
            }
            else{
                //printf("1 ");
                ret[i][j]=1;
            }
        }
        //printf("\n");
    }
    /*
    for(int i=0;i<=m+1;i++){
        for(int j=0;j<=n+1;j++){
            cout << ret[i][j] << " ";
        }
        printf("\n");
    }
    */
    return ret;
}


int main(){
    ofstream out_file("level4.txt");
    int **mat;
    mat = gen_map();
    for(int i=0;i<=m+1;i++){
        for(int j=0;j<=n+1;j++){
            cout << mat[i][j] << " ";
            out_file << mat[i][j] << " ";
        }
        printf("\n");
        out_file << endl;
    }
    
    out_file.close();
    return 0;
}