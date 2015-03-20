#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Entry.h"
#include "Handler.h"
#define MAX_NUM 100


Handler::Handler(int num)
	:personNum(num)
{}

void Handler::Display()
{
	for (std::vector<Entry>::iterator it = p1.begin(); it != p1.end(); ++it)
		(*it).ShowEntryInfo();
}

void Handler::AddPerson()
{
	file.open("a.txt", std::ios::in);
	std::string *a[MAX_NUM];
	for (int i = 0; !file.eof(); i++){
		a[i] = read(file);
		Entry person(a[i][0], a[i][1], a[i][2]);
		p1.push_back(person);
		//person.ShowEntryInfo();
		//personNum++;
	}
	delete[]a;
	file.close();
}
void Handler::Sort()
{
	std::sort(p1.begin(), p1.end());
}



std::string* read(std::ifstream &file)
{

	std::string  *arr = NULL;
	if (file.is_open() == false)
	{
		std::cout << "현재 정보가 없습니다. " << std::endl;
	}
	else{
			std::string word;
			std::getline(file, word);;
			std::string delimiter = " ";
			size_t pos = 0;
			arr = new std::string[3];
			std::string token;
			int i = 0;
			while ((pos = word.find(delimiter)) != std::string::npos) {
				token = word.substr(0, pos);
				arr[i] = token;
				i++;
				word.erase(0, pos + delimiter.length());
			}
			arr[i] = word;
	}
	return arr;
}
