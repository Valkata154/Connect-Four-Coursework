#include<stdio.h>
#include<string.h>

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
			printf("Game Started");
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
}
