#include <stdio.h>
#include <string.h>

#define ROW 6
#define COL 7

#define DASH '-'

#define PLAYER1 'O'
#define PLAYER2 'X'


typedef struct box
{
	char token;
	int row;
	int col;
} Box;


typedef struct board
{
	char token;
	int row;
	int col;
}Board;

void menu();
void rules();
void place_token(Board board[][COL], Box player);
void board_display(Board board[][COL]);
void board_create(Board board[][COL]);

