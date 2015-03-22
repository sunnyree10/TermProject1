#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "Handler.h"
#include "file.h"
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
	std::ifstream file;
	file.open("input.txt", ios::in);
	while (!file.eof()){
		string *a = NULL;
		a = ReadInputData(file);
		Entry person(a[0], a[1], a[2]);
		Entries.insert(std::pair<string, Entry>(a[0], person));
		personNum++;
		delete[]a;
	}
	file.close();

}

std::map<std::string, Entry> Handler::ReturnEntries()
{
	return Entries;
}