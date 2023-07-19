#include <stdio.h>
#include "PasswordManager.h"
#include "FileIO.h"
#include "Common.h"
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
	bool result;
	int numOfAttempts = 0;
	char choice[3] = {"\0"};
	char website[WEBSITE_NAME] = { "\0" };
	char username[USERNAME_MAXLEN] = { "\0" };
	char password[PASSWORD_MAXLEN] = { "\0" };

	// create login file
	FileIO myLoginFile;

	while ((strcmp(choice, "C") != 0))
	{
		printf("Password Utilities:\n");
		printf("\tA. Store Credentials\n");	// store credentials in text file
		printf("\tB. Update Credentials\n");	// change password of already existing credentials
		printf("\tC. Quit\n");				// quit program
		// get input from user
		printf("\tEnter your choice: ");
		// check if choice is to quit program
		scanf("%s", choice);
		
		if (choice[0] == 'A')
		{
			printf("\tEnter name of website: ");
			scanf("%s", website);	// find better way to store in string
			printf("\tEnter username: ");
			scanf("%s", username);	// find better way to store in string
			printf("\tEnter password: ");
			scanf("%s", password);	// find better way to store in string

			// validate password first
			while (((result = loginCred.validatePassword(password)) == false) && numOfAttempts <= 5)
			{
				printf("\n\tPassword Validation criteria: \t at least 1 uppercase, "
					"1 digit and 8 characters in length. ! @ # $ are not allowed.\n");
				printf("\tEnter password: ");
				scanf("%s", password);	// find better way to store in string
					
				if (numOfAttempts == 5)
				{
					printf("Number of attempts exceeded 5. Exiting program...");
					return 0;
				}
			}
			if (result)
			{
				loginCred.storeCredentials(website, username, password);

				// save credential in file
				string thisLogin = loginCred.getCredentials(website);
				result = myLoginFile.appendToFile(website, thisLogin);
			}
		}
		if (choice[0] == 'B')
		{
			numOfAttempts = 0;
			while (((result = loginCred.checkIfExists(website)) == false) && numOfAttempts <= 5)
			{
				printf("\tEnter name of website: ");
				scanf("%s", website);	// find better way to store in string

				if (numOfAttempts == 5)
				{
					printf("Number of attempts exceeded 5.\n");
					break;
				}
			}
			if (result)	// website exists in map, let user change credentials
			{
				// change username, password or both?
				printf("\tA. Change username\n");	// store credentials in text file
				printf("\tB. Change Password\n");	// change password of already existing credentials
				printf("\tC. Change both\n");				// quit program
				printf("\tD. Return\n");				// quit program

				printf("\tEnter your choice: ");
				scanf("%c", choice);
				if (choice[0] == 'A')
				{
					printf("\tEnter username: ");
					scanf("%s", username);	// find better way to store in string
					loginCred.setNewUserName(website, username);
				}
				else if (choice[0] == 'B')
				{
					printf("\tEnter password: ");
					scanf("%s", password);	// find better way to store in string
					loginCred.setNewPassword(website, password);
				}
				else if (choice[0] == 'C')
				{
					printf("\tEnter username: ");
					scanf("%s", username);	// find better way to store in string
					loginCred.setNewUserName(website, username);
					printf("\tEnter password: ");
					scanf("%s", password);	// find better way to store in string
					loginCred.setNewPassword(website, password);
				}
				else
				{

				}
			}

		}
		if (choice[0] == 'C')
		{
			break;	//exit program
		}
	}

	return 0;
}