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
	for (std::vector<Entry>::iterator it = v1.begin(); it != v1.end(); ++it)
		(*it).ShowEntryInfo();
}
void Handler::AddPerson()
{
	file.open("a.txt", std::ios::in);
	while(!file.eof()){
		std::string *a = NULL;
		a = read(file);
		Entry person(a[0], a[1], a[2]);
		v1.push_back(person);
		//person.ShowEntryInfo();
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
