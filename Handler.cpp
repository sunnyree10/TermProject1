#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Handler.h"

using namespace std;

// ����ó ������ ����
Entry::Entry(string name, string number, string email) {
	_name = name;
	_number = number;
	_email = email;
}


Handler::Handler(int num)
:personNum(num)
{}

// ����ó ������ ����ϴ� �Լ�
void Handler::Display() {
	cout << "�̸�\t" << "��ȭ��ȣ\t" << "�̸���" << endl;
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
		std::cout << "���� ������ �����ϴ�. " << std::endl;
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

// ����ó ������ ���Ϸ� �������� �Լ�
void WriteOutEntries(string fileName, Handler *myHandler) {
	ofstream outFile(fileName.data());
	for (map<string, Entry>::iterator it = myHandler->Entries.begin();
		it != myHandler->Entries.end(); ++it) {
		outFile << (*it).second.EntryName() << ' '
				<< (*it).second.EntryNumber() << ' '
				<< (*it).second.EntryEmail() << endl;
	}
}