#include "Common.h"
#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>	// to check if file exists
#include <stdbool.h>
#include <unordered_map>
#pragma warning (disable:4996)

using namespace std;

// constructor
FileIO::FileIO(void)
{
	this->fileName = PASSWORD_FILE;
	this->doesFileExist = false;
}

// destructor
FileIO::~FileIO(void)
{

}

int FileIO::appendToFile(string whichWebsite, string loginCreds)
{	
	ofstream file_stream(PASSWORD_FILE, ios::app);	// open file in append mode, if file doesn't exist create one

	if (!file_stream)
	{
		return FAIL;	// error opening file
	}
	else
	{
		file_stream << "[" << whichWebsite << "]" << loginCreds << endl;
		file_stream.close();
		return SUCCESS;
	}
}

int FileIO::changeInFile(string whichWebsite, string loginCreds, int changeWhat)
{
	// case for changing passwd

	// case for changing username

	// case for changing both
}

int FileIO::deleteInFile(string whichWebsite)
{


}