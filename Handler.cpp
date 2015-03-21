#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Entry.h"
#include "Handler.h"
#define MAX_NUM 100

using namespace std;

Handler::Handler(int num)
:personNum(num)
{}

void Handler::Display()
{
	for (map<string, Entry>::iterator it = Entries.begin(); it != Entries.end(); ++it)
		cout << (*it).first << endl;
}
void Handler::AddPerson()
{
	file.open("input.txt",ios::in);
	while(!file.eof()){
		string *a = NULL;
		a = read(file);
		Entry person(a[0], a[1], a[2]);
		Entries.insert(std::pair<string, Entry>(a[0], person));
		person.ShowEntryInfo();
		personNum++;
		delete[]a;
	}
	file.close();

}
/*void Handler::Sort()
{
	std::sort(v1.begin(), v1.end());
}*/
Handler::~Handler()
{
}


string* read(std::ifstream &file)
{

	string  *arr = NULL;
	if (file.is_open() == false)
	{
		std::cout << "현재 정보가 없습니다. " << std::endl;
	}
	else{
			string word;
			getline(file, word);;
			string delimiter = " ";
			size_t pos = 0;
			arr = new std::string[3];
			std::string token;
			int i = 0;
			while ((pos = word.find(delimiter)) != string::npos) {
				token = word.substr(0, pos);
				arr[i] = token;
				i++;
				word.erase(0, pos + delimiter.length());
			}
			arr[i] = word;
	}
	return arr;
}

void WriteOutEntries(string fileName, Handler *myHandler) {
	ofstream outFile(fileName.data());
	
	
	for (map<string, Entry>::iterator it = myHandler->Entries.begin();
		it != myHandler->Entries.end(); ++it) {
		outFile << (*it).second.EntryName() << ' '
				<< (*it).second.EntryNumber() << ' '
				<< (*it).second.EntryEmail() << endl;
	}
}