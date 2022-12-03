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
    int **data;   //���þ���˫��ָ�룬��ʵ���Ƕ�ά�������� 
};
typedef struct MAZE_STRU Maze;
LinkQueue SetNullQueue_Link()//�����ն���
{
    LinkQueue lqueue;
    lqueue=(LinkQueue)malloc(sizeof(struct Queue));
    if(lqueue!=NULL)
    {
        lqueue->f=NULL;     //��ʼ�� 
        lqueue->r=NULL;
    }
    else
        printf("Aloc failure!\n");
    return lqueue;
}
int IsNullQueue_Link(LinkQueue lqueue)//�ж϶����Ƿ�Ϊ��
{
	n=n+1;
   return  (lqueue->f==NULL);
}
void EnQueue_Link(LinkQueue lqueue,DataType x)//��Ӳ���
{
	n=n+1;
    PNode p;
    p=(PNode)malloc(sizeof(struct Node));//����ڵ�ռ�
    if(p==NULL)
        printf("Alloc Failure!\n");
    else
    {    p->data=x;//������ֵ
         p->link=NULL;//ָ����ֵ
        if(lqueue->f==NULL)//�ն��е����⴦��
        {
            lqueue->f=p;
            lqueue->r=p;
        }
        else
        {
            lqueue->r->link=p;//�����β
            lqueue->r=p;//�޸Ķ�βָ��
        }
    }

}
void DeQueue_Link(LinkQueue lqueue)  //���Ӳ��� 
{
	n=n+1;
    PNode p;
    if(lqueue->f==NULL)
        printf("It is empty queue!\n");
    else
    {
        p=lqueue->f;
        lqueue->f=lqueue->f->link; //ָ����һ���ڵ� 
        free(p);
    }
}
DataType FrontQueue_Link(LinkQueue lqueue) //ȡ��ͷԪ�� 
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
Maze* InitMaze(int size)  //��ʼ�� sizeΪ�Թ�����  dataΪ�洢�Թ��ı��� 
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
void ReadMaze(Maze* maze)    //�����Թ�    
{   int i,j;
printf("�������Թ���Ϣ:\n");
    for(i=0;i<maze->size;i++)
    {
        for(j=0;j<maze->size;j++)
        scanf("%d",&maze->data[i][j]);    
    }
}
void WriteMaze(Maze* maze)   //����Թ� 
{
    int i,j;
    printf("�Թ��Ľṹ���£�\n");
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
    int posX,posY;                        //��ʱ�������������㣨x,y��

    int i,j,mov;
    int **preposMarkX;                      //��¼�Թ����ߵ�ǰ��Xֵ��ÿ���ڵ�ֻ��ѯһ�� ,�� ���Ǹ��ݣ�1��1����������ѯ����1��2����ô preposMarkx[1][2]��ֵ����1����preposMarkyҲ��1�����Ƿֱ�洢 
    int **preposMarkY;                   //��¼�Թ����߹����е�ǰ��Yֵ
    int **Mark;                           //��Ƕ�ά���飬�����Щ���߹��������ظ���    1���߹� 
          //�����ǰ��������X����ռ�
    preposMarkX=(int **)malloc(sizeof(int*)*maze->size);
    for(i=0;i<maze->size;i++)
    {
        preposMarkX[i]=(int *)malloc(sizeof(int)*maze->size);
    }
    //�����ǰ��������Y����ռ�
    preposMarkY=(int **)malloc(sizeof(int*)*maze->size);
    for(i=0;i<maze->size;i++)
    {
        preposMarkY[i]=(int *)malloc(sizeof(int)*maze->size);
    }//������ǵĶ�ά�������ռ䣬������ֵ
    Mark=(int **)malloc(sizeof(int*)*maze->size);
    for(i=0;i<maze->size;i++)
    {
        Mark[i]=(int *)malloc(sizeof(int)*maze->size);
    }
    for(i=0;i<maze->size;i++)//������Ԫ�����ó�ֵ
    {
        for(j=0;j<maze->size;j++)
        {
            preposMarkX[i][j]=-1;
            preposMarkX[i][j]=-1;
            Mark[i][j]=0;
        }

    }
    linkQueueX=SetNullQueue_Link();       //�����ն���
    linkQueueY=SetNullQueue_Link();        //�����ն���
    EnQueue_Link(linkQueueX,entryX);       //�Թ���ڵ����
    EnQueue_Link(linkQueueY,entryY);        //�Թ���ڵ����
    Mark[entryX][entryY]=1;                                   //�Թ����ñ�־λ
    while(!IsNullQueue_Link(linkQueueX))
   {
        preposX=FrontQueue_Link(linkQueueX);//ȡ��ͷ
        DeQueue_Link(linkQueueX);//����
        preposY=FrontQueue_Link(linkQueueY);//ȡ��ͷ
        DeQueue_Link(linkQueueY);//����
    //���ڵ�ǰ������������һ�������ĵ�������
        for(mov=0;mov<4;mov++)                     //posxΪ����ʱ�������Ľڵ�  preposxΪposx��ǰ���ڵ��x����ֵ   preposyͬ�� 
        {
            posX=preposX+direction[mov][0];  //�ֱ�Ե�ǰ�ڵ���������ҵ��ĸ�������и�ֵ  ����̽�� 
            posY=preposY+direction[mov][1];
            if(posX==exitX&&posY==exitY)//������ڵ�     
            {
                preposMarkX[posX][posY]=preposX;   //��¼ǰ�� 
                preposMarkY[posX][posY]=preposY;
                  
                while(!(posX==entryX&&posY==entryY))          //ѭ�����·�� 
                {
                    preposX=preposMarkX[posX][posY];  //�ڵ���� 
                    preposY=preposMarkY[posX][posY];    
                    if(posX==exitX&&posY==exitY)
                        printf("(%d,%d)",exitX,exitY);
                    posX=preposX;                    //���ݵ�ǰһ���ڵ�  
                    posY=preposY;
                    printf("(%d,%d)",posX,posY);      //����߹���·�� 
                }
                return 1;
            }
            //������ߣ���û�б���չ��
            if(maze->data[posX][posY]==0&&Mark[posX][posY]==0)
            {
                EnQueue_Link(linkQueueX,posX);                    //�����չ
                EnQueue_Link(linkQueueY,posY);
                Mark[posX][posY]=1;                             //�����
                preposMarkX[posX][posY]=preposX;    //��¼ǰ��
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
    printf("�������Թ���С������4����Ϊ4X4�Թ���С:\n");
    scanf("%d",&mazeSize);
//    printf("%d",mazeSize); 
    maze=InitMaze(mazeSize);      
    ReadMaze(maze);
//     WriteMaze(maze); 
printf("�������˿�����ͳ�������,��1 2 1 2:\n");
    scanf("%d %d %d %d",&entryX,&entryY,&exitX,&exitY);//�������������  �ͳ�ȥ�Ľڵ����� 
    //printf("%d%d%d%d",entryX,entryY,exitX,exitY);
    find=MazeBFS(entryX,entryY,exitX,exitY,maze); 
	     printf("\nһ������%d��",n);
    if(find==0)  
        printf("�Ҳ���·����");
    return 0;
}
