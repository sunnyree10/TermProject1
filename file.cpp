#include <string>
#include <iostream>
#include <regex>
#include <map>
#include <fstream>

#include "file.h"
#include "Handler.h"

using namespace std;

string* ReadInputData(std::ifstream &file) {
	string  *arr = NULL;
	if (file.is_open() == false) {
		cout << "현재 정보가 없습니다. " << endl;
	}
	else {
		string word;
		getline(file, word);
		smatch m;
		regex e3("\\w+@\\w+\\.\\w+\\.*\\w*");//이메일
		regex e2("\\d{2,3}-\\d{3,4}-\\d{4}");//전화번호
		regex e1("\\b[a-zA-Z]+\\s*[a-zA-Z]*\\s*[a-zA-Z]*");//이름
		regex e[3] = { e1, e2, e3 };
		arr = new string[3];
		for (int i = 0; i < 3; i++)
		{
			regex_search(word, m, e[i]);
			arr[i] = m.str();
		}
	}
	return arr;
}

// 연락처 정보를 파일로 내보내는 함수
void WriteOutEntries(string fileName, Handler &myHandler) {
	std::ofstream outFile(fileName.data(), ios::app);
	std::map<std::string, Entry> Person = myHandler.EntryData();

	for (std::map<string, Entry>::iterator it = Person.begin();
		it != Person.end(); ++it) {
		outFile << (*it).second.EntryName() << ' '
			<< (*it).second.EntryNumber() << ' '
			<< (*it).second.EntryEmail() << endl;
	}
}