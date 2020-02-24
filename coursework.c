#include "header.h"

// Method to place token in the board
void place_token(Board board[][COL], Box player)
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
				if (turn == 0)
				{
					printf("\n-------------------------------\n");
					printf("-------- PLAYER 1 TURN --------\n");
					// Place the token
					place_token(board, player_one);
					system("cls");
					printf("-------------------------------\n\n");
					// Display the board
					board_display(board);
					printf("-------------------------------\n\n");
					system("cls");
					// Switch to Player Two
					turn = 1;
				}
				else
				{
					printf("\n-------------------------------\n");
					printf("-------- PLAYER 2 TURN --------\n");
					// Place the token
					place_token(board, player_two);
					system("cls");
					printf("-------------------------------\n\n");
					// Display the board
					board_display(board);
					printf("-------------------------------\n\n");
					system("cls");
					// Switch to Player One
					turn = 0;
				}
			}
		
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
