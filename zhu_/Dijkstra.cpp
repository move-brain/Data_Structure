#include <stdio.h>
#define INF 10000000
#define MaxSize 50
int graph[MaxSize][MaxSize];  //MaxSize为最大顶点数     代表点之间的关系 
int dis[MaxSize];             //dis[i]为源点到顶点i的最短距离    存储最短距离 
int visit[MaxSize];            //visit[i]标记顶点i的最短路径是否已求出visit[i] == 1表示已求出
int prevetrix[MaxSize];       //前驱动点
void dij(int n)
{    
    int count = 0;          //count是已求出最短路径的顶点数目
    visit[0] = 1;    
    prevetrix[0] = 0;    
    count++;    
    for (int i = 1; i < n; i++)    //初始化 最短路径表  
    {        
        dis[i] = graph[0][i];        //graph[0][i]代表下标为0的点到下标为i的点的距离 
        prevetrix[i] = 0;    
    }    
    while (count < n)    
    {        
        int min = INF, target_index;        
        for (int i = 1; i < n; i++)        
        {            
            if (visit[i] == 0 && min > dis[i])         //找到距离源点最短的顶点target_index
            {                
                min = dis[i];                
                target_index = i;            
            }        
        }        
        visit[target_index] = 1;        
        count++;                               //求出源点与节点最短路径数加一 
        for (int i = 1; i < n; i++)        
        {            
            if (visit[i] == 0 && dis[target_index] + 
            graph[target_index][i] < dis[i])            //与原来的最短路径表的值 作比较  作出更新 
            {                
                dis[i] = dis[target_index] + graph[target_index][i];        //更新权值   就是路径长短的意思 
                prevetrix[i] = target_index;                  //记录该节点的路径前一个点  方便后面输出路径     
            }        
        }    
    }
}
int main()
{    
    int n, m;    
    scanf("%d %d", &n, &m);      //n代表顶点数，m为边数 
    int a, b, w, path[n];    
    for (int i = 0; i < n; i++)    
    {        
        for (int j = 0; j < n; j++)        
        {            
            graph[i][j] = INF;        //把每个值都初始化为最大,类似无穷 
        }    
    }    
    for (int i = 0; i < m; i++) 
    {        
        scanf("%d %d %d", &a, &b, &w);         //输入边的信息 a，b为顶点坐标 w为权值 
        graph[a][b] = w;    
    }     
    dij(n);    
    printf("\n\n");    
    for (int i = 1; i < n; i++)    
    {        
        if (dis[i] == INF)       //无穷大代表  没有路径     
        {            
            printf("顶点0到顶点%d没有最短路径\n", i);        
        }        
        else        
        {            
    	    printf("顶点0到顶点%d有长为%d的最短路径：", i,dis[i]);            
    	    int cur = i, index = 0;            
            path[index] = cur;            
            while (1)                //这个循环用于  找出i节点的前驱节点   即使路径        
            {                
                path[index + 1] = prevetrix[path[index]];                  //将前驱节点赋值给下一个数组元素 
                if (path[index + 1] == 0)                    //如果为零   代表没有前驱，则是源点  即是下标为0的节点 
                    break;                
                index++;            
            }            
            for (int j = index + 1; j > 0; j--)            
            {                
                printf("%d->", path[j]);           //输出路径   index+1为源点下标   
            }            
            printf("%d\n", path[0]);        //终点 
        }    
    }
}
