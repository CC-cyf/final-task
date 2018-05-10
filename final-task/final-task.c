#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
#define DEPTH 3    //需为奇数
#define KILL_DEPTH 5    //需为奇数

void draw(char chess[][15]);
void computer_do(char chess[][15]);
//_Bool if_leagal(char chess[][15], int x, int y);
char winner(char chess[][15]);
enum chesses { empty, white, black };

int main()
{
	char n1, n2, player_color,computer_color;
	int chess_num=0;
	system("mode con cols=50 lines=22");
	char chess[15][15] = {0};
reinput_color:
	draw(chess);
	printf("请输入您所控制的棋子颜色:\n1.白色（后手）\n2.黑色（先手）\n");
	scanf("%d",&player_color);
	fflush(stdin);
	if (player_color != white && player_color != black)
	{
		printf("输入错误！\n");
		goto reinput_color;
	}
	computer_color = 3 - player_color;
	if (chess_num == 0 && player_color == white)
	{
		chess[7][7] = computer_color;
		chess_num++;
	}
	while (winner(chess) == empty)
	{
	reinput_position:
		draw(chess);
		printf("请输入行号（0-14）：");
		scanf("%d",&n1);
		fflush(stdin);
		getchar();
		if (n1 > 14)
		{
			printf("错误行号！！！");
			getchar();
			goto reinput_position;
		}
		printf("\n请输入列号（a-o）：");
		scanf("%c", &n2);
		fflush(stdin);
		getchar();
		if (n2 > 'o'||n2<'a')
		{
			printf("错误列号！！！");
			getchar();
			goto reinput_position;
		}
		/*if (chess_num == 1 && if_leagal(chess, n1, n2 - 'a') == false)//玩家白子
		{
			printf("犯规！！！");
			getchar();
			goto reinput_position;
		}*/
		if(chess[n1][n2-'a'] == empty)
		{
			chess[n1][n2 - 'a'] = player_color;
			chess_num++;
		}
		else
		{
			printf("该位置已经被占用！！！");
			getchar();
			goto reinput_position;
		}
		draw(chess);
		computer_do(chess);
	}
	system("pause");
}

void draw(char chess[][15])
{
	system("cls");
	printf("\t");
	for (int i = 0; i < 15; i++)
	{
		printf("%c ",'a'+i);
	}
	printf("\n");
	for (int i = 0; i < 15; i++)
	{
		printf("%d\t", i);
		for (int j = 0; j < 15; j++)
		{
			if (chess[i][j] == empty)
			{
				printf("+ ");
			}
			else
			{
				printf("%c ",chess[i][j]);
			}
		}
		printf("\n");
	}
}


char winner(char chess[][15])
{
	char white_num, black_num;
	//横向查找
	for (int i = 0; i < 14; i++)
	{
		white_num = 0;
		black_num = 0;
		for (int j = 0; j < 14; j++)
		{
			if (chess[i][j] == white)
			{
				white_num++;
				black_num = 0;
			}
			else if (chess[i][j] == black)
			{
				black_num++;
				white_num = 0;
			}
			else
			{
				white_num = 0;
				black_num = 0;
			}
			if (black_num == 5)return black;
			if (white_num == 5)return white;
		}
	}
	//纵向查找
	for (int i = 0; i < 14; i++)
	{
		white_num = 0;
		black_num = 0;
		for (int j = 0; j < 14; j++)
		{
			if (chess[j][i] == white)
			{
				white_num++;
				black_num = 0;
			}
			else if (chess[j][i] == black)
			{
				black_num++;
				white_num = 0;
			}
			else
			{
				white_num = 0;
				black_num = 0;
			}
			if (black_num == 5)return black;
			if (white_num == 5)return white;
		}
	}
	//"/"这样查找
	for (int i = 5; i < 14; i++)
	{
		white_num = 0;
		black_num = 0;
		for (int j = 0; j < i; j++)
		{
			if (chess[j][i-j] == white)
			{
				white_num++;
				black_num = 0;
			}
			else if (chess[j][i-j] == black)
			{
				black_num++;
				white_num = 0;
			}
			else
			{
				white_num = 0;
				black_num = 0;
			}
		if (black_num == 5)return black;
		if (white_num == 5)return white;
		}
	}
	for (int i = 1; i < 9; i++)
	{
		white_num = 0;
		black_num = 0;
		for (int j = 14; j > i; j--)
		{
			if (chess[i+14-j][j] == white)
			{
				white_num++;
				black_num = 0;
			}
			else if (chess[i+14-j][j] == black)
			{
				black_num++;
				white_num = 0;
			}
			else
			{
				white_num = 0;
				black_num = 0;
			}
			if (black_num == 5)return black;
			if (white_num == 5)return white;
		}
	}
	//"\"这样查找
	for (int i = 0; i < 9; i++)
	{
		white_num = 0;
		black_num = 0;
		for (int j = 0; j < 14 - i; j++)
		{
			if (chess[i+j][j] == white)
			{
				white_num++;
				black_num = 0;
			}
			else if (chess[i+j][j] == black)
			{
				black_num++;
				white_num = 0;
			}
			else
			{
				white_num = 0;
				black_num = 0;
			}
			if (black_num == 5)return black;
			if (white_num == 5)return white;
		}
	}
	for (int i = 1; i < 9; i++)
	{
		white_num = 0;
		black_num = 0;
		for (int j = 0; j < 14 - i; j++)
		{
			if (chess[j][i+j] == white)
			{
				white_num++;
				black_num = 0;
			}
			else if (chess[j][i+j] == black)
			{
				black_num++;
				white_num = 0;
			}
			else
			{
				white_num = 0;
				black_num = 0;
			}
			if (black_num == 5)return black;
			if (white_num == 5)return white;
		}
	}
}

/*_Bool if_leagal(char chess[][15], int x, int y)
{

}*/