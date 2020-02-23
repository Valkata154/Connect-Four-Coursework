#include <stdio.h>
#include <string.h>

#define ROW 6
#define COL 7

#define DASH '-'

typedef struct board
{
	char token;
	int row;
	int col;
}Board;

void menu();
void rules();
void board_display(Board board[][COL]);
void board_create(Board board[][COL]);

