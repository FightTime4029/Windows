#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define eazy_count 10


void Initboard(char board[ROWS][COLS], int row, int col, char set);//初始化数组
void DisplayBoard(char board[ROWS][COLS], int row, int col);//打印数组
void SetMine(char board[ROWS][COLS], int row, int col);//放置雷
int Fined_Mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);//找到雷