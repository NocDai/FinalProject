#include <stdio.h>  
#include <termios.h>  
#include <unistd.h>  
#include <fcntl.h>  
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
int main(void)  
{  
  /*while(!kbhit())  
    puts("Press a key!");  
  printf("You pressed '%c'!/n", getchar());  
  */
  int a=0;
  while(1){
      if(kbhit()){
        int c=getchar();
        c-=48;
        a+=c;
        
      }
      for(int i=0;i<100000000;i++);
      printf("%d\n",a);
  }
  return 0;  
}