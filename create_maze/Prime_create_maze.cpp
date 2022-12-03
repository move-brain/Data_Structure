#include <fstream>
#include <iostream>
#include <math.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <stdlib.h>
static const int L = 10;
using namespace std;

int main()
{

	string path = "maze/" + to_string(L) + 'x' + to_string(L) + ".txt";
	ofstream fout(path);
	// 存入长度
	fout << L << " " << L << endl;

	int Maze[L][L] = {0};

	//最外围设置为路，可以有效的保护里面一层墙体，并防止挖出界
	for (int i = 0; i < L; i++)
	{
		Maze[i][0] = 1;
		Maze[0][i] = 1;
		Maze[L - 1][i] = 1;
		Maze[i][L - 1] = 1;
	}

	//墙队列，包括X , Y
	vector<int> X;
	vector<int> Y;
	//任取初始值
	X.push_back(2);
	Y.push_back(2);

	//当墙队列为空时结束循环
	while (X.size())
	{
		//在墙队列中随机取一点
		int r = rand() % X.size();
		int x = X[r];
		int y = Y[r];

		//判读上下左右四个方向是否为路
		int count = 0;
		for (int i = x - 1; i < x + 2; i++)
		{
			for (int j = y - 1; j < y + 2; j++)
			{
				if (abs(x - i) + abs(y - j) == 1 && Maze[i][j] > 0)
				{
					++count;
				}
			}
		}

		if (count <= 1)
		{
			Maze[x][y] = 1;
			//在墙队列中插入新的墙
			for (int i = x - 1; i < x + 2; i++)
			{
				for (int j = y - 1; j < y + 2; j++)
				{
					if (abs(x - i) + abs(y - j) == 1 && Maze[i][j] == 0)
					{
						X.push_back(i);
						Y.push_back(j);
					}
				}
			}
		}

		//删除当前墙
		X.erase(X.begin() + r);
		Y.erase(Y.begin() + r);
	}

	//设置迷宫进出口
	Maze[2][1] = 1;
	int i;
	for (i = L - 3; i >= 0; i--)
	{
		if (Maze[i][L - 3] == 1)
		{
			Maze[i][L - 2] = 1;
			break;
		}
	}
	
	
	
	
	
	//画迷宫
	for (int i = 0; i < L; i++)
	{
		for (int j = 1; j < L-1; j++)
		{
			fout << Maze[i][j];
			if (Maze[i][j] == 1)
			//	printf("  ");
			printf(" %d",0);	
			else
			//	printf("口");
			printf(" %d",1);
		}
		printf("\n");
		fout << '\n';
	}
//		for (int i = 0; i < L; i++)
//	{
//		for (int j = 0; j < L; j++)
//		{
//			fout << Maze[i][j];
//			if (Maze[i][j] == 1)
//				printf("  ");
//			//printf("%d",1);	
//			else
//				printf("哈");
//			//printf("%d",0);
//		}
//		printf("\n");
//		fout << '\n';
//	}
	// 存入路口
	fout << 2 << " " << 2 << " ";
	fout << i << " " << L - 2 << endl;
	fout.close();
	return 0;
}
