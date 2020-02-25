#include "header.h"

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
	
	int last_column = 0;
	
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
			// Reset board on new game
			board_create(board);
			game = 0;
			turn = 0;
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
					printf("\n-------------------------------\n");
					printf("-------- PLAYER 1 TURN --------\n");
					// Place the token and save the column for undo function
					last_column = place_token(board, player_one);
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
						for (int row = 0; row <= 5; row++)
						{
							// Find the top-most token placed for the given column
							if (board[row][last_column].token == player_one.token)
							{
								// Swap it with a dash
								board[row][last_column].token = DASH;
								break;
							}
						}
					}
					system("cls");
					
					
					// Check if four connect somewhere
					win1 = vertical_checker(board, player_one) + horizontal_checker(board, player_one) + diagonal_checker(board, player_one);
					if (win1 > 0)
					{
						// Print message to the winner
						printf("\n-------------------------------\n");
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
							turn = 0;
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
					// Switch to Player Two
					turn = 1;
					answer = 0;
				}
				// PLAYER 2
				else
				{
					printf("\n-------------------------------\n");
					printf("-------- PLAYER 2 TURN --------\n");
					// Place the token and save the column for undo function
					last_column = place_token(board, player_two);
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
						for (int row = 0; row <= 5; row++)
						{
							// Find the top-most token placed for the given column
							if (board[row][last_column].token == player_two.token)
							{
								// Swap it with a dash
								board[row][last_column].token = DASH;
								break;
							}
						}
					}
					
					system("cls");
					// Check if four connect somewhere
					win2 = vertical_checker(board, player_two) + horizontal_checker(board, player_two) + diagonal_checker(board, player_two);
					if (win2 > 0)
					{
						// Print message to the winner
						printf("\n-------------------------------\n");
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
							turn = 0;
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
					// Switch to Player One
					turn = 0;
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
