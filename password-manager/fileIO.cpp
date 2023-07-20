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

bool FileIO::getIsFound()
{
	return this->isFound;
}

vector<string> FileIO::getFileContent()
{
	return this->fileContent;
}
//
//vector<string>::iterator getIterator()
//{
//	return 
//}

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
	if (changeWhat == CHANGE_PASS)
	{

	}

	// case for changing username
	else if (changeWhat == CHANGE_USER)
	{

	}
	return 0;
}


// overloaded function
int FileIO::changeInFile(string whichWebsite, string username, string password)
{
	// case for changing both
	return 0;
}

int FileIO::deleteInFile(string whichWebsite)
{
	// read the contents of the file in a vector
	//ifstream input_file(PASSWORD_FILE);
	//vector<string> fileContent;
	this->isFound = false;

	checkIfExists(whichWebsite, isFound, this->fileContent, this->iterator);	// check if website exists in file

	//if (!input_file)
	//{
	//	cerr << "Error opening file" << endl;
	//}
	//else
	//{
	//	string eachLine;
	//	while (getline(input_file, eachLine))
	//	{
	//		fileContent.push_back(eachLine);
	//	}

	//	input_file.close();	

	//	// search the vector for said website
	//	bool isFound = false;
	//	for (auto iterator = fileContent.begin(); iterator != fileContent.end(); iterator++)
	//	{
	//		if (*iterator == whichWebsite)
	//		{
	//			fileContent.erase(iterator);
	//			isFound = true;
	//			break;
	//		}
	//	}

	if (this->isFound)
	{
		this->fileContent.erase(iterator);

		// write modified content to passwd file
		ofstream output_file(PASSWORD_FILE);

		if (!output_file)
		{
			cerr << "Error opening file" << endl;
		}
		else
		{
			for (const auto& eachLine : fileContent)
			{
				output_file << eachLine << endl;
			}
			output_file.close();

			return SUCCESS;
		}
	}

	return FAIL;
}

void FileIO::checkIfExists(string whichWebsite, bool& isFound, vector<string> &fileContent, vector<string>::iterator& iterator)
{
	// read the contents of the file in a vector
	ifstream input_file(PASSWORD_FILE);

	if (!input_file)
	{
		cerr << "Error opening file" << endl;
	}
	else
	{
		string eachLine;
		while (getline(input_file, eachLine))
		{
			fileContent.push_back(eachLine);
		}

		input_file.close();

		// search the vector for said website
		iterator = find(fileContent.begin(), fileContent.end(), whichWebsite);
		isFound = (iterator != fileContent.end());
	}
}
