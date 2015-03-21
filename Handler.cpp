#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Handler.h"

using namespace std;

// 연락처 정보를 저장
Entry::Entry(string name, string number, string email) {
	_name = name;
	_number = number;
	_email = email;
}


Handler::Handler(int num)
:personNum(num)
{}

// 연락처 정보를 출력하는 함수
void Handler::Display() {
	cout << "이름\t" << "전화번호\t" << "이메일" << endl;
	for (map<string, Entry>::iterator itEntries = Entries.begin(); itEntries != Entries.end(); ++itEntries) {
		cout << (*itEntries).second.EntryName() << "\t"
			 << (*itEntries).second.EntryNumber() << "\t"
			 << (*itEntries).second.EntryEmail() << endl;
	}
}

// 
void Handler::AddPerson() {
	file.open("input.txt",ios::in);
	while(!file.eof()){
		string *a = NULL;
		a = read(file);
		Entry person(a[0], a[1], a[2]);
		Entries.insert(std::pair<string, Entry>(a[0], person));
		personNum++;
		delete[]a;
	}
	file.close();

}

string* read(std::ifstream &file) {
	string  *arr = NULL;
	if (file.is_open() == false) {
		std::cout << "현재 정보가 없습니다. " << std::endl;
	}
	else {
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

// 연락처 정보를 파일로 내보내는 함수
void WriteOutEntries(string fileName, Handler *myHandler) {
	ofstream outFile(fileName.data());
	for (map<string, Entry>::iterator it = myHandler->Entries.begin();
		it != myHandler->Entries.end(); ++it) {
		outFile << (*it).second.EntryName() << ' '
				<< (*it).second.EntryNumber() << ' '
				<< (*it).second.EntryEmail() << endl;
	}
}