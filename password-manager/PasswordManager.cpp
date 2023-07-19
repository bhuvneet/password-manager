
#include "PasswordManager.h"
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <ctype.h> 
#include <iostream>
#include <random>
#include <unordered_map>	// to store key-value login credentials. unordered-map will enable faster retrieval.
#include "Common.h"
using namespace std;
#pragma warning (disable:4996)


// constructor
PasswordManager::PasswordManager(void)
{
	this->encryptionKey = (const unsigned char*)"0123456789abcdef0123456789abcdef";
	this->initVector = (const unsigned char*)"0123456789abcdef";
}

// destructor
PasswordManager::~PasswordManager()
{
}

const unsigned char* PasswordManager::getKey()
{
	return this->encryptionKey;
}

const unsigned char* PasswordManager::getInitVector()
{
	return this->initVector;
}

const string PasswordManager::getCredentials(string whichWebsite)
{
	return this->loginCreds[whichWebsite];
}

/*Name: Encrypt()
Description: This private method takes a string as a parameter and returns the encrypted form of it.
Parameter: String
Return: Status - Success or Fail
Output: None
*/
void PasswordManager::Encrypt(unsigned char plaintext [], unsigned char ciphertext[])
{
	char* salt = generateSalt(16);
	char result[256];

	// Initialize the OpenSSL library
	OpenSSL_add_all_algorithms();
	ERR_load_crypto_strings();

	const EVP_CIPHER* cipher = EVP_aes_256_cbc();  // AES-256 in CBC mode
	const int keyLength = EVP_CIPHER_key_length(cipher);
	const int ivLength = EVP_CIPHER_iv_length(cipher);

	// Generate a random encryption key and initialization vector (IV)
	unsigned char* key = (unsigned char*)malloc(keyLength * sizeof(char));	// allocate memory for length of keyLength
	unsigned char* iv = (unsigned char*)malloc(ivLength* sizeof(char));	// allocate memory for length of keyLength
	if (key != NULL && iv != NULL)
	{
		RAND_bytes(key, keyLength);
		key[keyLength] = { '\0' };	// null terminate char array to mitigate garbage values
		RAND_bytes(iv, ivLength);
		iv[ivLength] = { '\0' };	// null terminate char array to mitigate garbage values
	}

	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, cipher, nullptr, key, iv);

	// Encrypt the password
	int plaintextSize = sizeof(plaintext) / sizeof(unsigned char);
	int encryptedLength = plaintextSize + EVP_CIPHER_block_size(cipher);
	//unsigned char* encryptedData = new unsigned char[encryptedLength];
	int finalLength = 0;
	EVP_EncryptUpdate(ctx, ciphertext, &encryptedLength, plaintext, plaintextSize);
	EVP_EncryptFinal_ex(ctx, ciphertext + encryptedLength, &finalLength);

	//std::string encryptedPassword(reinterpret_cast<char*>(encryptedData), encryptedLength + finalLength);

	// Output the encrypted string
	std::cout << "Encrypted String: ";
	for (int i = 0; i < finalLength; i++)
		printf("%02x", ciphertext[i]);
	std::cout << std::endl;

	EVP_CIPHER_CTX_free(ctx);

	// Combine the salt, key, and IV into a single string - USE THIS TO AUTHENTICATE USER
	strcpy(result, (char*)salt);  
	strcat(result, (char*)key);
	strcat(result, (char*)iv);
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
char* PasswordManager::generateSalt(int length)
{
	const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	const int charsetSize = sizeof(charset) - 1;
	random_device rd;
	mt19937 generator(rd());
	char* salt = (char*)malloc(length * sizeof(char));	// allocate memory for length of salt

	if (salt != NULL)
	{
		for (int i = 0; i < length; ++i) {
			salt[i] = charset[generator() % charsetSize];
		}
		salt[length] = { '\0' };	// null terminate char array to mitigate garbage values
	}

	return salt;
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
int PasswordManager::storeCredentials(char* website, char* username, char* password) 
{

	// encrypt password and store
	setEncryptedPassword(password);
	//Encrypt((unsigned char*)password, this->ciphertext);

	// store in a key-value pair format - Key: whichLogin; Value: username + hashedPassword
	// save password in an unordered map
	strcpy(this->whichLogin, website);
	size_t length = sizeof(ciphertext) / sizeof(unsigned char);
	string login;
	login.append(username);
	login.append(" ");
	login.append(reinterpret_cast<const char*>(ciphertext), length);
	this->loginCreds[this->whichLogin] = login;

	return 0;
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
int PasswordManager::setEncryptedPassword(char* password)
{
	// encrypted the plaintext password
	Encrypt((unsigned char*)password, this->ciphertext);
	return 0;
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
unsigned char* PasswordManager::getEncryptedPassword(void)
{
	return this->ciphertext;
}

int PasswordManager::setNewUserName(string whichWebsite, string username)
{
	return 0;
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
int PasswordManager::setNewPassword(string whichWebsite, string password)
{
	// change password for credentials already saved in file
	// first check if password exists
	// validate password
	// update password in map
	return 0;
}

/*Name: validatePassword
Description: Function takes a password and returns true if it is:
	at least 8 characters long or contains 
	at least one uppercase letter
	at least one digit 
	at least one of these four characters: ! @ # $ 
	Otherwise it returns false.
Parameter: const char*
Return: True or False
Output: Result of the validation
*/
bool PasswordManager::validatePassword(const char* password)
{
	size_t length = strlen(password);
	int isDigit = 0;
	int isUpper = 0;

	// check if password is valid
	if (length >= 8)
	{
		for (int i = 0; i < length; i++)
		{
			if (password[i] == '!' || password[i] == '@' 
				|| password[i] == '#' || password[i] == '$')
			{
				return false;
			}
			// check only when we don't already have 1 digit and 1 uppercase count.
			if (isDigit != 1)
			{
				if (isdigit(password[i]) != 0)
				{
					isDigit += 1;
				}
			}
			if (isUpper != 1)
			{
				if (isupper(password[i]) != 0)
				{
					isUpper += 1;
				}
			}
		}

		if (isDigit == 0 || isUpper == 0)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
int PasswordManager::checkIfExists(string website)
{
	this->result = 0;
	if (loginCreds.find(website) == loginCreds.end())
	{
		// not found
		return result;
	}
	else
	{	// website exists in map
		return result = 1;
	}
}