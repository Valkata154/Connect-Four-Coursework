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

int main(void)
{
   
	// Variables
	int quit = 0;
	int choice = 0;
	int game = 0;
	int turn = 0;
	int answer = 0;
	int answer_other = 0;
	int win1 = 0;
	int win2 = 0;
	int restart = 0;
	int player1_score = 0;
	int player2_score = 0;
	int last_column = 0;
	struct Stack* stack = createStack(100);
	int stackItems = 0;
	int arrayTemp[MAX];
	
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
				stackItems = 0;
				arrayTemp[MAX];
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
							struct Stack* tempStack = createStack(100);
							// Find the last put item in the given column and row
							for (int row = 0; row <= 5; row++)
							{
								// Find the top-most token placed for the given column
								if (board[row][peek(stack)].token == player_one.token)
								{
									// Swap it with a dash
									board[row][peek(stack)].token = DASH;
									push(tempStack, pop(stack));
									turn = 0;
									break;
								}
							}
							// Show the board and ask if user is happy with changes
							system("cls");
							printf("-------------------------------\n\n");
							board_display(board);
							printf("-------------------------------\n");
							printf("Are you happy with the change?\nType: 1 if yes\nType: 2 to redo\n");
							scanf("%d", &answer_other);
							// If not redo the changes
							if(answer_other == 2)
							{
								// Pop from temp stack to save last value
								int col = pop(tempStack);
								// Push the value to the actual stack
								push(stack, col);
								// Place the token
								place_token_2(board, player_one, col);
								turn = 1;
							}
						}
						else
						{
							// Create temp stack to store popped values
							struct Stack* tempStack = createStack(100);
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
										// When popping add to temp stack
										push(tempStack, pop(stack));
										break;
									}
								}
							}
							
							// Show the board and ask if user is happy with changes
							system("cls");
							printf("-------------------------------\n\n");
							board_display(board);
							printf("-------------------------------\n");
							printf("Are you happy with the changes?\nType: 1 if yes\nType: 2 to redo\n");
							scanf("%d", &answer_other);
							// If not redo all the changes
							if(answer_other == 2)
							{
								for(int i = 0; i < num; i++)
								{
									// Pop from temp stack to save last value
									int col = pop(tempStack);
									// Push to the actual stack
									push(stack, col);
									// Decide which player token to place and place it 
									if(i % 2 == 0){
										place_token_2(board, player_one, col);
									}
									else
									{
										place_token_2(board, player_two, col);
									}
							
								}
								turn = 1;
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
						
						game = 1;
						
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
							struct Stack* tempStack = createStack(100);
							// Find the last put item in the given column and row
							for (int row = 0; row <= 5; row++)
							{
								// Find the top-most token placed for the given column
								if (board[row][peek(stack)].token == player_two.token)
								{
									// Swap it with a dash
									board[row][peek(stack)].token = DASH;
									push(tempStack, pop(stack));
									turn = 1;
									break;
								}
							}
							// Show the board and ask if user is happy with changes
							system("cls");
							printf("-------------------------------\n\n");
							board_display(board);
							printf("-------------------------------\n");
							printf("Are you happy with the change?\nType: 1 if yes\nType: 2 to redo\n");
							scanf("%d", &answer_other);
							// If not redo the changes
							if(answer_other == 2)
							{
								// Pop from temp stack to save last value
								int col = pop(tempStack);
								// Push the value to the actual stack
								push(stack, col);
								// Place the token
								place_token_2(board, player_two, col);
								turn = 0;
							}
						}
						else
						{
							// Create temp stack to store popped values
							struct Stack* tempStack = createStack(100);
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
										// When popping add to temp stack
										push(tempStack, pop(stack));
										break;
									}
								}
							}
							
							// Show the board and ask if user is happy with changes
							system("cls");
							printf("-------------------------------\n\n");
							board_display(board);
							printf("-------------------------------\n");
							printf("Are you happy with the changes?\nType: 1 if yes\nType: 2 to redo\n");
							scanf("%d", &answer_other);
							// If not redo all the changes
							if(answer_other == 2)
							{
								for(int i = 0; i < num; i++)
								{
									// Pop from temp stack to save last value
									int col = pop(tempStack);
									// Push to the actual stack
									push(stack, col);
									// Decide which player token to place and place it 
									if(i % 2 != 0){
										place_token_2(board, player_one, col);
									}
									else
									{
										place_token_2(board, player_two, col);
									}
							
								}
								turn = 0;
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
						game = 1;
					}
					answer = 0;
				}
			}
			// Pop all the elements from the stack and place them in a temp array in reversed order.
			while(!isEmpty(stack))
			{
				stackItems++;
				insert(arrayTemp, stackItems, peek(stack));
				pop(stack);
			}
			break;
		
		// Display the rules
		case 2:
			rules();
			break;
		
		// Exit the game
		case 4:
			credits();
			// Clear the screen
			system("pause");
			system("cls");
			quit = 1;
			break;
		// Replay the previous game
		case 3:
			// Create new array
			int n = 1;
			int array[MAX];
			
			// Get the elements from the temp array in the correct order
			for(int i = stackItems; i >= 0; i--)
			{
				insert(array, n, arrayTemp[i]);
				n++;
			}
			
			// Reset board
			board_create(board);
			int turnNum = 0;
		
			// Loop until all tokens are placed
			for(int j = 1; j <= stackItems; j++)
			{
				// Player one turn
				if(j % 2 != 0)
				{
					// Place token
					place_token_2(board, player_one, array[j]);
					printf("---------- Turn: %d -----------\n\n", turnNum);
					printf("-------------------------------\n\n");
				}
				// Player two turn
				else
				{
					// Place token 
					place_token_2(board, player_two, array[j]);
					printf("---------- Turn: %d -----------\n\n", turnNum);
					printf("-------------------------------\n\n");
				}
				if(j == 1)
				{
					printf("Starting replay...\n");			
				}
				// Make the system sleep for 1.5s
				Sleep(1500);
				system("cls");
				turnNum++;
			}
			// Finish the replay
			printf("-------------------------------\n\n");
			board_display(board);
			printf("-------------------------------\n\n");
			printf("----- Replay has finished -----\n\n");
			printf("-------------------------------\n\n");
			system("pause");
			break;
		}			
	}	
	return 0;
}
