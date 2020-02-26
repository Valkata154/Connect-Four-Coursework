#include "header.h"

/*
*  STACK FUNCTIONS
*/

//  Function to create a stack of given capacity.
struct Stack* createStack(unsigned capacity) 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*)malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 
  
// Function to find whether stack is full
int isFull(struct Stack* stack) 
{ 
    return stack->top == stack->capacity - 1; 
} 
  
// Function to find whether stack is empty
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1; 
} 
  
// Function to add an item to stack.
void push(struct Stack* stack, int item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
} 
  
// Function to remove an item from stack.
int pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
} 
  
// Function to return the top from stack without removing it 
int peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top]; 
} 

/*
*  CHECKING FUNCTIONS
*/

// Method to check diagonally for a winner
int diagonal_checker(Board board[][COL], Box player)
{
	int occurances = 0;
	
	// From LEFT to RIGHT go through each column
	for (int column = 0; column <= 6; column++)
	{
		// Go through each row
		for (int row = 5; row >= 0; row--)
		{
			// Check the diagonal boxes if they connect
			for (int i = 0; i < 4; i++)
			{
				if (board[row - i][column + i].token == player.token)
				{
					occurances = occurances + 1;
				}
				// If 4 connected return that there is a winner
				if (occurances == 4)
				{
					return 1;
				}
			}
			// If less than 4 reset the occurances
			if (occurances < 4)
			{
				occurances = 0;
			}
		}
	}

	// From RIGHT to LEFT go through each column
	for (int column = 6; column >= 0; column--)
	{
		// Go through each row
		for (int row = 5; row >= 0; row--)
		{
			// Check the diagonal boxes if they connect
			for (int i = 0; i < 4; i++)
			{
				if (board[row - i][column - i].token == player.token)
				{
					occurances = occurances + 1;
				}
				// If 4 connected return that there is a winner
				if (occurances == 4)
				{
					return 1;
				}
			}
			// If less than 4 reset the occurances
			if (occurances < 4)
			{
				occurances = 0;
			}
		}
	}
	return 0;
}

// Method to check horizontally for a winner
int horizontal_checker(Board board[][COL], Box player)
{
	int occurances = 0;

	// Go through each row
	for (int row = 5; row >= 0; row--)
	{
		// Go through each column
		for (int column = 6; column >= 0; column--)
		{
			// Check the side boxes if they connect
			for (int i = 0; i < 4; i++)
			{
				if (board[row][column - i].token == player.token)
				{
					occurances = occurances + 1;
				}
				// If 4 connected return that there is a winner
				if (occurances == 4)
				{
					return 1;
				}
			}
			// If less than 4 reset the occurances
			if (occurances < 4)
			{
				occurances = 0;
			}
		}
	}
	return 0;
}

// Method to check vertically for a winner
int vertical_checker(Board board[][COL], Box player)
{
	int occurances = 0;

	// Go through each column
	for (int column = 6; column >= 0; column--)
	{
		// Go through each row
		for (int row = 5; row >= 0; row--)
		{
			// Check the lower boxes if they connect
			for (int i = 0; i < 4; i++)
			{
				if (board[row - i][column].token == player.token)
				{
					occurances = occurances + 1;
				}
				// If 4 connected return that there is a winner
				if (occurances == 4)
				{
					return 1;
				}
			}
			// If less than 4 reset the occurances
			if (occurances < 4)
			{
				occurances = 0;
			}
		}
	}
	return 0;
}

// Method to place token in the board
int place_token(Board board[][COL], Box player)
{
	int column = 0;
	int quit = 0;
	
	// Show the board after token has been placed
	printf("-------------------------------\n\n");
	board_display(board);
	printf("-------------------------------\n\n");

	while (quit == 0)
	{
		// Read user input for column
		printf("Enter column number below:\n");
		scanf("%d", &column);
		
		if(column < 0 || column > 6)
		{
			printf("\nERROR - Invalid Number!\n");
			printf("Please enter a number between 0 and 6.\n\n");
		}
		else
		{
			// Place the token at the given column in the lowest available row
			for (int row = ROW; row >= 0; row--)
			{
				// Check if box is available
				if (board[row][column].token == DASH)
				{
					board[row][column].token = player.token;
					quit = 1;
					break;
				}
			}
		}
	}
	
	// Return the column for undo function
	return column;
}

/*
*  BOARD FUNCTIONS
*/

// Method to initialize the empty board with dashes
void board_create(Board board[][COL])
{
	// Go through all rows and columns and add a dash
	for (int row = 0; row < ROW; row++)
	{
		for (int column = 0; column < COL; column++)
		{
			board[row][column].token = DASH;
		}
	}
}

// Method to display the board
void board_display(Board board[][COL])
{
	// Print numbers
	printf("  | 0 | 1 | 2 | 3 | 4 | 5 | 6 |\n\n");
	// Go through all rows and columns and print them
	for (int row = 0; row < ROW; row++)
	{
		// Print number on the side
		printf("%d ", row);
		for (int column = 0; column < COL; column++)
		{
			// If statement in order to print side line on the last iteration
			if(column < COL - 1)
			{	
				printf("| %c ", board[row][column]);
			}
			else
			{
				printf("| %c |", board[row][column]);
			}
		}
		printf("\n\n");
	}
}

/*
*  DISPLAY FUNCTIONS
*/

// Rules method to display all the rules the players have to follow
void rules()
{
	// Display rules
	printf("\n----------------------------------------------------\n\n");
	printf("This is a two player game in a terminal.\n");
	printf("You can play versus your friend.\n");
	printf("Everyone takes turns to drop down tokens.\n");
	printf("After you drop a piece you will be asked,\n");
	printf("if you want to undo your move.\n");
	printf("You can make one or multiple redo's.\n");
	printf("To win a game, you have to have 4 tokens connecting\n");
	printf("in any direction without interruption.\n");
	printf("Hope you have fun while playing!\n");
	printf("Good luck!\n");
	printf("\n----------------------------------------------------\n");
	// Pause for the user to read and then clear
	system("pause");
	system("cls");
}

void credits()
{
	// Display credits
	printf("\n----------------------------------------------------\n\n");
	printf("Game Created By: Valeri Vladimirov\n");
	printf("Matriculation Number: 40399682\n");
	printf("Email: valkata154@gmail.com\n");
	printf("Github: valkata154\n");
	printf("Thank you for playing the game!\n");
	printf("I hope you liked it!\n");
	printf("Exiting game...\n");
	printf("\n----------------------------------------------------\n");
}

// Menu method to display all the options for the players
void menu()
{
	// Clear the screen and display the menu
	system("cls");
	printf("\n-----------------------\n");
	printf("-- Connect Four Game --\n");
	printf("-----------------------\n\n");
	printf("MENU:\n\n");
	printf("[1] START GAME\n");
	printf("[2] RULES\n");
	printf("[3] QUIT\n");
}
