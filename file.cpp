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
		cout << "���� ������ �����ϴ�. " << endl;
	}
	else {
		string word;
		getline(file, word);
		smatch m;
		regex e3("\\w+@\\w+\\.\\w+\\.*\\w*");//�̸���
		regex e2("\\d{3}-\\d{4}-\\d{4}");//��ȭ��ȣ
		regex e1("\\b[a-zA-Z]+\\s*[a-zA-Z]*\\s*[a-zA-Z]*");//�̸�
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

// ����ó ������ ���Ϸ� �������� �Լ�
void WriteOutEntries(string fileName, Handler &myHandler) {
	std::ofstream outFile(fileName.data(), ios::app);
	std::map<std::string, Entry> Person = myHandler.ReturnEntries();

	for (std::map<string, Entry>::iterator it = Person.begin();
		it != Person.end(); ++it) {
		outFile << (*it).second.EntryName() << ' '
			<< (*it).second.EntryNumber() << ' '
			<< (*it).second.EntryEmail() << endl;
	}
}