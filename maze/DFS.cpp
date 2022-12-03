#include <stdio.h>
#include <stdlib.h>
typedef int DataType;
int n=0;
struct Node     
{
	DataType data;
	struct Node* next;
};

struct Maze   //�洢�Թ� �Ľṹ 
{
	DataType data[100][100];
	int size;
}; 

typedef struct Node *PNode;    
typedef struct Node *top, *LinkStack;


LinkStack SetNullStack_Link()   //�������� ˳������  ��ʵ����ջ 
{
	LinkStack top =(LinkStack)malloc(sizeof(struct Node));
	if (top != NULL)
		top->next = NULL;
	else 
		 printf("Alloc failure");
	return top;
 } 

int IsNullStack_link(LinkStack top)    //�ж�ջ�Ƿ�Ϊ�� 
{
	n=n+1;
	if(top->next == NULL)
		return 1;
	else 
		return 0;
 } 
 
 
void Push_link(LinkStack top,DataType x)    //��ջ��ͷָ��� ��ӽڵ� 
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
 
void Pop_link(LinkStack top)    //ɾ��ջ��Ԫ�� 
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

DataType Top_link(LinkStack top)   //��ȡջ��Ԫ�� 
{
	n=n+1;
	if(IsNullStack_link(top))
		printf("it is empty stack!22");
	else 
		return top->next->data;
 } 


// 
int MazeDFS(int entryX,int entryY,int exitX,int exitY,Maze maze)   //�ٶ������㷨ʵ�ֺ��� 
{
	
	int direction[4][2]={{0,1},{1,0},{0,-1},{-1,0}};   
	LinkStack linkStackX = NULL;   //�洢�������Ľڵ���Ϣ   ���ǻ�û�л���ɨ��Ľڵ�   ��������洢x,y 
	LinkStack linkStackY = NULL;      
	int posX,posY;   //��ʱ����,����̽����ͬ�����ϵĽڵ� 
	int preposX,preposY;   //���ڴ洢ǰ���ڵ� 
	int **mark;   //���ڴ洢�ڵ��Ƿ�̽��������Ϣ 
	int i,j;
	int mov;
	
	mark = (int**)malloc(sizeof(int*) * maze.size);   //�򵥵ĳ�ʼ�� 
	for(i=0;i<maze.size;i++)
		mark[i]=(int*)malloc(sizeof(int)*maze.size);
	for(i=0;i<maze.size;i++)
	{
		for(j=0;j<maze.size;j++)
			mark[i][j]=0;
	}
	linkStackX = SetNullStack_Link(); //����洢x��������� 
	linkStackY = SetNullStack_Link();    //ͬ�� 
	mark[entryX][entryY] = 1;  //1���Ǳ�̽���� 
	Push_link(linkStackX,entryX);  
	Push_link(linkStackY,entryY);
	while(!IsNullStack_link(linkStackX))
	{
		preposX = Top_link(linkStackX);
		preposY = Top_link(linkStackY);
		Pop_link(linkStackX);
		Pop_link(linkStackY);
		mov = 0;
		while(mov<4)   //����ɨ���ĸ����� 
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
			mov = 0;   //��˼��ֱ����һ���������� 
		
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
	printf("�������Թ���С������4����Ϊ4X4�Թ���С:\n"); 
	scanf("%d",&maze.size);  //�����Թ���С 
	printf("�������Թ���Ϣ:\n");
	for(int i=0;i<maze.size;i++){      //�������Թ���Ϣ 
		for(int j=0;j<maze.size;j++){
			scanf("%d",&maze.data[i][j]);
		}
	}
	printf("�������˿�����ͳ�������,��1 2 1 2:\n");
	scanf("%d%d%d%d",&entryX,&entryY,&exitX,&exitY); //�����˿ںͳ��� 

	MazeDFS(entryX,entryY,exitX,exitY,maze);
	printf("\nһ������%d��",n);
}




 
