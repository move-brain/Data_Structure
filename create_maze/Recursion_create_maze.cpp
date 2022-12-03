#include <iostream>
#include <stdlib.h>
#include <time.h>
static const int L=42;
 
static const int ROUTE=0;
static const int WALL=1;
 
void CreateMaze(int **maze,int x1,int y1,int x2,int y2){
    //�ж��Ƿ��ܼ����ָ�
    if(x2-x1<2||y2-y1<2){
        return ;
    }
    
    //���ȡ��
    int x=x1+1+rand()%(x2-x1-1);
    int y=y1+1+rand()%(y2-y1-1);
    
    //��ǽ
    for(int i=x1;i<=x2;i++) maze[i][y]=WALL;
    for(int i=y1;i<=y2;i++) maze[x][i]=WALL;
 
    //�ݹ�ָ������������
    CreateMaze(maze,x1,y1,x-1,y-1);
    CreateMaze(maze, x+1, y+1, x2, y2);
    CreateMaze(maze,x+1,y1,x2,y-1);
    CreateMaze(maze, x1, y+1, x-1, y2);
    
    //���ȡ���е�����ǽ
    int r[4]={0};
    r[rand()%4]=1;
    
    //��ǽ�����ȡ�㿪��
    for(int i=0;i<4;i++){
        if(r[i]==0){
            int rx=x;
            int ry=y;
            switch (i) {
                case 0:
                    //�жϸ�λ���Ƿ���ȷ����ͨ�������������ж����ݣ���������λ�����ֻ������ǽ������һ��
                    do{
                        rx=x1+rand()%(x-x1);
                    }while(maze[rx-1][ry]+maze[rx+1][ry]+maze[rx][ry-1]+maze[rx][ry+1]>2*WALL);
                    break;
                case 1:
                    do{
                        ry=y+1+rand()%(y2-y);
                    }while(maze[rx-1][ry]+maze[rx+1][ry]+maze[rx][ry-1]+maze[rx][ry+1]>2*WALL);
                    break;
                case 2:
                    do{
                        rx=x+1+rand()%(x2-x);
                    }while(maze[rx-1][ry]+maze[rx+1][ry]+maze[rx][ry-1]+maze[rx][ry+1]>2*WALL);
                    break;
                case 3:
                    do{
                        ry=y1+rand()%(y-y1);
                    }while(maze[rx-1][ry]+maze[rx+1][ry]+maze[rx][ry-1]+maze[rx][ry+1]>2*WALL);
                    break;
                default:
                    break;
            }
            maze[rx][ry]=ROUTE;
        }
    }
}
 
int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));
    
    int **Maze=(int**)malloc(L*sizeof(int*));
    for(int i=0;i<L;i++){
        Maze[i]=(int*)calloc(L,sizeof(int));
    }
    
    //���һȦΪǽ
    for(int i=0;i<L;i++){
        Maze[0][i]=WALL;
        Maze[i][0]=WALL;
        Maze[L-1][i]=WALL;
        Maze[i][L-1]=WALL;
    }
    
    //�����Թ�
    CreateMaze(Maze, 1,1, L-2, L-2);
    
    //���ó���
    Maze[1][0]=ROUTE;
    Maze[L-2][L-1]=ROUTE;
    
    //���Թ�
    for(int i=0;i<L;i++){
        for(int j=0;j<L;j++){
            if(Maze[i][j]==WALL){
                printf("XX");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
    
    for(int i=0;i<L;i++) free(Maze[i]);
    free(Maze);
    
    return 0;
}
