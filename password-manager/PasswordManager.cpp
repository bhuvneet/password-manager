
#include "PasswordManager.h"
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include "Constants.h"
using namespace std;
#pragma warning (disable:4996)


// constructor
PasswordManager::PasswordManager(string text)
{
	string result = Encrypt(text);
}

// destructor
PasswordManager::~PasswordManager()
{
}

/*Name: Encrypt()
Description: This private method takes a string as a parameter and returns the encrypted form of it.
Parameter: String
Return: Status - Success or Fail
Output: None
*/
string PasswordManager::Encrypt(const string& plainText)
{
	OpenSSL_add_all_algorithms();	// initialize OpenSSL
	ERR_load_CRYPTO_strings();

	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char*)KEY, (const unsigned char*)INITIALIZATION_VECTOR);

	// Encrypt the string
	int ciphertextLen = plainText.size() + AES_BLOCK_SIZE;
	unsigned char* ciphertext = new unsigned char[ciphertextLen];
	int len;
	EVP_EncryptUpdate(ctx, ciphertext, &len, (const unsigned char*)plainText.c_str(), plainText.size());
	int ciphertextFinalLen;
	EVP_EncryptFinal_ex(ctx, ciphertext + len, &ciphertextFinalLen);

	// Output the encrypted string
	std::cout << "Encrypted String: ";
	for (int i = 0; i < len + ciphertextFinalLen; i++)
		printf("%02x", ciphertext[i]);
	std::cout << std::endl;

	string result(reinterpret_cast<char*>(ciphertext), ciphertextLen);

	// Clean up
	delete[] ciphertext;	//free memory
	EVP_CIPHER_CTX_free(ctx);
	ERR_free_strings();

	return result;
}