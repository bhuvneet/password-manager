#pragma once
#include <iostream>

using namespace std;

class PasswordManager
{
public:
	PasswordManager(void);
	~PasswordManager();

	const unsigned char* getKey(void);	// HOW TO HIDE THE KEY?
	const unsigned char* getInitVector(void);	// HOW TO HIDE THE INIT_VECTOR?
	int storeCredentials(char* username, char* password);
	int setEncryptedPassword(string password);
	void getEncryptedPassword(void);
	int setNewPassword(string password);
	void validatePassword(string password);
	int checkIfExists(string username, string password);

private:
	const unsigned char* encryptionKey;
	const unsigned char* initVector;
	string encryptedPass;	// stores encrypted password
	unsigned char ciphertext[256];
	unsigned char plaintext[256];
	int result;

	// private member functions
	/*Name: Encrypt()
	Description: This private method takes a string as a parameter and returns the encrypted form of it.
	Parameter: String
	Return: Status - Success or Fail
	Output: None
	*/
	void Encrypt(unsigned char plaintext[], unsigned char ciphertext[]);
};