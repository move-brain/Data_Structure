#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>
#include <stdlib.h>
//��ͼ����L�������Թ�����40�����İ�Χ��ǽ��2��������Χ·��2
#define L 12
 
//ǽ��·���ı�ʶ
#define WALL  0
#define ROUTE 1
 
//�����Թ��ĸ��Ӷȣ���ֵԽ���Ӷ�Խ�ͣ���СֵΪ0
static int Rank = 0;
 
//�����Թ�
void CreateMaze(int **maze, int x, int y);
 
int main(void) {
	srand((unsigned)time(NULL));
 
	int **Maze = (int**)malloc(L * sizeof(int *));
	for (int i = 0; i < L; i++) {
		Maze[i] = (int*)calloc(L, sizeof(int));
	}
 
	//����Χ����Ϊ·����ԭ��Ϊ�˷�ֹ��·ʱ�ڳ��߽磬ͬʱΪ�˱����Թ��������һȦǽ�屻�ڴ�
	for (int i = 0; i < L; i++){
		Maze[i][0] = ROUTE;
		Maze[0][i] = ROUTE;
		Maze[i][L - 1] = ROUTE;
		Maze[L - 1][i] = ROUTE;
	}
 
	//�����Թ�����2��2��Ϊ���
	CreateMaze(Maze, 2, 2);
 
	//���Թ�����ںͳ���
	Maze[2][1] = ROUTE;
 
	//�����㷨����ԣ�������һ�����ʲ��ڣ�L-3,L-2��������ʱ��ҪѰ�ҳ���
	for (int i = L - 3; i >= 0; i--) {
		if (Maze[i][L - 3] == ROUTE) {
			Maze[i][L - 2] = ROUTE;
			break;
		}
	}
 
	//���Թ�
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			if (Maze[i][j] == ROUTE) {
				printf("  ");
			}
			else {
				printf("��");
			}
		}
		printf("\n");
	}
 	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			if (Maze[i][j] == ROUTE) {
				printf("0");
			}
			else {
				printf("1");
			}
		}
		printf("\n");
	}
	for (int i = 0; i < L; i++) free(Maze[i]);
	free(Maze);
 
	system("pause");
	return 0;
}
 
void CreateMaze(int **maze, int x, int y) {
	maze[x][y] = ROUTE;
 
	//ȷ���ĸ��������
	int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	for (int i = 0; i < 4; i++) {
		int r = rand() % 4;
		int temp = direction[0][0];
		direction[0][0] = direction[r][0];
		direction[r][0] = temp;
 
		temp = direction[0][1];
		direction[0][1] = direction[r][1];
		direction[r][1] = temp;
	}
 
	//���ĸ�������
	for (int i = 0; i < 4; i++) {
		int dx = x;
		int dy = y;
 
		//�����ڵľ��룬��Rank��������С
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range>0) {
			dx += direction[i][0];
			dy += direction[i][1];
 
			//�ų�����ͷ·
			if (maze[dx][dy] == ROUTE) {
				break;
			}
 
			//�ж��Ƿ��ڴ�·��
			int count = 0;
			for (int j = dx - 1; j < dx + 2; j++) {
				for (int k = dy - 1; k < dy + 2; k++) {
					//abs(j - dx) + abs(k - dy) == 1 ȷ��ֻ�жϾŹ�����ĸ��ض�λ��
					if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == ROUTE) {
						count++;
					}
				}
			}
 
			if (count > 1) {
				break;
			}
 
			//ȷ�������ڴ�ʱ��ǰ��
			--range;
			maze[dx][dy] = ROUTE;
		}
 
		//û���ڴ�Σ�գ��Դ�Ϊ�ڵ�ݹ�
		if (range <= 0) {
			CreateMaze(maze, dx, dy);
		}
	}
}
