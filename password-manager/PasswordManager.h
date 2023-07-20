#pragma once
#include <iostream>
#include <unordered_map>	// to store key-value login credentials. unordered-map will enable faster retrieval.


using namespace std;

class PasswordManager
{
public:
	PasswordManager(void);
	~PasswordManager();

	const unsigned char* getKey(void);	// HOW TO HIDE THE KEY?
	const unsigned char* getInitVector(void);	// HOW TO HIDE THE INIT_VECTOR?
	const string getCredentials(string whichWebsite);
	const string getAuthString();
	int storeCredentials(char* website, char* username, char* password);
	int setEncryptedPassword(char* password);
	unsigned char* getEncryptedPassword(void);
	bool validatePassword(const char* password);
	vector<uint8_t> generateSalt(int length);
	string calculate_hash();
	unsigned long hash(string& str, int len);

private:
	char whichLogin[126];
	char userName[126];
	unordered_map<string, string> loginCreds;

	unsigned char* encryptionKey;
	unsigned char* initVector;
	string encryptedPass;	// stores encrypted password
	unsigned char ciphertext[256];
	unsigned char plaintext[256];
	int result;
	string authUserString;

	// private member functions
	/*Name: Encrypt()
	Description: This private method takes a string as a parameter and returns the encrypted form of it.
	Parameter: String
	Return: Status - Success or Fail
	Output: None
	*/
	void Encrypt(unsigned char plaintext[], unsigned char ciphertext[]);
};