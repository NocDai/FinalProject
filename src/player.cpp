#include "player.h"
#include <stdlib.h>
Player::Player(int x, int y, Map& m, int _mode)
        :Coordinate(x, y)
{
    this->set(*this, m);
    mode = _mode;
    isdead = false;
    have_key = false;
}

Player::Player(Coordinate coord, Map& m, int _mode)
        :Coordinate(coord)
{
    m.setPlace(*this , player);
    mode = _mode;
    isdead = false;
    have_key = false;
    pass = false;
}

void Player::walk(char com, Map& m){
    int pre_x = x;
    int pre_y = y;
    if(com == 's')  y++;
    else if(com == 'a') x--;
    else if(com == 'w') y--;
    else if(com == 'd') x++;
    if(x>m.getDim()-1) x=m.getDim()-1;
    else if (x<0)   x=0;
    if(y>m.getDim()-1) y=m.getDim()-1;
    else if (y<0)   y=0;
    if(! (set(Coordinate(pre_x, pre_y), m))){
        x = pre_x;
        y = pre_y;
    }
}

void Player::walk(Map& m){
    int pre_x = x;
    int pre_y = y;
    char com = find_path(m);
    cout<<com<<endl;
    if(com == 's')  y++;
    else if(com == 'a') x--;
    else if(com == 'w') y--;
    else if(com == 'd') x++;
    if(x>m.getDim()-1) x=m.getDim()-1;
    else if (x<0)   x=0;
    if(y>m.getDim()-1) y=m.getDim()-1;
    else if (y<0)   y=0;
    if(! (set(Coordinate(pre_x, pre_y), m))){
        x = pre_x;
        y = pre_y;
    }
}

bool Player::set(Coordinate pre, Map& m){
    OBJ obj = m.collision(*this);
    if(obj == Non){
        m.setPlace(pre, Non);
        m.setPlace(*this , player);
        return true;
    }
    else if(obj == Wall){
        return false;
    }
    else if(obj == key){
        m.setPlace(pre, Non);
        m.setPlace(*this , player);
        have_key = true;
    }
    else if(obj == spot){
        m.setPlace(pre, Non);
        m.setPlace(*this , player);
        pass = true;
    }
    else if(obj == ghost){
        m.setPlace(pre,Non);
        //isdead =true;
    }
    return true;
}

bool Player::dead_check(){
    return isdead;
}

bool Player::key_check(){
    return have_key;
}

bool Player::pass_check(){
    return pass;
}

void Player::be_killed(){
    isdead = true;
}

void Player::look_around(Map& m){
    int x = getX();
    int y = getY();
    for(int i=0; i<3; i++){
        for(int j=0; j<3 ;j++){
            sight[i][j] = m.aplace(x-1+j, y-1+i);
            if(sight[i][j]==2){
                sight[i][j] = 0;
            }
        }
    }
}

void Player::remember(Map &m){
    look_around(m);
    
    Coordinate now_see[5][5];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            now_see[i][j] = Coordinate(x-1+j, y-1+i);
            if(m.collision(now_see[i][j])==key || m.collision(now_see[i][j])==spot){
                score[now_see[i][j]] += 10;
            }
            if(m.collision(now_see[i][j])==ghost){
                score[now_see[i][j]] -= 1;
            }
        }
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            mapping[now_see[i][j]] = sight[i][j];
            if(sight[i][j]==0)
                score.insert(pair<Coordinate,float>(now_see[i][j],10));
            else if(sight[i][j]==1)
                score.insert(pair<Coordinate,float>(now_see[i][j],0));
            else if(sight[i][j]==3)
                score.insert(pair<Coordinate,float>(now_see[i][j],0));
            else if(sight[i][j]==4)
                score.insert(pair<Coordinate,float>(now_see[i][j],100));
            else if(sight[i][j]==5)
                score.insert(pair<Coordinate,float>(now_see[i][j],100));
        }
    }
    float GAMMA = 0.00005;
    for(map<Coordinate,float>::iterator it = score.begin(); it!=score.end(); it++){
        it->second *= GAMMA;
    }
    
}

char Player::find_path(Map &m){
    remember(m);
    float policy[4]={0};
    map<Coordinate,float>::iterator it;
    for(it=score.begin(); it!=score.end(); it++){
        if((it->first).getX() > x && (it->first).getY() < y){
            policy[0] += it->second;
            policy[3] += it->second;
        }
        else if((it->first).getX() == x && (it->first).getY() < y)
            policy[0] += it->second; 
        else if((it->first).getX() < x && (it->first).getY() < y){
            policy[0] += it->second;
            policy[1] += it->second;
        }
        else if((it->first).getX() < x && (it->first).getY() == y)
            policy[1] += it->second;
        else if((it->first).getX() < x && (it->first).getY() > y){
            policy[1] += it->second;
            policy[2] += it->second;
        }
        else if((it->first).getX() == x && (it->first).getY() > y)
            policy[2] += it->second;
        else if((it->first).getX() > x && (it->first).getY() > y){
            policy[2] += it->second;
            policy[3] += it->second;
        }
        else if((it->first).getX() > x && (it->first).getY() == y)
            policy[3] += it->second;
    }
    cout<<policy[0]<<' '<<policy[1]<<' '<<policy[2]<<' '<<policy[3]<<endl;
    char path[4]= {'w', 'a', 's', 'd'};
    
    if(policy[0]==0 && policy[1]==0 && policy[2]==0 && policy[3]==0){
        int i = rand()%4;
        return path[i];
    }
    
    if(m.aplace(x,y-1)==Wall)   policy[0]=-1;
    else if(m.aplace(x,y-1)==ghost) policy[0]= -1;
    if(m.aplace(x-1,y)==Wall)   policy[1]=-1;
    else if(m.aplace(x-1,y)==ghost) policy[1]= -1;
    if(m.aplace(x,y+1)==Wall)   policy[2]=-1;
    else if(m.aplace(x-1,y)==ghost) policy[2]= -1;
    if(m.aplace(x+1,y)==Wall)   policy[3]=-1;
    else if(m.aplace(x-1,y)==ghost) policy[3]= -1;
    for(int i=0;i<4;i++){
        if(policy[i]>policy[i+1]){
            policy[i+1]=policy[i];
            path[i+1] = path[i];
        }
    }
    return path[3];
}
/*
void find_path(Point endP,vector<Point>& shortestPath){
    //maze -> mapping
    //m,n -> mapping size
    //startP -> *this
    //endP ->
    //vector<Point> shortestPath -> Path
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
*/