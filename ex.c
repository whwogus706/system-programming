/*2011097075_whwogus_makeboard_and_color*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 4

unsigned long score=0;
unsigned char scheme=0;


//make the color for board and number
void makecolor(unsigned char value, char *color, size_t length){
        unsigned char basic[] = {8,255,1,255,2,255,3,255,4,255,5,255,6,255,7,255,9,0,10,0,11,0,12,0,13,0,14,0,255,0,255,0};
        unsigned char * schemes[] = {basic};
        unsigned char * background = schemes[scheme]+0;
        unsigned char * foreground = schemes[scheme]+1;

        if (value > 0) while (value--) {
                if (background+2<schemes[scheme]+sizeof(basic)) {
                        background+=2;
                        foreground+=2;
                }
        }

        printf(color,length,"\033[38;5;%d;48;5;%dm",*foreground,*background);
}
//make 4x4 board & pts
void makeboard(unsigned char board[SIZE][SIZE]){
        unsigned char x, y;
        char c;
        char color[40], reset[] = "\033[m";

        printf("  2222      000        44     8888     \n");
        printf(" 22  22   00   00     4 4    88  88    \n");
        printf("    22    00   00    4  4     8888     \n");
        printf("   22     00   00   444444   88  88    \n");
        printf(" 222222     000         4     8888     \n\n");

        printf("       ------------\n");
        printf("       |          |\n");
        printf("       |    %ld pts | \n", score);
        printf("       ------------\n");






        for (y=0;y<SIZE;y++) {
                for (x=0;x<SIZE;x++) {
                        makecolor(board[x][y],color,40);
                        printf("%s",color);
                        printf("       ");
                        printf("%s",reset);
                }
                printf("\n");
                for (x=0;x<SIZE;x++) {
                        makecolor(board[x][y],color,40);
                        printf("%s",color);
                        if (board[x][y]!=0) {
                                char s[8];
                                snprintf(s,8,"%lu",(unsigned long)1<<board[x][y]);
                                unsigned char t = 7-strlen(s);
                                printf("%*s%s%*s",t-t/2,"",s,t/2,"");
                        } else {
                                printf("   +   ");
                        }
                        printf("%s",reset);
                }
                printf("\n");
                for (x=0;x<SIZE;x++) {
                        makecolor(board[x][y],color,40);
                        printf("%s",color);
                        printf("       ");
                        printf("%s",reset);
                }
                printf("\n");

        }
        printf("\n");
        printf("   MOVE: ←,↑,→,↓  QUIT: q     \n");
        printf("\033[A");
}

unsigned char findTarget(unsigned char array[SIZE],unsigned char x,unsigned char stop) {
        unsigned char t;
        if (x==0) {
                return x;
        }
        for(t=x-1;t>=0;t--) {
                if (array[t]!=0) {
                        if (array[t]!=array[x]) {
                                return t+1;
                        }
                        return t;
                } else {
                        if (t==stop) {
                                return t;
                        }
                }
        }
        return x;
}

void addRandom(unsigned char board[SIZE][SIZE]) {
        static bool initialized = false;
        unsigned char x,y;
        unsigned char r,len=0;
        unsigned char n,list[SIZE*SIZE][2];

        if (!initialized) {
                srand(time(NULL));
                initialized = true;
        }

        for (x=0;x<SIZE;x++) {
                for (y=0;y<SIZE;y++) {
                        if (board[x][y]==0) {
                                list[len][0]=x;
                                list[len][1]=y;
                                len++;
                        }
                }
        }

        if (len>0) {
                r = rand()%len;
                x = list[r][0];
                y = list[r][1];
                n = (rand()%10)/9+1;
                board[x][y]=n;
        }
}

//initialize the board before starting the game
void initboard(unsigned char board[SIZE][SIZE]) {
        unsigned char x,y;
        for (x=0;x<SIZE;x++) {
                for (y=0;y<SIZE;y++) {
                        board[x][y]=0;
                }
        }
        addRandom(board);
        addRandom(board);
        makeboard(board);
        score = 0;
}

//main 
int main(int argc, char *argv[]){
        unsigned char board[SIZE][SIZE];
        char c;

        initboard(board);
        while(1){
                c=getchar();
                if(c==-1){
                        printf("key error!\n");
                        break;
                }
                else{
                        makeboard(board);
                        usleep(15000);
                        makeboard(board);
                }
                if(c=='q'){
                        break;
                }
        }

        return EXIT_SUCCESS;
}
  

