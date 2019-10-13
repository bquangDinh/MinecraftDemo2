#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class File
{
public:
	static string readFile(const char* file);
};

