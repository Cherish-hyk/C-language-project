#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols,char set)
{
	int i = 0;
	int j = 0;
	for (i = 1; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i <= row; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <=row; i++)
	{
		printf("%d ", i);
		for (j = 1; j<=col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}
int get_mine_count(char mine[ROWS][COLS], int x, int y)
{
	    return mine[x + 1][y + 1] +
		       mine[x + 1][y] +
		       mine[x + 1][y - 1] +
		       mine[x][y + 1] +
		       mine[x][y - 1] +
		       mine[x - 1][y + 1] +
		       mine[x - 1][y] +
		       mine[x - 1][y - 1] - 8 * '0';
}
void SpreadBoard(char mine[ROWS][COLS],char show[ROWS][COLS],int x,int y)
{
	//show[x + 1][y + 1] = ' ';
	//show[x + 1][y ] = ' ';
	//show[x + 1][y - 1] = ' ';
	//show[x ][y + 1] = ' ';
	//show[x ][y ] = ' ';
	//show[x ][y - 1] = ' ';
	//show[x - 1][y + 1] = ' ';
	//show[x - 1][y ] = ' ';
	//show[x - 1][y - 1] = ' ';
	int i ;
	int j ;
	//int count = 0;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			show[x+i][y+j] = ' ';
			int count = 0;
			count = get_mine_count(mine, x + i, y + j);
			if (count == 0)
			{
				SpreadBoard(mine,show, x+i, y+j);
			}
		}
	}
}
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0, y = 0;
	int win = 0;
	while (win<row*col-EASY_COUNT)
	{
		printf("请输入排查雷的坐标:\n");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (mine[x][y] == '1')
			{
				printf("很遗憾，您被炸死了\n");
				DisplayBoard(mine, row, col);
				break;
			}
			else
			{
				int count = get_mine_count(mine, x, y);
				while (count == 0)
				{
					int i;
					for (i = -1; i <= 1; i++)
					{
						if (count == 0)
						{
							SpreadBoard(mine,show, x+i, y+i);
							DisplayBoard(show, row, col);
							win += 9;
						}
					}
				}
				if (count == 0)
				{
					SpreadBoard(mine,show,x,y);
					DisplayBoard(show, row, col);
					win += 9;
				}
				else
				{
					show[x][y] = count + '0';
					DisplayBoard(show, row, col);
					win++;
				}
			}
		}
		else
		{
			printf("坐标错误，请重新输入：");
		}
	}
	if (win == row * col - EASY_COUNT)
	{
		printf("恭喜你胜利了\n");
		DisplayBoard(mine, row, col);
	}
}