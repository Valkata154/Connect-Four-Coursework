/*
*
*  @author: Valeri Vladimirov 40399682
*  Last Modified: 25/02/2019
*  Purpose: Connect Four game implementation in C.
*  Functionality: Add piece, check for connection of four,
*  undo move, play again.
*
*/

#include "header.h"

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
	printf("To win a game, you have to have 4 tokens connecting\n");
	printf("in any direction without interruption.\n");
	printf("Hope you have fun while playing!\n");
	printf("Good luck!\n");
	printf("\n----------------------------------------------------\n");
	// Pause for the user to read and then clear
	system("pause");
	system("cls");
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

int main(void)
{
   
	// Variables
	int quit = 0;
	int choice = 0;
	int game = 0;
	int turn = 0;
	int answer = 0;
	int win1 = 0;
	int win2 = 0;
	int restart = 0;
	int player1_score = 0;
	int player2_score = 0;
	int last_column = 0;
	struct Stack* stack = createStack(100);
	
	Board board[ROW][COL] = { '\0' };
	Box player_one = { '/0' };
	Box player_two = { '/0' };

	// Initialize tokens
	player_one.token = PLAYER1;
	player_two.token = PLAYER2;
	
	// Fill the board with dashes (meaning the cells are empty)
	board_create(board);
	
	while(quit==0)
	{
		// Display the menu
		menu();
		// Get user input 
		printf("Enter selection: ");
		scanf("%d", &choice);
		// Clear the screen
		system("cls");
		
		// Switch statement for the menu
		switch (choice)
		{
		// Start the game
		case 1:
			// Reset board and variables on new game
			board_create(board);
			game = 0;
			turn = 0;
			player2_score = 0;
			player1_score = 0;
			printf("\n-------------------------------\n");
			printf("--------- GAME STARTED --------\n");
			printf("-------------------------------\n\n");
			// Display board
			board_display(board);
			system("pause");
			system("cls");
			// While playing switch turns between players until someone wins
			while (game == 0)
			{
				// PLAYER 1
				if (turn == 0)
				{
					// Switch to Player Two
					turn = 1;
					// Display score
					printf("---------- SCORE --------------\n");
					printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
					printf("-------------------------------\n");
					printf("-------------------------------\n");
					printf("-------- PLAYER 1 TURN --------\n");
					// Place the token and save the column in the stack for undo function
					push(stack, place_token(board, player_one)); 
					system("cls");
					printf("-------------------------------\n\n");
					// Display the board
					board_display(board);
					printf("-------------------------------\n\n");
					
					
					// Ask the user if they want to undo their move
					printf("Do you want to undo your move?\nType: 1 for YES and 0 for NO\n");
					scanf("%d", &answer);
					// If yes find the box
					if(answer == 1)
					{
						// Ask user if they want to undo
						printf("Type 1 if you want to undo ONLY YOUR TURN\nor 2 if you want to undo MORE THAN ONCE.\n");
						scanf("%d", &answer);
						if (answer == 1)
						{
							// Find the last put item in the given column and row
							for (int row = 0; row <= 5; row++)
							{
								// Find the top-most token placed for the given column
								if (board[row][peek(stack)].token == player_one.token)
								{
									// Swap it with a dash
									board[row][peek(stack)].token = DASH;
									pop(stack);
									turn = 0;
									break;
								}
							}
						}
						else
						{
							// Ask how many turns to go back and pop and change elements multiple times
							int num;
							printf("How many turns do you want to go back?\n");
							scanf("%d", &num);
							for(int i = 0; i < num; i++)
							{
								for (int row = 0; row <= 5; row++)
								{
									// Find the top-most token placed for the given column
									if (board[row][peek(stack)].token == player_one.token || board[row][peek(stack)].token == player_two.token)
									{
										// Swap it with a dash
										board[row][peek(stack)].token = DASH;
										pop(stack);
										break;
									}
								}
							}
							
							// Check to which players belongs  the last element to figure out which turn to play
							for (int row = 0; row <= 5; row++)
							{
								if (board[row][peek(stack)].token == player_one.token)
								{
									turn = 1;
								}
								else
								{
									turn = 0;
								}
							}
						}
					}
					system("cls");
					
					
					// Check if four connect somewhere
					win1 = vertical_checker(board, player_one) + horizontal_checker(board, player_one) + diagonal_checker(board, player_one);
					if (win1 > 0)
					{
						// Increment  and display the score
						player1_score++;
						printf("---------- SCORE --------------\n");
						printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
						printf("-------------------------------\n");
						// Print message to the winner
						printf("-------------------------------\n");
						printf("--- PLAYER 1 IS THE WINNER! ---\n");
						printf("-------------------------------\n\n");
						// Display the board
						board_display(board);
						printf("-------------------------------\n\n");
						system("pause");
						
						// Ask the user if they want to restart
						system("cls");
						printf("---------------\n");
						printf("Play again?\n");
						printf("Type 1 for YES\n");
						printf("Type 2 for NO\n");
						printf("---------------\n\n");
						scanf("%d", &restart);
						system("cls");
						if (restart == 2)
						{
							game = 1;
						}
						if (restart == 1)
						{
							// Reset the board and variables
							win1 = 0;
							board_create(board);
							// Display the board
							printf("\n-------------------------------\n");
							printf("------- RESTARTING GAME -------\n");
							printf("-------------------------------\n\n");
							board_display(board);
							printf("-------------------------------\n\n");
							system("pause");
							system("cls");
						}
					}
					answer = 0;
				}
				// PLAYER 2
				else
				{
					// Switch to Player One
					turn = 0;
					// Display score
					printf("---------- SCORE --------------\n");
					printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
					printf("-------------------------------\n");
					printf("-------------------------------\n");
					printf("-------- PLAYER 2 TURN --------\n");
					// Place the token and save the column in the stack for undo function
					push(stack, place_token(board, player_two));
					system("cls");
					printf("-------------------------------\n\n");
					// Display the board
					board_display(board);
					printf("-------------------------------\n\n");
					
					
					// Ask the user if they want to undo their move
					printf("Do you want to undo your move?\nType: 1 for YES and 0 for NO\n");
					scanf("%d", &answer);
					// If yes find the box
					if(answer == 1)
					{
						// Ask user if they want to undo
						printf("Type 1 if you want to undo ONLY YOUR TURN\nor 2 if you want to undo MORE THAN ONCE.\n");
						scanf("%d", &answer);
						if (answer == 1)
						{
							// Find the last put item in the given column and row
							for (int row = 0; row <= 5; row++)
							{
								// Find the top-most token placed for the given column
								if (board[row][peek(stack)].token == player_two.token)
								{
									// Swap it with a dash
									board[row][peek(stack)].token = DASH;
									pop(stack);
									turn = 1;
									break;
								}
							}
						}
						else
						{
							// Ask how many turns to go back and pop and change elements multiple times
							int num;
							printf("How many turns do you want to go back?\n");
							scanf("%d", &num);
							for(int i = 0; i < num; i++)
							{
								for (int row = 0; row <= 5; row++)
								{
									// Find the top-most token placed for the given column
									if (board[row][peek(stack)].token == player_one.token || board[row][peek(stack)].token == player_two.token)
									{
										// Swap it with a dash
										board[row][peek(stack)].token = DASH;
										pop(stack);
										break;
									}
								}
							}
							
							// Check to which players belongs  the last element to figure out which turn to play
							for (int row = 0; row <= 5; row++)
							{
								if (board[row][peek(stack)].token == player_two.token)
								{
									turn = 0;
								}
								else
								{
									turn = 1;
								}
							}
						}
					}
					system("cls");
					
					// Check if four connect somewhere
					win2 = vertical_checker(board, player_two) + horizontal_checker(board, player_two) + diagonal_checker(board, player_two);
					if (win2 > 0)
					{
						// Display and increment score
						player2_score++;
						printf("---------- SCORE --------------\n");
						printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
						printf("-------------------------------\n");
						// Print message to the winner
						printf("-------------------------------\n");
						printf("--- PLAYER 2 IS THE WINNER! ---\n");
						printf("-------------------------------\n\n");
						// Display the board
						board_display(board);
						printf("-------------------------------\n\n");
						system("pause");
						
						// Ask the user if they want to restart
						system("cls");
						printf("---------------\n");
						printf("Play again?\n");
						printf("Type 1 for YES\n");
						printf("Type 2 for NO\n");
						printf("---------------\n\n");
						scanf("%d", &restart);
						system("cls");
						if (restart == 2)
						{
							game = 1;
						}
						if (restart == 1)
						{
							// Reset the board and variables
							win2 = 0;
							board_create(board);
							// Display the board
							printf("\n-------------------------------\n");
							printf("------- RESTARTING GAME -------\n");
							printf("-------------------------------\n\n");
							board_display(board);
							printf("-------------------------------\n\n");
							system("pause");
							system("cls");
						}
					}
					answer = 0;
				}
			}
			break;
		
		// Display the rules
		case 2:
			rules();
			break;
		
		// Exit the game
		case 3:
			printf("Exiting Game...");
			// Clear the screen
			system("cls");
			quit = 1;
			break;
		}
			
	}	
	return 0;
}
