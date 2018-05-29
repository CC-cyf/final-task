#include <stdio.h>
#include <string.h>
#include "consts.h"

void computer_do(char chess[][15])
{
	char position[2];
	calculator(chess, DEPTH, position);
	chess[position[0]][position[1]] = computer_color;
}

int calculator(char chess[][15],char depth,char position[2])
{
	if (depth == 0) return 0;

	char chess_temp[15][15];
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			chess_temp[i][j] = chess[i][j];
		}
	}
	char neighbors[15][15] = { 0 };
	char sequance[72][16] = { '\0' };
	char position_temp[2];
	int scores[15][15] = { 0 };
	generator(chess, neighbors);
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (neighbors[i][j] != 0)
			{
				chess_temp[i][j] = computer_color;
				flat(chess_temp, sequance);
				scores[i][j] = evaluate(sequance);
				neighbors[i][j] = 0;
				calculator(chess_temp, depth - 1, position_temp);
			}
		}
	}
	if (depth == DEPTH)
	{
		int max = 0;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				max = max > scores[i][j] ? max : scores[i][j];
				position[0] = i;
				position[1] = j;
			}
		}
	}
	//****************************************************************************************************************************************
	return 0;
}

void generator(char chess[][15], char neighbors[][15])
{
	int x, y, temp_x, temp_y;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			//找到点
			x = i;
			y = j;
			if (chess[x][y] != empty)continue;    //排除已有棋子的位置
			//开始扫描周围2格内是否有棋子
			for (int k = -NEIGHBOR_DEPTH; k <= NEIGHBOR_DEPTH; k++)
			{
				for (int l = -NEIGHBOR_DEPTH; l <= NEIGHBOR_DEPTH; l++)
				{
					temp_x = x + k;
					temp_y = y + l;
					if (temp_y < 0)continue;
					if (temp_x < 0)break;
					if (temp_y > 14)continue;
					if (temp_x > 14)break;
					if (chess[temp_x][temp_y] != empty)
					{
						neighbors[x][y]++;
					}
				}
			}
		}
	}
}

void flat(char chess[][15], char sequance[][16])
{
	//横向序列
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			sequance[i][j] = chess[i][j];
		}
	}
	//纵向序列
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			sequance[i+15][j] = chess[j][i];
		}
	}
	//"/"这样的序列
	for (int i = 4; i < 15; i++)
	{
		for (int j = 0; j < i; j++)
		{
			sequance[i+30][j]=chess[j][i-j];
		}
	}
	for (int i = 1; i < 11; i++)
	{
		for (int j = 14; j > i; j--)
		{
			sequance[i + 41][j] = chess[i + 14 - j][j];
		}
	}
	//"\"这样的序列
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 14 - i; j++)
		{
			sequance[i + 51][j] = chess[i + j][j];
		}
	}
	for (int i = 1; i < 11; i++)
	{
		for (int j = 0; j < 14 - i; j++)
		{
			sequance[i + 62][j] = chess[j][i + j];
		}
	}
}

int evaluate(char sequance[][16])	//只对电脑的棋子评估
{
	int score = 0;
	//100000分
	char chenwu[5] = { computer_color,computer_color,computer_color,computer_color,computer_color };
	//10000分
	char huosi1[6] = { empty,computer_color,computer_color,computer_color,computer_color,empty };
	char huosi2[5] = { computer_color,empty,computer_color,computer_color,computer_color };
	char huosi3[5] = { computer_color,computer_color,empty,computer_color,computer_color };
	char huosi4[5] = { computer_color,computer_color,computer_color,empty,computer_color };
	//1000分
	char sisi1[6] = { empty,computer_color,computer_color,computer_color,computer_color,player_color };
	char sisi2[6] = { player_color,computer_color,computer_color,computer_color,computer_color,empty };
	char huosan[5] = { empty,computer_color,computer_color,computer_color,empty };
	//100分
	char sisan1[5] = { empty,computer_color,computer_color,computer_color,player_color };
	char sisan2[5] = { player_color,computer_color,computer_color,computer_color,empty };
	char huoer[4] = { empty,computer_color,computer_color,empty };
	//10分
	char sier1[4] = { empty,computer_color,computer_color,player_color };
	char sier2[4] = { player_color,computer_color,computer_color,empty };
	char huoyi[3] = { empty,computer_color,empty };
	//***************************************************************************************************************************8
	for (int i = 0; i < 71; i++)
	{
		//100000
		score += 100000 * find(sequance[i], chenwu, 5);
		//10000
		score += 10000 * find(sequance[i], huosi1, 6);
		score += 10000 * find(sequance[i], huosi2, 5);
		score += 10000 * find(sequance[i], huosi3, 5);
		score += 10000 * find(sequance[i], huosi4, 5);
		//1000
		score += 1000 * find(sequance[i], sisi1, 6);
		score += 1000 * find(sequance[i], sisi2, 6);
		score += 1000 * find(sequance[i], huosan, 5);
		//100
		score += 100 * find(sequance[i], sisan1, 5);
		score += 100 * find(sequance[i], sisan2, 5);
		score += 100 * find(sequance[i], huoer, 4);
		//10
		score += 10 * find(sequance[i], sier1, 4);
		score += 10 * find(sequance[i], sier2, 4);
		score += 10 * find(sequance[i], huoyi, 3);
	}
	return score;
}

char find(char place[16], char goal[],char length)
{
	char times_show_up = 0;
	_Bool temp;
	for (int i = 0; i < 16-length; i++)
	{
		temp = 1;
		for (int j = 0; j < length; j++)
		{
			if (place[i + j] != goal[j])
			{
				temp = 0;
			}
		}
		if (temp == 1)
		{
			times_show_up++;
		}
	}
	return times_show_up;
}