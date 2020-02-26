#include <stdio.h>
#include <string.h>
#include <limits.h> 

#define ROW 6
#define COL 7

#define DASH '-'

#define PLAYER1 'O'
#define PLAYER2 'X'

struct Stack { 
    int top; 
    unsigned capacity; 
    int* array; 
}; 

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
void credits();
int place_token(Board board[][COL], Box player);
void board_display(Board board[][COL]);
void board_create(Board board[][COL]);
int vertical_checker(Board board[][COL], Box player);
int horizontal_checker(Board board[][COL], Box player);
int diagonal_checker(Board board[][COL], Box player);
struct Stack* createStack(unsigned capacity);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int peek(struct Stack* stack);

