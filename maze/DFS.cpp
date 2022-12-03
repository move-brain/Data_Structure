#include <stdio.h>
#include <stdlib.h>
typedef int DataType;
int n=0;
struct Node     
{
	DataType data;
	struct Node* next;
};

struct Maze   //存储迷宫 的结构 
{
	DataType data[100][100];
	int size;
}; 

typedef struct Node *PNode;    
typedef struct Node *top, *LinkStack;


LinkStack SetNullStack_Link()   //建立链表 顺序链表  其实就是栈 
{
	LinkStack top =(LinkStack)malloc(sizeof(struct Node));
	if (top != NULL)
		top->next = NULL;
	else 
		 printf("Alloc failure");
	return top;
 } 

int IsNullStack_link(LinkStack top)    //判断栈是否为空 
{
	n=n+1;
	if(top->next == NULL)
		return 1;
	else 
		return 0;
 } 
 
 
void Push_link(LinkStack top,DataType x)    //在栈的头指针后 添加节点 
{
	n=n+1;
	PNode p;
	p = (PNode)malloc(sizeof(struct Node));
	if(top == NULL)
		printf("Alloc failure");
	else
	{
		p->data = x;
		p->next = top->next;
		top->next = p;
	}	
 } 
 
 //???
 
void Pop_link(LinkStack top)    //删除栈顶元素 
 {
 	n=n+1;
 	PNode p;
 	if(IsNullStack_link(top))
 	{
 		printf("it is empty stack!11");
	 }
	 else{
	 p = top->next; 
	 top->next = p->next;
	 free(p);	
	 }
	 
  } 


//????????

DataType Top_link(LinkStack top)   //获取栈顶元素 
{
	n=n+1;
	if(IsNullStack_link(top))
		printf("it is empty stack!22");
	else 
		return top->next->data;
 } 


// 
int MazeDFS(int entryX,int entryY,int exitX,int exitY,Maze maze)   //速度搜索算法实现函数 
{
	
	int direction[4][2]={{0,1},{1,0},{0,-1},{-1,0}};   
	LinkStack linkStackX = NULL;   //存储经过过的节点信息   就是还没有回溯扫描的节点   两个链表存储x,y 
	LinkStack linkStackY = NULL;      
	int posX,posY;   //临时变量,用于探索不同方向上的节点 
	int preposX,preposY;   //用于存储前驱节点 
	int **mark;   //用于存储节点是否被探索过的信息 
	int i,j;
	int mov;
	
	mark = (int**)malloc(sizeof(int*) * maze.size);   //简单的初始化 
	for(i=0;i<maze.size;i++)
		mark[i]=(int*)malloc(sizeof(int)*maze.size);
	for(i=0;i<maze.size;i++)
	{
		for(j=0;j<maze.size;j++)
			mark[i][j]=0;
	}
	linkStackX = SetNullStack_Link(); //定义存储x坐标的链表 
	linkStackY = SetNullStack_Link();    //同理 
	mark[entryX][entryY] = 1;  //1即是被探索过 
	Push_link(linkStackX,entryX);  
	Push_link(linkStackY,entryY);
	while(!IsNullStack_link(linkStackX))
	{
		preposX = Top_link(linkStackX);
		preposY = Top_link(linkStackY);
		Pop_link(linkStackX);
		Pop_link(linkStackY);
		mov = 0;
		while(mov<4)   //即是扫描四个方向 
		{
			posX = preposX + direction[mov][0];
			posY = preposY + direction[mov][1];
			if(posX == exitX && posY == exitY)
			{
				Push_link(linkStackX,preposX);
				Push_link(linkStackY,preposY);
				while(!IsNullStack_link(linkStackX))
				{
					posX = Top_link(linkStackX);
					posY = Top_link(linkStackY);
					Pop_link(linkStackX);
					Pop_link(linkStackY);
					printf("(%d,%d)",posX,posY);
				}
				return 1;
			}
		if(maze.data[posX][posY] == 0 && mark[posX][posY]==0)   
		{
			mark[posX][posY] = 1;
			Push_link(linkStackX,preposX);
			Push_link(linkStackY,preposY);
			preposX = posX;
			preposY = posY;
			mov = 0;   //意思是直接往一个方向深入 
		
		}
		else
			mov++; 
		}
		
	}
	
	return 0;
	
} 


int main()
{
	int size,exitX,exitY,entryY,entryX;
	Maze maze;
	printf("请输入迷宫大小，输入4，则为4X4迷宫大小:\n"); 
	scanf("%d",&maze.size);  //输入迷宫大小 
	printf("请输入迷宫信息:\n");
	for(int i=0;i<maze.size;i++){      //、输入迷宫信息 
		for(int j=0;j<maze.size;j++){
			scanf("%d",&maze.data[i][j]);
		}
	}
	printf("请输入人口坐标和出口坐标,如1 2 1 2:\n");
	scanf("%d%d%d%d",&entryX,&entryY,&exitX,&exitY); //输入人口和出口 

	MazeDFS(entryX,entryY,exitX,exitY,maze);
	printf("\n一共執行%d步",n);
}




 
