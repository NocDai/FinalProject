#include "ghost.h"

Ghost::Ghost(Coordinate coord, Map& m) :Coordinate(coord)
{
    m.setPlace(*this, ghost);
}

void Ghost::look_around(Map& m){
    int x = getX();
    int y = getY();
    for(int i=0; i<3; i++){
        for(int j=0; j<3 ;j++){
            sight[i][j] = m.aplace(x-1+j, y-1+i);
            std::cout<<sight[i][j]<<' ';
        }
        std::cout<<"\r\n";
    }
}

char Ghost::find_path(){
    int policy[3][3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(sight[i][j]== player){
                policy[i][j] = 5;
            }
            else if(sight[i][j]==Wall){
                policy[i][j] = 0; 
            }
            else
                policy[i][j] = 1;
            
            std::cout<<policy[i][j]<<' ';
        }
        std::cout<<"\r\n";
    }
    
    if(policy[0][1]!=0){
        policy[0][1] = policy[0][0]+ 2*policy[0][1]+ policy[0][2];
    }
    if(policy[1][0]!=0){
        policy[1][0] = policy[0][0]+ 2*policy[1][0]+ policy[2][0];
    }
    if(policy[1][2]!=0){
        policy[1][2] = policy[0][2]+ 2*policy[1][2]+ policy[2][2];
    }
    if(policy[2][1]!=0){
        policy[2][1] = policy[2][0]+ 2*policy[2][1]+ policy[2][2];
    }
    std::cout<<policy[0][1]<<policy[1][0]<<policy[1][2]<<policy[2][1]<<"\r\n";
    int p_path[4] = {policy[0][1], policy[1][0], policy[1][2], policy[2][1]};
    char path[4]= {'w', 'a', 'd', 's'};
    for(int i=0;i<4;i++){
        if(p_path[i]>p_path[i+1]){
            p_path[i+1]=p_path[i];
            path[i+1] = path[i];
        }
    }
    //std::cout<<max_p<<std::endl;
    return path[3];
}

void Ghost::kill(Player& p){
    p.be_killed();
}

void Ghost::walk(Player& pl, Map& m){
    look_around(m);
    char p=find_path();
    std::cout<<p<<std::endl;
    int pre_x = x;
    int pre_y = y;
    if(p == 's')  y++;
    else if(p == 'a') x--;
    else if(p == 'w') y--;
    else if(p == 'd') x++;
    if(x>6) x=6;
    else if (x<0)   x=0;
    if(y>6) y=6;
    else if (y<0)   y=0;
    
    OBJ obj = m.collision(*this);
    if(obj == player){
        kill(pl);
        m.setPlace(Coordinate(pre_x,pre_y), Non);
        m.setPlace(Coordinate(x,y), ghost);
    }
    else if(obj == Wall){
        x = pre_x;
        y = pre_y;
    }
    else if(obj == Non){
        m.setPlace(Coordinate(pre_x,pre_y), Non);
        m.setPlace(Coordinate(x,y), ghost);
    }
    else{
        m.setPlace(Coordinate(pre_x,pre_y), Non);
    }
}