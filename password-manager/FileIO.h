#pragma once
#ifndef _FIO_H_
#define _FIO_H_
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class FileIO
{
public:
	FileIO(void);
	~FileIO();

	int appendToFile(string whichWebsite, string loginCreds);
	int deleteInFile(string whichWebsite);	// delete credential or update
	int changeInFile(string whichWebsite, string loginCreds, int changeWhat);	// update credential

private:
	string fileName;
	struct stat buffer;
	bool doesFileExist;
};

#endif