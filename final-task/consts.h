#pragma once

#define false 0
#define true 1
#define DEPTH 1    //需为奇数
#define KILL_DEPTH 7    //需为奇数
#define NEIGHBOR_DEPTH 2

int player_color,computer_color;

//为防止strstr函数不能按预期工作，故empty取1
enum chesses { empty = 1, white, black };

//main.c
void draw(char chess[][15]);
char winner(char chess[][15]);

//compute_core.c
void computer_do(char chess[][15]);
void generator(char chess[][15], char neighbors[][15]);
void flat(char chess[][15], char sequance[][16]);
int evaluate(char sequance[][16]);
int calculator(char chess[][15], char depth, char position[2]);
char find(char place[16], char goal[], char length);