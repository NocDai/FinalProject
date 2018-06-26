#include "player.h"
#include <stdlib.h>
#include <cmath>
#include <ctime>
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
    last_command = com;
}

bool Player::set(Coordinate pre, Map& m){
    OBJ obj = m.collision(*this);
    if(obj == Non){
        m.setPlace(pre, Non);
        m.setPlace(*this , player);
        score[*this]= -1;
        return true;
    }
    else if(obj == Wall){
        return false;
    }
    else if(obj == key){
        m.setPlace(pre, Non);
        m.setPlace(*this , player);
        have_key = true;
        score.clear();
    }
    else if(obj == spot){
        m.setPlace(pre, Non);
        m.setPlace(*this , player);
        pass = true;
    }
    else if(obj == ghost){
        m.setPlace(pre,Non);
        isdead =true;
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
    
    Coordinate now_see[3][3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            now_see[i][j] = Coordinate(x-1+j, y-1+i);
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
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(m.collision(now_see[i][j])==key || m.collision(now_see[i][j])==spot){
                score[now_see[i][j]] += 10;
            }
            else if(m.collision(now_see[i][j])==ghost){
                score[now_see[i][j]] -= 1;
            }
            else if(m.collision(now_see[i][j])==Non){
                //score[now_see[i][j]] *= 0.00005;
            }
        }
    }
    float GAMMA = 0.00005;
    for(map<Coordinate,float>::iterator it = score.begin(); it!=score.end(); it++){
        //if(m.collision(it->first)!=Non)
            //it->second += 0.001;
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
    srand(time(NULL));
    if(policy[0]==0 && policy[1]==0 && policy[2]==0 && policy[3]==0){
        policy[0] = rand()%50;
        policy[1] = rand()%50;
        policy[2] = rand()%50;
        policy[3] = rand()%50;
    }
    
    if(m.aplace(x,y-1)==Wall)   policy[0]=-1000000;
    else if(m.aplace(x,y-1)==ghost) policy[0]= -1000000;
    if(m.aplace(x-1,y)==Wall)   policy[1]=-1000000;
    else if(m.aplace(x-1,y)==ghost) policy[1]= -1000000;
    if(m.aplace(x,y+1)==Wall)   policy[2]=-1000000;
    else if(m.aplace(x-1,y)==ghost) policy[2]= -1000000;
    if(m.aplace(x+1,y)==Wall)   policy[3]=-1000000;
    else if(m.aplace(x-1,y)==ghost) policy[3]= -1000000;
    for(int i=0;i<4;i++){
        if(policy[i]>policy[i+1]){
            policy[i+1]=policy[i];
            path[i+1] = path[i];
        }
        else if (policy[i]==policy[i+1]){
            int j= rand()%2;
            policy[i+1] = policy[i+j];
            path[i+1] = path[i+j];
        }
    }
    return path[3];
}