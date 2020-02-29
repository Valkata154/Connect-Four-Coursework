/*
*
*  @author: Valeri Vladimirov 40399682
*  Last Modified: 29/02/2019
*  Purpose: Connect Four game implementation in C.
*  Functionality: 
*	
*	- Normal Play, Competitive Play, Versus Bot Play
*	- Pop Out, Pop 10, 5-in-a-Row
*	- Undo once, Undo more than once, redo the undo (depending on game mode)
*	- Place tokens, remove tokens
*	- Diagonal, horizontal, vertical checks
*	- Replay games from the start (depending on game mode)
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
	int player_score = 0;
	int player1_score = 0;
	int player2_score = 0;
	int bot_score = 0;
	int last_column = 0;
	int stack_items = 0;
	int array_temp[MAX];
	int gamemode = 1;
	int row = 5;
	int counter = 0;
	int poping = 0;
	int game_num = 1;
	int difficulty = 1;
	int exit = 0;
	int game_counter = 0;
	
	struct Stack* stack = createStack(100);
	
	Board board[ROW][COL] = { '\0' };
	Board board2[ROW][COL5] = { '\0' };
	Box player_one = { '/0' };
	Box player_two = { '/0' };

	// board_create_five(board2);
	// board_display_five(board2);

	// Initialize tokens
	player_one.token = PLAYER1;
	player_two.token = PLAYER2;
	
	// Fill the boards with dashes (meaning the cells are empty)
	board_create(board);
	board_create_five(board2);
	
	// Create array for 15 replays and 42moves and init it with -1's
	int array[15][MAX];				
	init(array);
	
	while(quit==0)
	{
		// Display the menu
		menu();
		while(exit == 0)
		{
			// Get user input 
			printf("Enter selection: ");
			scanf("%d", &choice);
			system("cls");
			// Wrong input checking
			if(choice < 1 || choice > 5)
			{
				system("cls");
				menu();
				printf("\n[ERROR] Please enter a number that is in the given range!\n\n");
			}
			else
			{
				exit = 1;
			}
		}
		exit = 0;
		system("cls");
		
		// Switch statement for the menu
		switch (choice)
		{
		// Start the game
		case 1:
			// Reset board and variables on new game
			board_create(board);
			board_create_five(board2);
			game = 0;
			turn = 0;
			counter = 0;
			game_counter = 0;	
			row = 5;
			printf("\n-------------------------------\n");
			printf("--------- GAME STARTED --------\n");
			printf("-------------------------------\n\n");
			// Display board
			if(gamemode == 6)
			{
				board_display_five(board2);
			}
			else
			{
				board_display(board);
			}
			system("pause");
			system("cls");
			// While playing switch turns between players until someone wins
			while (game == 0)
			{
				stack_items = 0;
				array_temp[MAX];
				
				// PLAYER 1
				if (turn == 0)
				{
					// Switch to Player Two
					turn = 1;
					// Display score when not playing vs BOT
					if(gamemode != 5)
					{
						printf("---------- SCORE --------------\n");
						printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
						printf("-------------------------------\n");
						printf("-------------------------------\n");
						printf("-------- PLAYER 1 TURN --------\n");
					}
					// When playing vs BOT
					else
					{
						system("cls");
						printf("---------- SCORE --------------\n");
						printf("------ Player: %d - Bot: %d -----\n", player1_score, bot_score);
						printf("-------------------------------\n");
						printf("-------------------------------\n");
						printf("--------- PLAYER TURN ---------\n");
					}
					// Place the token and save the column in the stack for undo function
					if(gamemode == 1 || gamemode == 5 || gamemode == 2)
					{
						push(stack, place_token(board, player_one)); 
						game_counter++;
					}
					else if(gamemode ==6)
					{
						place_token_five(board2, player_one);
						game_counter++;
					}
					// Placing for POP 10
					else if(gamemode == 4)
					{
						push(stack, place_token_pop_ten(board, player_one, row)); 
						counter++; 
						game_counter++;
						if(counter == 7)
						{
							counter = 0;
							row--;
						}
					}
					// POP OUT
					else if (gamemode == 3)
					{
						system("cls");
						printf("---------- SCORE --------------\n");
						printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
						printf("-------------------------------\n");
						printf("-------------------------------\n");
						printf("-------- PLAYER 1 TURN --------\n");
						printf("-------------------------------\n\n");
						board_display(board);
						printf("-------------------------------\n\n");
						// Ask the user if they want to pop or place
						while(exit == 0)
						{
							printf("Would you like to place or pop?\nType [1] to place or [2] to pop\n");
							printf("Enter selection: ");
							scanf("%d", &poping);
							system("cls");
							// Wrong input checking.
							if(poping < 1 || poping > 2)
							{
								system("cls");
								printf("[ERROR] Please enter a number that is in the given range!\n\n");
							}
							else
							{
								exit = 1;
							}
						}
						exit = 0;
						
						// If they want to place
						if(poping == 1)
						{
							push(stack, place_token(board, player_one)); 
							game_counter++;
						}
						// Else if they want to POP
						else
						{
							printf("---------- SCORE --------------\n");
							printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
							printf("-------------------------------\n");
							printf("-------------------------------\n");
							printf("-------- PLAYER 1 TURN --------\n");
							printf("-------------------------------\n\n");
							board_display(board);
							printf("-------------------------------\n\n");
							int col = 0;
							// Ask which column to pop and remove the first token
							while(exit == 0)
							{
								printf("Enter on which column from [0] to [6]: ");
								scanf("%d", &col);
								
								system("cls");
								// Wrong input checking
								if(col < 0 || col > 6)
								{
									system("cls");
									printf("[ERROR] Please enter a number that is in the given range!\n\n");
								}
								else
								{
									exit = 1;
								}
							}
							exit = 0;
							// Remove the bottom token
							remove_token(board, player_one, col);
							game_counter--;
						}
					}
						
					system("cls");
					printf("-------------------------------\n\n");
					board_display(board);
					printf("-------------------------------\n\n");
					if(gamemode == 2 || gamemode == 6)
					{
						system("cls");
					}
					
					// UNDO not allowed for Pop Out, Competitive and VS bot and 5-IN-A-ROW
					if(gamemode == 1 || gamemode == 4)
					{
						// Ask the user if they want to undo their move
						while(exit == 0)
						{
							printf("Do you want to undo your move?\nType: [1] for YES and [2] for NO\n");
							scanf("%d", &answer);
							
							system("cls");
							// Wrong input checking
							if(answer < 1 || answer > 2)
							{
								system("cls");
								printf("[ERROR] Please enter a number that is in the given range!\n\n");
							}
							else
							{
								exit = 1;
							}
						}
						exit = 0;
						
						// If yes find the box
						if(answer == 1)
						{
							// Ask user if they want to undo once or more
							while(exit == 0)
							{
								printf("Type [1] if you want to undo ONLY YOUR TURN\nor [2] if you want to undo MORE THAN ONCE.\n");
								scanf("%d", &answer);
								
								system("cls");
								// Wrong input checking
								if(answer < 1 || answer > 2)
								{
									system("cls");
									printf("[ERROR] Please enter a number that is in the given range!\n\n");
								}
								else
								{
									exit = 1;
								}
							}
							exit = 0;
							// If only once
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
										counter--;
										game_counter--;
										break;
									}
								}
								// Show the board and ask if user is happy with changes
								system("cls");
								printf("-------------------------------\n\n");
								board_display(board);
								printf("-------------------------------\n");
								while(exit == 0)
								{
									printf("Are you happy with the change?\nType: [1] if yes\nType: [2] to redo\n");
									scanf("%d", &answer_other);
									system("cls");
									// Wrong input checking
									if(answer_other < 1 || answer_other > 2)
									{
										system("cls");
										printf("[ERROR] Please enter a number that is in the given range!\n\n");
									}
									else
									{
										exit = 1;
									}
								}
								exit = 0;
								// If not redo the changes
								if(answer_other == 2)
								{
									// Pop from temp stack to save last value
									int col = pop(tempStack);
									// Push the value to the actual stack
									push(stack, col);
									// Place the token back to its place
									place_token_2(board, player_one, col);
									turn = 1;
									counter++;
									game_counter++;
								}
							}
							// If undo more than once
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
								// Pop 10 counter
								counter = counter - num;
								game_counter = game_counter - num;
								
								// Show the board and ask if user is happy with changes
								system("cls");
								printf("-------------------------------\n\n");
								board_display(board);
								printf("-------------------------------\n");
								while(exit == 0)
								{
									printf("Are you happy with the change?\nType: [1] if yes\nType: [2] to redo\n");
									scanf("%d", &answer_other);
									system("cls");
									// Wrong input checking
									if(answer_other < 1 || answer_other > 2)
									{
										system("cls");
										printf("[ERROR] Please enter a number that is in the given range!\n\n");
									}
									else
									{
										exit = 1;
									}
								}
								exit = 0;
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
									game_counter = game_counter + num;
									counter = counter + num;
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
					}
					
					if(gamemode == 6)
					{
						// Check if 5 connect somewhere
						win1 = vertical_checker_five(board2, player_one) + horizontal_checker_five(board2, player_one) + diagonal_checker_five(board2, player_one);
					}
					else
					{
						// Check if four connect somewhere
						win1 = vertical_checker(board, player_one) + horizontal_checker(board, player_one) + diagonal_checker(board, player_one);
					}
					if (win1 > 0)
					{
						// Versus person
						if(gamemode < 5 || gamemode == 6)
						{
							system("cls");
							// Increment  and display the score
							player1_score++;
							printf("---------- SCORE --------------\n");
							printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
							printf("-------------------------------\n");
							// Print message to the winner
							printf("-------------------------------\n");
							printf("--- PLAYER 1 IS THE WINNER! ---\n");
							printf("-------------------------------\n\n");
						}
						// Versus BOT
						else
						{
							system("cls");
							// Increment  and display the score
							player1_score++;
							printf("---------- SCORE --------------\n");
							printf("------ Player: %d - Bot: %d -----\n", player1_score, bot_score);
							printf("-------------------------------\n");
							// Print message to the winner
							printf("-------------------------------\n");
							printf("---- PLAYER IS THE WINNER! ----\n");
							printf("-------------------------------\n\n");
						}
						if(gamemode == 6)
						{
							board_display_five(board2);
						}
						else
						{
							board_display(board);
						}
						printf("-------------------------------\n\n");
						system("pause");
						game = 1;	
					}
					if(game_counter == 42 && win1 == 0)
					{
						system("cls");
						printf("---------- SCORE --------------\n");
						printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
						printf("-------------------------------\n");
						// Print message to the winner
						printf("-------------------------------\n");
						printf("-------- GAME FINISHED  -------\n");
						printf("------- WITHOUT A WINNER  -----\n");
						printf("-------------------------------\n\n");
						game = 1;
						
						if(gamemode == 6)
						{
							board_display_five(board2);
						}
						else
						{
							board_display(board);
						}
					}
					answer = 0;
					// Pop 10 checker if row is filled
					if(counter == 7)
					{
						counter = 0;
						row--;
					}
				}
				
				
				
				
				
				
				// PLAYER 2
				else
				{
					// Switch to Player One
					turn = 0;
					// Display score versus person
					if(gamemode < 5 || gamemode == 6)
					{
						printf("---------- SCORE --------------\n");
						printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
						printf("-------------------------------\n");
						printf("-------------------------------\n");
						printf("-------- PLAYER 2 TURN --------\n");
					}
					
					// Place the token and save the column in the stack for undo function DEFAULT
					if(gamemode == 1 || gamemode == 2 )
					{
						push(stack, place_token(board, player_two)); 
						game_counter++;
						
					}
					else if(gamemode ==6)
					{
						place_token_five(board2, player_two);
						game_counter++;						
					}
					// BOT moves
					else if (gamemode == 5)
					{	
						push(stack, place_token_bot(board, peek(stack), difficulty));
						game_counter++;	
						system("cls");
						printf("---------- SCORE --------------\n");
						printf("------ Player: %d - Bot: %d -----\n", player1_score, bot_score);
						printf("-------------------------------\n");
						printf("-------------------------------\n");
						printf("----------- BOT TURN ----------\n");
						printf("-------------------------------\n\n");
						board_display(board);
						printf("\n-------------------------------\n\n");
						system("pause");
					}
					// Place for POP 10
					else if(gamemode == 4)
					{
						push(stack, place_token_pop_ten(board, player_two, row));
						game_counter++;							
						counter++; 
						if(counter == 7)
						{
							counter = 0;
							row--;
						}
					}
					// POP OUT
					else if (gamemode == 3)
					{
						system("cls");
						printf("---------- SCORE --------------\n");
						printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
						printf("-------------------------------\n");
						printf("-------------------------------\n");
						printf("-------- PLAYER 2 TURN --------\n");
						printf("-------------------------------\n\n");
						board_display(board);
						printf("-------------------------------\n\n");
						// Ask the user if they want to pop or place
						while(exit == 0)
						{
							printf("Would you like to place or pop?\nType [1] to place or [2] to pop\n");
							printf("Enter selection: ");
							scanf("%d", &poping);
							system("cls");
							
							// Check for wrong input
							if(poping < 1 || poping > 2)
							{
								system("cls");
								printf("[ERROR] Please enter a number that is in the given range!\n\n");
							}
							else
							{
								exit = 1;
							}
						}
						exit = 0;
						// Placing
						if(poping == 1)
						{
							push(stack, place_token(board, player_two)); 
							game_counter++;	
						}
						// Poping
						else
						{
							printf("---------- SCORE --------------\n");
							printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
							printf("-------------------------------\n");
							printf("-------------------------------\n");
							printf("-------- PLAYER 2 TURN --------\n");
							printf("-------------------------------\n\n");
							// Display the board
							board_display(board);
							printf("-------------------------------\n\n");
							int col = 0;
							// Ask for which column to remove the first token and remove it
							while(exit == 0)
							{
								printf("Enter on which column from [0] to [6]: ");
								scanf("%d", &col);
								system("cls");
								// Checking for wrong input
								if(col < 0 || col > 6)
								{
									system("cls");
									printf("[ERROR] Please enter a number that is in the given range!\n\n");
								}
								else
								{
									exit = 1;
								}
							}
							exit = 0;
							remove_token(board, player_one, col);
							game_counter--;	
						}
					}
					system("cls");
					printf("-------------------------------\n\n");
					board_display(board);
					printf("-------------------------------\n\n");
					if(gamemode == 2 || gamemode == 6)
					{
						system("cls");
					}
					
					// UNDO not allowed for Pop Out, Competitive and VS bot
					if(gamemode == 1 || gamemode == 4)
					{
						// Ask the user if they want to undo their move
						while(exit == 0)
						{
							printf("Do you want to undo your move?\nType: [1] for YES and [2] for NO\n");
							scanf("%d", &answer);
							system("cls");
							// Wrong input checking
							if(answer < 1 || answer > 2)
							{
								system("cls");
								printf("[ERROR] Please enter a number that is in the given range!\n\n");
							}
							else
							{
								exit = 1;
							}
						}
						exit = 0;
						// If yes find the box
						if(answer == 1)
						{
							// Ask user if they want to undo once or more
							while(exit == 0)
							{
								printf("Type [1] if you want to undo ONLY YOUR TURN\nor [2] if you want to undo MORE THAN ONCE.\n");
								scanf("%d", &answer);
								system("cls");
								// Wrong input checking
								if(answer < 1 || answer > 2)
								{
									system("cls");
									printf("[ERROR] Please enter a number that is in the given range!\n\n");
								}
								else
								{
									exit = 1;
								}
							}
							exit = 0;
							// If once
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
										counter--;
										game_counter--;	
										break;
									}
								}
								// Show the board and ask if user is happy with changes
								system("cls");
								printf("-------------------------------\n\n");
								board_display(board);
								printf("-------------------------------\n");
								while(exit == 0)
								{
									printf("Are you happy with the change?\nType: [1] if yes\nType: [2] to redo\n");
									scanf("%d", &answer_other);
									
									system("cls");
									// Wrong input checking
									if(answer_other < 1 || answer_other > 2)
									{
										system("cls");
										printf("[ERROR] Please enter a number that is in the given range!\n\n");
									}
									else
									{
										exit = 1;
									}
								}
								exit = 0;
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
									counter++;
									game_counter++;	
								}
							}
							// If more than once
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
								counter = counter - num;
								game_counter = game_counter - num;	
								
								// Show the board and ask if user is happy with changes
								system("cls");
								printf("-------------------------------\n\n");
								board_display(board);
								printf("-------------------------------\n");
								while(exit == 0)
								{
									printf("Are you happy with the change?\nType: [1] if yes\nType: [2] to redo\n");
									scanf("%d", &answer_other);
									system("cls");
									// Wrong input checking
									if(answer_other < 1 || answer_other > 2)
									{
										system("cls");
										printf("[ERROR] Please enter a number that is in the given range!\n\n");
									}
									else
									{
										exit = 1;
									}
								}
								exit = 0;
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
									counter = counter + num;
									game_counter = game_counter + num;	
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
					}
					
					if(gamemode == 6)
					{
						// Check if 5 connect somewhere
						win2 = vertical_checker_five(board2, player_two) + horizontal_checker_five(board2, player_two) + diagonal_checker_five(board2, player_two);
					}
					else
					{
						// Check if four connect somewhere
						win2 = vertical_checker(board, player_two) + horizontal_checker(board, player_two) + diagonal_checker(board, player_two);
					}
					if (win2 > 0)
					{
						if(gamemode < 5 || gamemode == 6)
						{
							system("cls");
							// Display and increment score
							player2_score++;
							printf("---------- SCORE --------------\n");
							printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
							printf("-------------------------------\n");
							// Print message to the winner
							printf("-------------------------------\n");
							printf("--- PLAYER 2 IS THE WINNER! ---\n");
							printf("-------------------------------\n\n");
						}
						else
						{
							system("cls");
							// Increment  and display the score
							bot_score++;
							printf("---------- SCORE --------------\n");
							printf("------ Player: %d - Bot: %d -----\n", player1_score, bot_score);
							printf("-------------------------------\n");
							// Print message to the winner
							printf("-------------------------------\n");
							printf("------ BOT IS THE WINNER! -----\n");
							printf("-------------------------------\n\n");
						}
						// Display the board
						if(gamemode == 6)
						{
							board_display_five(board2);
						}
						else
						{
							board_display(board);
						}
						printf("-------------------------------\n\n");
						system("pause");
						game = 1;
					}
					if(game_counter == 42 && win2 == 0)
					{
						system("cls");
						printf("---------- SCORE --------------\n");
						printf("-- Player 1: %d - Player 2: %d --\n", player1_score, player2_score);
						printf("-------------------------------\n");
						// Print message to the winner
						printf("-------------------------------\n");
						printf("-------- GAME FINISHED  -------\n");
						printf("------- WITHOUT A WINNER  -----\n");
						printf("-------------------------------\n\n");
						game = 1;
						
						if(gamemode == 6)
						{
							board_display_five(board2);
						}
						else
						{
							board_display(board);
						}
					}
					answer = 0;
					// Checking for pop 10
					if(counter == 7)
					{
						counter = 0;
						row--;
					}
				}
			}
			// Saving replays (not for pop out and 5-in-a-row)
			if(gamemode < 3 || gamemode > 3 || gamemode < 6)
			{
				// Pop all the elements from the stack and place them in a temp array in reversed order.
				while(!isEmpty(stack))
				{
					stack_items++;
					insert(array_temp, stack_items, peek(stack));
					pop(stack);
				}
				int n = 0;
				
				// Get the elements from the temp array in the correct order
				for(int i = stack_items; i >= 0; i--)
				{
					array[game_num][n] = array_temp[i];
					n++;
				}
				// Increment to the next game
				game_num++;
			}
			break;
		
		// Display the rules
		case 2:
			rules();
			break;
		
		// Exit the game
		case 5:
			credits();
			// Clear the screen
			system("pause");
			system("cls");
			quit = 1;
			break;
		// Replay games
		case 4:
			// Replay not allowed for Pop Out
			if(gamemode < 3 || gamemode > 3 || gamemode > 5)
			{
				// Prompt the user to pick a replay
				int number = 0;
				printf("Enter the number of the game you want to see.\nFor the first game type: [1]\nfor the second game: [2] and so on...\n");
				scanf("%d", &number);
				// Reset board
				board_create(board);
				int turnNum = 0;
			
				int j = 1;
				// Loop until all tokens are placed
				while(array[number][j] != -1)
				{
					// Player one turn
					if(j % 2 != 0)
					{
						// Place token
						place_token_2(board, player_one, array[number][j]);
						printf("---------- Turn: %d -----------\n\n", turnNum);
						printf("-------------------------------\n\n");
					}
					// Player two turn
					else
					{
						// Place token 
						place_token_2(board, player_two, array[number][j]);
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
					j++;
				}
				// If there are no more replays
				if(array[number][j] == -1)
				{
					// Finish the replay
					printf("-------------------------------\n\n");
					board_display(board);
					printf("-------------------------------\n\n");
					printf("----- Replay has finished -----\n\n");
					printf("-------------------------------\n\n");
				}
				if(array[number][j] == -1 && array[number][2] == -1)
				{
					system("cls");
					printf("-------------------------------------\n\n");
					printf("-------- There are no replays -------\n\n");
					printf("-------------------------------------\n\n");
				}
				system("pause");
			}
			else
			{
				printf("Undo and replay are not supported on POP OUT Gamemode!\n");
				system("pause");
				system("cls");
			}
			break;
		
		// Gamemode
		case 3:
			while(exit == 0)
			{
				printf("Select Gamemode:\n\n");
				printf("[1] CONNECT FOUR NORMAL\n");
				printf("[2] COMPETITIVE\n");
				printf("[3] POP OUT\n");
				printf("[4] POP 10\n");
				printf("[5] VERSUS BOT\n");
				printf("[6] 5-IN-A-ROW\n");
				printf("\nEnter selection: ");
				scanf("%d", &gamemode);
				// Wrong input checking
				if(gamemode < 1 || gamemode > 6)
				{
					system("cls");
					printf("[ERROR] Please enter a number that is in the given range!\n\n");
				}
				else
				{
					exit = 1;
				}
			}
			exit = 0;
			// If playing vs bot ask for difficulty
			if(gamemode == 5)
			{
				system("cls");
				player_score = 0;
				bot_score = 0;
				printf("\nYou have selected to play vs the Computer!\n");
				while(exit == 0)
				{
					printf("Please select a difficulty level:\n\n");
					printf("[1] EASY (DEFAULT)\n");
					printf("[2] HARD\n");
					printf("\nEnter selection: ");
					scanf("%d", &difficulty);
					// Wrong input checking.
					if(difficulty < 1 || difficulty > 2)
					{
						system("cls");
						printf("[ERROR] Please enter a number that is in the given range!\n\n");
					}
					else
					{
						exit = 1;
					}
				}
				exit = 0;
			}
		}			
	}	
	return 0;
}
