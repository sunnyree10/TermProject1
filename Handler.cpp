#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "Handler.h"
#include "file.h"

// ����ó ������ ����
Entry::Entry(std::string name, std::string number, std::string email) {
	_name = name;
	_number = number;
	_email = email;
}


// ����ó ������ ����ϴ� �Լ�
void Handler::DisplayEntries() {
	std::cout << "�̸�\t" << "��ȭ��ȣ\t" << "�̸���" << std::endl;
	for (std::map<std::string, Entry>::iterator itEntries = Entries.begin(); itEntries != Entries.end(); ++itEntries) {
		std::cout << itEntries->second.EntryName() << "\t"
				  << itEntries->second.EntryNumber() << "\t"
				  << itEntries->second.EntryEmail() << std::endl;
	}
}

// ���Ͽ��� ����ó ������ �������� �Լ�
void Handler::GetEntriesFromFile() {
	std::ifstream openFile("input.txt");
	while (!openFile.eof()){
		std::string *data = NULL;
		data = ReadInputData(openFile);
		Entry tmpEntry(data[0], data[1], data[2]);
		Entries.insert(std::pair<std::string, Entry>(data[0], tmpEntry));
		++personNum;
		delete[] data;
	}
	openFile.close();
}

// �̸����� ����ó�� �˻��ϴ� �Լ�
std::map<std::string, Entry>::iterator Handler::FindEntryWithName() {
	std::string name;
	std::cout << "�̸����� �˻�: ";
	std::cin >> name;
	std::map<std::string, Entry>::iterator findEntry = Entries.find(name);
	if (findEntry != Entries.end()) {
		std::cout << "�̸�\t" << "��ȭ��ȣ\t" << "�̸���" << std::endl;
		std::cout << findEntry->second.EntryName() << "\t"
				  << findEntry->second.EntryNumber() << "\t"
				  << findEntry->second.EntryEmail() << std::endl;
	}
	else {
		std::cout << "�˻� ����� �����ϴ�." << std::endl;
	}

	return findEntry;
}