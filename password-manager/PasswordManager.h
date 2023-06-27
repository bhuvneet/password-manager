#pragma once
#include <iostream>

using namespace std;

class PasswordManager
{
public:
	PasswordManager(string password);
	~PasswordManager();

	void setEncryptedPassword(string password);
	void getEncryptedPassword(void);
	const unsigned char* getKey(void);	// HOW TO HIDE THE KEY?
	const unsigned char* getInitVector(void);	// HOW TO HIDE THE INIT_VECTOR?
	void setNewPassword(string password);
	void validatePassword(string password);

private:
	const unsigned char* encryptionKey;
	const unsigned char* initVector;
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