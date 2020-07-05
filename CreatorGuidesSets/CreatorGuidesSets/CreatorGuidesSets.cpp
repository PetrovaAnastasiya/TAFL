#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <regex>

using namespace std;
#define neterminal string

bool openFile(ifstream& file, string fileName)
{
	file.open(fileName);
	if (file.is_open())
		return true;
	else
	{
		return false;
	}
}

string readInputData()
{
	const string FILE_IN_NAME = "input.txt";

	ifstream fileForWork;
	bool is_opened = openFile(fileForWork, FILE_IN_NAME);
	
	fileForWork.close();
}

int main()
{
	string 
}