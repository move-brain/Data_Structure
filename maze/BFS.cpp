#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
int n=0;
struct Node
{
    DataType data;
    struct Node *link;
};
typedef struct Node*PNode;
struct Queue
{
    PNode f;
    PNode r;
};
typedef struct Queue *LinkQueue;
struct MAZE_STRU
{
    int size;
    int **data;   //不用纠结双重指针，其实就是二维数组来用 
};
typedef struct MAZE_STRU Maze;
LinkQueue SetNullQueue_Link()//创建空队列
{
    LinkQueue lqueue;
    lqueue=(LinkQueue)malloc(sizeof(struct Queue));
    if(lqueue!=NULL)
    {
        lqueue->f=NULL;     //初始化 
        lqueue->r=NULL;
    }
    else
        printf("Aloc failure!\n");
    return lqueue;
}
int IsNullQueue_Link(LinkQueue lqueue)//判断队列是否为空
{
	n=n+1;
   return  (lqueue->f==NULL);
}
void EnQueue_Link(LinkQueue lqueue,DataType x)//入队操作
{
	n=n+1;
    PNode p;
    p=(PNode)malloc(sizeof(struct Node));//申请节点空间
    if(p==NULL)
        printf("Alloc Failure!\n");
    else
    {    p->data=x;//数据域赋值
         p->link=NULL;//指针域赋值
        if(lqueue->f==NULL)//空队列的特殊处理
        {
            lqueue->f=p;
            lqueue->r=p;
        }
        else
        {
            lqueue->r->link=p;//插入队尾
            lqueue->r=p;//修改队尾指针
        }
    }

}
void DeQueue_Link(LinkQueue lqueue)  //出队操作 
{
	n=n+1;
    PNode p;
    if(lqueue->f==NULL)
        printf("It is empty queue!\n");
    else
    {
        p=lqueue->f;
        lqueue->f=lqueue->f->link; //指向下一个节点 
        free(p);
    }
}
DataType FrontQueue_Link(LinkQueue lqueue) //取队头元素 
{
            n=n+1;
    if(lqueue->f==NULL)
    {
         printf("It is empty queue");
         return 0;
    }
    else
    {

        return lqueue->f->data;   
    }

}
Maze* InitMaze(int size)  //初始化 size为迷宫长度  data为存储迷宫的变量 
{
    int i;
    Maze*maze=(Maze*)malloc(sizeof(Maze));
    maze->size=size;
    maze->data=(int **)malloc(sizeof(int*)*maze->size);
    for(i=0;i<maze->size;i++)
    {
        maze->data[i]=(int*)malloc(sizeof(int)*maze->size);
    }
    
    return maze;
}
void ReadMaze(Maze* maze)    //输入迷宫    
{   int i,j;
printf("请输入迷宫信息:\n");
    for(i=0;i<maze->size;i++)
    {
        for(j=0;j<maze->size;j++)
        scanf("%d",&maze->data[i][j]);    
    }
}
void WriteMaze(Maze* maze)   //输出迷宫 
{
    int i,j;
    printf("迷宫的结构如下：\n");
    for(i=0;i<maze->size;i++)
    {
        for(j=0;j<maze->size;j++)
        {
            printf("%5d",maze->data[i][j]);
        }
        printf("\n");
    }
}




int MazeBFS(int entryX,int entryY,int exitX,int exitY,Maze *maze)
{
    LinkQueue linkQueueX=NULL;
    LinkQueue linkQueueY=NULL;
    int direction[4][2]={{0,1},{1.0},{0,-1},{-1,0}};
    int preposX,preposY;
    int posX,posY;                        //临时变量，存放坐标点（x,y）

    int i,j,mov;
    int **preposMarkX;                      //记录迷宫行走的前驱X值，每个节点只查询一次 ,如 我是根据（1，1）这个坐标查询到（1，2）那么 preposMarkx[1][2]的值就是1，而preposMarky也是1，就是分别存储 
    int **preposMarkY;                   //记录迷宫行走过程中的前驱Y值
    int **Mark;                           //标记二维数组，标记那些点走过，不再重复走    1是走过 
          //给存放前驱的数组X分配空间
    preposMarkX=(int **)malloc(sizeof(int*)*maze->size);
    for(i=0;i<maze->size;i++)
    {
        preposMarkX[i]=(int *)malloc(sizeof(int)*maze->size);
    }
    //给存放前驱的数组Y分配空间
    preposMarkY=(int **)malloc(sizeof(int*)*maze->size);
    for(i=0;i<maze->size;i++)
    {
        preposMarkY[i]=(int *)malloc(sizeof(int)*maze->size);
    }//给做标记的二维数组分配空间，并附初值
    Mark=(int **)malloc(sizeof(int*)*maze->size);
    for(i=0;i<maze->size;i++)
    {
        Mark[i]=(int *)malloc(sizeof(int)*maze->size);
    }
    for(i=0;i<maze->size;i++)//给所有元素设置初值
    {
        for(j=0;j<maze->size;j++)
        {
            preposMarkX[i][j]=-1;
            preposMarkX[i][j]=-1;
            Mark[i][j]=0;
        }

    }
    linkQueueX=SetNullQueue_Link();       //创建空队列
    linkQueueY=SetNullQueue_Link();        //创建空队列
    EnQueue_Link(linkQueueX,entryX);       //迷宫入口点入队
    EnQueue_Link(linkQueueY,entryY);        //迷宫入口点入队
    Mark[entryX][entryY]=1;                                   //迷宫设置标志位
    while(!IsNullQueue_Link(linkQueueX))
   {
        preposX=FrontQueue_Link(linkQueueX);//取队头
        DeQueue_Link(linkQueueX);//出队
        preposY=FrontQueue_Link(linkQueueY);//取队头
        DeQueue_Link(linkQueueY);//出队
    //将于当前点相邻且满足一定条件的点放入队列
        for(mov=0;mov<4;mov++)                     //posx为搜索时被搜索的节点  preposx为posx的前驱节点的x坐标值   preposy同理 
        {
            posX=preposX+direction[mov][0];  //分别对当前节点的上下左右的四个坐标进行赋值  进行探查 
            posY=preposY+direction[mov][1];
            if(posX==exitX&&posY==exitY)//到达出口点     
            {
                preposMarkX[posX][posY]=preposX;   //记录前驱 
                preposMarkY[posX][posY]=preposY;
                  
                while(!(posX==entryX&&posY==entryY))          //循环输出路线 
                {
                    preposX=preposMarkX[posX][posY];  //节点回退 
                    preposY=preposMarkY[posX][posY];    
                    if(posX==exitX&&posY==exitY)
                        printf("(%d,%d)",exitX,exitY);
                    posX=preposX;                    //回溯到前一个节点  
                    posY=preposY;
                    printf("(%d,%d)",posX,posY);      //输出走过的路线 
                }
                return 1;
            }
            //如果能走，且没有被扩展过
            if(maze->data[posX][posY]==0&&Mark[posX][posY]==0)
            {
                EnQueue_Link(linkQueueX,posX);                    //入队扩展
                EnQueue_Link(linkQueueY,posY);
                Mark[posX][posY]=1;                             //做标记
                preposMarkX[posX][posY]=preposX;    //记录前驱
                preposMarkY[posX][posY]=preposY;
            }

        }
   }
   return 0;
}
int main()
{
    Maze* maze;
    int mazeSize;
    int entryX,entryY,exitX,exitY;
    int find=0;
    printf("请输入迷宫大小，输入4，则为4X4迷宫大小:\n");
    scanf("%d",&mazeSize);
//    printf("%d",mazeSize); 
    maze=InitMaze(mazeSize);      
    ReadMaze(maze);
//     WriteMaze(maze); 
printf("请输入人口坐标和出口坐标,如1 2 1 2:\n");
    scanf("%d %d %d %d",&entryX,&entryY,&exitX,&exitY);//输入出发点坐标  和出去的节点坐标 
    //printf("%d%d%d%d",entryX,entryY,exitX,exitY);
    find=MazeBFS(entryX,entryY,exitX,exitY,maze); 
	     printf("\n一共執行%d步",n);
    if(find==0)  
        printf("找不到路径！");
    return 0;
}
