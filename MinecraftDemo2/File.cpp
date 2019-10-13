#include "File.h"

string File::readFile(const char* file)
{
	string fileContent;
	ifstream iFile;

	iFile.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		iFile.open(file);
		stringstream fileStream;
		fileStream << iFile.rdbuf();
		iFile.close();
		fileContent = fileStream.str();
	}
	catch (ifstream::failure e) {
		cout << "Unable to read file" << endl;
		return string();
	}

	return fileContent;
}
