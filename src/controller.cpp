#include <stdio.h>  
#include <termios.h>  
#include <unistd.h>  
#include <fcntl.h>

#include "controller.h"

bool over = false;
bool win = false;
int kbhit(void)  
{  
    struct termios oldt, newt;  
    int ch;  
    int oldf;  
    tcgetattr(STDIN_FILENO, &oldt);  
    newt = oldt;  
    newt.c_lflag &= ~(ICANON | ECHO);  
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);  
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);  
    ch = getchar();  
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
    fcntl(STDIN_FILENO, F_SETFL, oldf);  
    if(ch != EOF)  
    {  
        ungetc(ch, stdin);  
        return 1;  
    }  
    return 0;  
}

void delay(void){
    for(int i=0;i<50000000;i++);
}

bool Update(Player& p, Key& k, PassSpot& ps, Map& m){
    if(p.pass_check()){
        over = true;
        printf("You Win\r\n");
        return over;
    }
    if(p.dead_check()){
        printf("FAIL\r\n");
        over = true;
    }
    if(p.key_check()){
        k.taken(m, ps);
        printf("You have key now!!!\r\n");
    }
    
    return over;
}