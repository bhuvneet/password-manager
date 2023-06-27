#include <stdio.h>
#include "PasswordManager.h"
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
	//PasswordManager password("HelloWorld!");
	char choice[3];
	while (true)
	{
		printf("Password Utilities:\n");
		printf("\tA. Store Credentials\n");	// store credentials in text file
		printf("\tB. Change Password\n");	// change password of already existing credentials
		printf("\tC. Validate Password\n");	// validate password
		printf("\tD. Quit\n");				// quit program
		// get input from user
		printf("\tEnter your choice: ");
		// check if choice is to quit program
		scanf("%1s", choice);
		if ((strcmp(choice,"d") == 0) || (strcmp(choice, "D") == 0))
		{
			break;
		}
	}

	return 0;
}