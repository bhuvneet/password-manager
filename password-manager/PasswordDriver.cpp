#include <stdio.h>
#include "PasswordManager.h"
#include "Constants.h"
#pragma warning (disable:4996)

/*Name:
Description:
Parameter:
Return:
Output:
*/

// main driver file
int main()
{
	PasswordManager loginCred;	// instance of PasswordManager class

	char choice[3] = {"\0"};
	char username[USERNAME_MAXLEN] = { "\0" };
	char password[PASSWORD_MAXLEN] = { "\0" };

	while ((strcmp(choice, "d") != 0) || (strcmp(choice, "D") != 0))
	{
		printf("Password Utilities:\n");
		printf("\tA. Store Credentials\n");	// store credentials in text file
		printf("\tB. Change Password\n");	// change password of already existing credentials
		printf("\tC. Validate Password\n");	// validate password
		printf("\tD. Quit\n");				// quit program
		// get input from user
		printf("\tEnter your choice: ");
		// check if choice is to quit program
		scanf("%s", choice);
		
		if (choice[0] == 'A')
		{
			printf("A");
			printf("\tEnter username: ");
			scanf("%s", username);	// find better way to store in string
			printf("\tEnter password: ");
			scanf("%s", password);	// find better way to store in string
			// check if already exists in file
			// verify password
			loginCred.storeCredentials(username, password);
		}
		if (choice[0] == 'B')
		{
			printf("A");
		}
		if (choice[0] == 'C')
		{
			printf("A");
		}
	}

	return 0;
}