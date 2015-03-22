#include <iostream>
#include <string>

#include "Handler.h"
#include "file.h"

using namespace std;

int main()
{
	Handler h1;
	h1.GetEntriesFromFile();
	h1.DisplayEntries();
	string fileName = "output.txt";
	WriteOutEntries(fileName, h1);
	return 0;
}