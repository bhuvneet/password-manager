#pragma once
#ifndef _FIO_H_
#define _FIO_H_

#define CHANGE_USER	1
#define CHANGE_PASS	2

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
	int changeInFile(string whichWebsite, string username, string password);
	void checkIfExists(string whichWebsite, bool& isFound, vector<string>& fileContent, vector<string>::iterator& iterator);
	bool getIsFound();
	vector<string> getFileContent();
	vector<string>::iterator getIterator();

private:
	string fileName;
	struct stat buffer;
	bool doesFileExist;
	vector<string> fileContent;
	vector<string>::iterator iterator;
	bool isFound;
};

#endif