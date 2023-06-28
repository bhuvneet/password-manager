
#include "PasswordManager.h"
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <iostream>
#include <random>
#include <map>
#include "Constants.h"
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
	int len;
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
int PasswordManager::storeCredentials(char* username, char* password) 
{
	// check if file exists
	FILE* fp = fopen(PASSWORD_FILE, "a");
	if (fp != NULL)
	{
		// encrypt password and store
		Encrypt((unsigned char*)password, this->ciphertext);

		// store in a key-value pair format - Key: whichLogin; Value: username + hashedPassword
		// save password in an ordered map
		fprintf(fp, (const char*)this->ciphertext);
	}
	else
	{
		fp = fopen(PASSWORD_FILE, "w");	// create file
	}
	fclose(fp);

	return 0;
	// if not, create file and add credentials to it once validated
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
int PasswordManager::setEncryptedPassword(string password)
{
	// encrypted the plaintext password
	return 0;
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
void PasswordManager::getEncryptedPassword(void)
{

}

/*Name:
Description:
Parameter:
Return:
Output:
*/
int PasswordManager::setNewPassword(string password)
{
	// change password for credentials already saved in file
	return 0;
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
void PasswordManager::validatePassword(string password)
{
	// check if password is valid
}

/*Name:
Description:
Parameter:
Return:
Output:
*/
int PasswordManager::checkIfExists(string username, string password)
{
	// check if credentials exist in file
	return 0;
}