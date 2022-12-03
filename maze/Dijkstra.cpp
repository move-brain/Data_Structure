#include <stdio.h>
#define INF 10000000
#define MaxSize 50
int graph[MaxSize][MaxSize];  //MaxSizeΪ��󶥵���     �����֮��Ĺ�ϵ 
int dis[MaxSize];             //dis[i]ΪԴ�㵽����i����̾���    �洢��̾��� 
int visit[MaxSize];            //visit[i]��Ƕ���i�����·���Ƿ������visit[i] == 1��ʾ�����
int prevetrix[MaxSize];       //ǰ������
void dij(int n)
{    
    int count = 0;          //count����������·���Ķ�����Ŀ
    visit[0] = 1;    
    prevetrix[0] = 0;    
    count++;    
    for (int i = 1; i < n; i++)    //��ʼ�� ���·����  
    {        
        dis[i] = graph[0][i];        //graph[0][i]�����±�Ϊ0�ĵ㵽�±�Ϊi�ĵ�ľ��� 
        prevetrix[i] = 0;    
    }    
    while (count < n)    
    {        
        int min = INF, target_index;        
        for (int i = 1; i < n; i++)        
        {            
            if (visit[i] == 0 && min > dis[i])         //�ҵ�����Դ����̵Ķ���target_index
            {                
                min = dis[i];                
                target_index = i;            
            }        
        }        
        visit[target_index] = 1;        
        count++;                               //���Դ����ڵ����·������һ 
        for (int i = 1; i < n; i++)        
        {            
            if (visit[i] == 0 && dis[target_index] + 
            graph[target_index][i] < dis[i])            //��ԭ�������·�����ֵ ���Ƚ�  �������� 
            {                
                dis[i] = dis[target_index] + graph[target_index][i];        //����Ȩֵ   ����·�����̵���˼ 
                prevetrix[i] = target_index;                  //��¼�ýڵ��·��ǰһ����  ����������·��     
            }        
        }    
    }
}
int main()
{    
    int n, m;    
    scanf("%d %d", &n, &m);      //n����������mΪ���� 
    int a, b, w, path[n];    
    for (int i = 0; i < n; i++)    
    {        
        for (int j = 0; j < n; j++)        
        {            
            graph[i][j] = INF;        //��ÿ��ֵ����ʼ��Ϊ���,�������� 
        }    
    }    
    for (int i = 0; i < m; i++) 
    {        
        scanf("%d %d %d", &a, &b, &w);         //����ߵ���Ϣ a��bΪ�������� wΪȨֵ 
        graph[a][b] = w;    
    }     
    dij(n);    
    printf("\n\n");    
    for (int i = 1; i < n; i++)    
    {        
        if (dis[i] == INF)       //��������  û��·��     
        {            
            printf("����0������%dû�����·��\n", i);        
        }        
        else        
        {            
    	    printf("����0������%d�г�Ϊ%d�����·����", i,dis[i]);            
    	    int cur = i, index = 0;            
            path[index] = cur;            
            while (1)                //���ѭ������  �ҳ�i�ڵ��ǰ���ڵ�   ��ʹ·��        
            {                
                path[index + 1] = prevetrix[path[index]];                  //��ǰ���ڵ㸳ֵ����һ������Ԫ�� 
                if (path[index + 1] == 0)                    //���Ϊ��   ����û��ǰ��������Դ��  �����±�Ϊ0�Ľڵ� 
                    break;                
                index++;            
            }            
            for (int j = index + 1; j > 0; j--)            
            {                
                printf("%d->", path[j]);           //���·��   index+1ΪԴ���±�   
            }            
            printf("%d\n", path[0]);        //�յ� 
        }    
    }
}
