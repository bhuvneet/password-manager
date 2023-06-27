#pragma once
#include <iostream>

using namespace std;

class PasswordManager
{
public:
	PasswordManager(string text);
	~PasswordManager();

private:
	string encryptedPass;	// stores encrypted password

	// private member functions
	/*Name: Encrypt()
	Description: This private method takes a string as a parameter and returns the encrypted form of it.
	Parameter: String
	Return: Status - Success or Fail
	Output: None
	*/
	string Encrypt(const string& plainText);
};