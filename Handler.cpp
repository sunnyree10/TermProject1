#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "Handler.h"
#include "file.h"

// Entry ������: ����ó ������ ����
Entry::Entry(std::string name, std::string number, std::string email) {
	_name = name;
	_number = number;
	_email = email;
}


// ����ó�� �߰��ϴ� �Լ�
void Handler::AddEntry() {
	std::string *data;
	data = new std::string[3];
	std::cout << "����ó�� �߰��մϴ�." << std::endl;
	
	// ���� �ʿ�
	std::cout << "�̸�: ";
	
	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::getline(std::cin, data[0]);
	
	while (true) {
		std::cout << "��ȭ��ȣ: ";
		std::cin >> data[1];
		std::regex num("\\d{2,3}-\\d{3,4}-\\d{4}");
		if (std::regex_match(data[1], num) != true) {
			std::cout << "�Է��� �߸��Ǿ����ϴ�. �Է� ����: 010-1234-5678" << std::endl;
			continue;
		}
		else break;
	}
	while (true) {
		std::cout << "�̸���: ";
		std::cin >> data[2];
		std::regex em("\\w+@\\w+\\.\\w+\\.?\\w*");
		if (std::regex_match(data[2], em) != true) {
			std::cout << "�Է��� �߸��Ǿ����ϴ�. �Է� ����: example@example.com �Ǵ� .co.kr" << std::endl;
			continue;
		}
		else break;
	}
	Entry tmpEntry(data[0], data[1], data[2]);
	Entries.insert(std::pair<std::string, Entry>(data[0], tmpEntry));
	++personNum;
}

// ����ó ������ ����ϴ� �Լ�
void Handler::DisplayEntries() {
	std::cout << std::endl;
	std::cout << "�� " << personNum << "���� ����ó" << std::endl;
	std::cout << "�̸�\t\t" << "��ȭ��ȣ\t" << "�̸���" << std::endl;
	for (std::map<std::string, Entry>::iterator itEntries = Entries.begin(); itEntries != Entries.end(); ++itEntries) {
		std::cout << itEntries->second.EntryName() << "\t\t"
				  << itEntries->second.EntryNumber() << "\t"
				  << itEntries->second.EntryEmail() << std::endl;
	}
}

// ������ ������ ���� �޸𸮿� �ҷ����� �Լ�
void Handler::GetEntriesFromFile() {
	Entries.clear();
	std::ifstream openFile("entries.txt");
	while (!openFile.eof()){
		std::string *data = NULL;
		data = ReadInputData(openFile);
		Entry tmpEntry(data[0], data[1], data[2]);
		Entries.insert(std::pair<std::string, Entry>(data[0], tmpEntry));
		++personNum;
		delete[] data;
	}
	openFile.close();
	std::cout << "����ȭ �Ϸ�!" << std::endl;
}

// �̸� �Ǵ� ��ȭ��ȣ�� ����ó�� �˻��ϴ� �Լ�
std::map<std::string, Entry>::iterator Handler::FindEntry() {
	std::string data;
	std::regex num("\\d{2,3}-\\d{3,4}-\\d{4}");
	std::map<std::string, Entry>::iterator findEntry;

	std::cout << std::endl;
	std::cout << "�̸� �Ǵ� ��ȭ��ȣ�� ����ó�� �˻��մϴ�." << std::endl;
	std::cout << "��ȭ��ȣ�� ������(-)�� �����Ͽ� �Է����ּ���." << std::endl;
	
	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "�̸� �Ǵ� ��ȭ��ȣ: ";
	std::getline(std::cin, data);
	
	std::cout << std::endl;

	// �Է� �����Ͱ� ��ȭ��ȣ�� ���
	if (std::regex_match(data, num) == true) {
		for (findEntry = Entries.begin(); findEntry != Entries.end() && data.compare(findEntry->second.EntryNumber()); ++findEntry);
		if (findEntry != Entries.end()) {
			std::cout << "�̸�\t\t" << "��ȭ��ȣ\t" << "�̸���" << std::endl;
			std::cout << findEntry->second.EntryName() << "\t\t"
					  << findEntry->second.EntryNumber() << "\t"
					  << findEntry->second.EntryEmail() << std::endl;
		}
		else{
			std::cout << "�˻� ����� �����ϴ�." << std::endl;
		}
	}
	// �Է� �����Ͱ� ��ȭ��ȣ�� �ƴ� ��� �̸����� ����
	else {
		findEntry = Entries.find(data);
		if (findEntry != Entries.end()) {
			std::cout << "�̸�\t\t" << "��ȭ��ȣ\t" << "�̸���" << std::endl;
			std::cout << findEntry->second.EntryName() << "\t\t"
					  << findEntry->second.EntryNumber() << "\t"
					  << findEntry->second.EntryEmail() << std::endl;
		}
		else {
			std::cout << "�˻� ����� ���ų� �Է� ������ �ùٸ��� �ʽ��ϴ�." << std::endl;
		}
	}

	return findEntry;
}

// ��ȭ��ȣ�� �ش��ϴ� �̸��� �����ϴ� �Լ�
std::string Handler::GetNameFromNumber(std::string number) {
	std::map<std::string, Entry>::iterator findEntry;
	for (findEntry = Entries.begin(); findEntry != Entries.end() && number.compare(findEntry->second.EntryNumber()); ++findEntry);
	if (findEntry != Entries.end()) return findEntry->first;
	else return number;
}