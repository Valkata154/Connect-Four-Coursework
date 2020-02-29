#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> 
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define ROW 6
#define COL 7

#define DASH '-'

#define PLAYER1 'O'
#define PLAYER2 'X'

# define MAX 42

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

void display (int *array);
void init(int array[][MAX]);
void reverse (int *array);
void insert(int *array , int pos , int num);
void place_token_2(Board board[][COL], Box player, int column);
int place_token_pop_ten(Board board[][COL], Box player, int r);
void remove_token(Board board[][COL], Box player, int column);
int place_token_bot(Board board[][COL], int column, int difficulty);

