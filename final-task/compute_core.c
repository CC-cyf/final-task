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
	int score = 0;
	//100000分
	char chenwu[5] = { color,color,color,color,color };
	//10000分
	char huosi1[6] = { empty,color,color,color,color,empty };
	char huosi2[5] = { color,empty,color,color,color };
	char huosi3[5] = { color,color,empty,color,color };
	char huosi4[5] = { color,color,color,empty,color };
	//1000分
	char sisi1[6] = { empty,color,color,color,color,3 - color };
	char sisi2[6] = { 3 - color,color,color,color,color,empty };
	char huosan[5] = { empty,color,color,color,empty };
	//100分
	char sisan1[5] = { empty,color,color,color,3 - color };
	char sisan2[5] = { 3 - color,color,color,color,empty };
	char huoer[4] = { empty,color,color,empty };
	//10分
	char sier1[4] = { empty,color,color,3 - color };
	char sier2[4] = { 3 - color,color,color,empty };
	char huoyi[3] = { empty,color,empty };
	//***************************************************************************************************************************8
	for (int i = 0; i < 71; i++)
	{
		//100000
		if (strstr(sequance[i], chenwu)) score += 100000;
		//10000
		if (strstr(sequance[i], huosi1)) score += 10000;
		if (strstr(sequance[i], huosi2)) score += 10000;
		if (strstr(sequance[i], huosi3)) score += 10000;
		if (strstr(sequance[i], huosi4)) score += 10000;
		//1000
		if (strstr(sequance[i], sisi1)) score += 1000;
		if (strstr(sequance[i], sisi2)) score += 1000;
		if (strstr(sequance[i], huosan)) score += 1000;
		//100
		if (strstr(sequance[i], sisan1)) score += 100;
		if (strstr(sequance[i], sisan2)) score += 100;
		if (strstr(sequance[i], huoer)) score += 100;
		//10
		if (strstr(sequance[i], sier1)) score += 10;
		if (strstr(sequance[i], sier2)) score += 10;
		if (strstr(sequance[i], huoyi)) score += 10;
	}
	return score;
}