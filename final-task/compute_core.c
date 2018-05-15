#include <stdio.h>
#include <string.h>
#include "consts.h"

int minimax(char x, char y, char chess[][15], char depth);
void generator(char chess[][15],char neighbors[][15]);
void flat(char chess[][15], char sequance[][15]);
int evaluate(char sequance[][15],char color);

void computer_do(char chess[][15])
{
	char neighbors[15][15] = { 0 };
	char sequance[72][15] = { '\0' };
	int scores[15][15] = { 0 };
	generator(chess, neighbors);
	//****************************************************************************************************************************************
}

void generator(char chess[][15], char neighbors[][15])
{
	int x, y, temp_x, temp_y;
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			//找到点
			x = i;
			y = j;
			if (chess[x][y] != empty)continue;    //排除已有棋子的位置
			//开始扫描周围2格内是否有棋子
			for (int k = -2; k < 2; k++)
			{
				for (int l = -NEIGHBOR_DEPTH; l < NEIGHBOR_DEPTH; l++)
				{
					temp_x = x + k;
					temp_y = y + l;
					if (temp_y < 0)continue;
					if (temp_x < 0)break;
					if (chess[temp_x][temp_y] != empty)
					{
						neighbors[x][y]++;
					}
				}
			}
		}
	}
}

void flat(char chess[][15], char sequance[][15])
{
	//横向序列
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			sequance[i][j] = chess[i][j];
		}
	}
	//纵向序列
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			sequance[i+15][j] = chess[j][i];
		}
	}
	//"/"这样的序列
	for (int i = 4; i < 14; i++)
	{
		for (int j = 0; j < i; j++)
		{
			sequance[i+30][j]=chess[j][i-j];
		}
	}
	for (int i = 1; i < 10; i++)
	{
		for (int j = 14; j > i; j--)
		{
			sequance[i + 41][j] = chess[i + 14 - j][j];
		}
	}
	//"\"这样的序列
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 14 - i; j++)
		{
			sequance[i + 51][j] = chess[i + j][j];
		}
	}
	for (int i = 1; i < 10; i++)
	{
		for (int j = 0; j < 14 - i; j++)
		{
			sequance[i + 62][j] = chess[j][i + j];
		}
	}
}

int evaluate(char sequance[][15],char color)
{
	int score;
	char chenwu[5] = { color,color,color,color,color };
	char huosi1[]//***************************************************************************************************************************8
	for (int i = 0; i < 71; i++)
	{
		strstr(sequance[i][],)
	}
}