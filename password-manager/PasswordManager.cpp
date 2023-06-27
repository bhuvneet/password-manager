
#include "PasswordManager.h"
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <stdio.h>
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
	OpenSSL_add_all_algorithms();	// initialize OpenSSL
	ERR_load_CRYPTO_strings();

	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, 
		(const unsigned char*)this->getKey(), (const unsigned char*)this->getInitVector());

	int len;
	int plaintextSize = sizeof(plaintext) / sizeof(unsigned char);

	// Encrypt the string
	int ciphertextLen = plaintextSize + AES_BLOCK_SIZE;
	//ciphertext = new unsigned char[ciphertextLen];
	
	EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintextSize);
	int ciphertextFinalLen;
	EVP_EncryptFinal_ex(ctx, ciphertext + len, &ciphertextFinalLen);

	// Output the encrypted string
	std::cout << "Encrypted String: ";
	for (int i = 0; i < len + ciphertextFinalLen; i++)
		printf("%02x", ciphertext[i]);
	std::cout << std::endl;

	//string result(reinterpret_cast<char*>(ciphertext), ciphertextLen);

	// Clean up
	//delete[] ciphertext;	//free memory
	EVP_CIPHER_CTX_free(ctx);
	ERR_free_strings();
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
		// file exists - validate creds, check if duplicate exists, encrypt password and store
		Encrypt((unsigned char*)password, this->ciphertext);
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