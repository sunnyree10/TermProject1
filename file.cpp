#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <regex>

#include "Handler.h"
#include "message.h"
#include "file.h"

std::string* ReadInputData(std::ifstream &file) {
	std::string *arr = NULL;
	if (file.is_open() == false) {
		std::cout << "���� ������ �����ϴ�. " << std::endl;
	}
	else {
		std::string word;
		std::getline(file, word);
		std::smatch m;
		std::regex e3("\\w+@\\w+\\.\\w+\\.*\\w*"); //�̸���
		std::regex e2("\\d{2,3}-\\d{3,4}-\\d{4}"); //��ȭ��ȣ
		std::regex e1("[a-zA-Z]+\\s*[a-zA-Z]+"); //�̸�
		std::regex e[3] = { e1, e2, e3 };
		arr = new std::string[3];
		for (int i = 0; i < 3; ++i) {
			std::regex_search(word, m, e[i]);
			arr[i] = m.str();
		}
	}
	return arr;
}

// ����ó�� ���Ϸ� �������� �Լ�
void WriteOutEntries(Handler &myHandler) {
	std::ofstream outFile("entries.txt");
	std::map<std::string, Entry> Person = myHandler.EntryData();

	for (std::map<std::string, Entry>::iterator it = Person.begin(); it != Person.end(); ++it) {
		if (it != Person.begin()) outFile << std::endl;
		outFile << (*it).second.EntryName() << ' '
				<< (*it).second.EntryNumber() << ' '
				<< (*it).second.EntryEmail();
	}
}

// ���Ͽ��� SMS�� �о���� �Լ�
std::string* ReadSMSFromFile(std::ifstream &file) {
	std::string *arr = NULL;
	if (file.is_open() == false) {
		std::cout << "���� �޼��� ������ �����ϴ�. " << std::endl;
	}
	else {
		std::string data;
		std::getline(file, data);
		arr = new std::string[2];
		std::smatch m;
		std::regex num("\\d{2,3}-\\d{3,4}-\\d{4}"); // ��ȭ��ȣ
		std::regex_search(data, m, num);
		arr[0] = m.str();
		arr[1] = data.substr(arr[0].length() + 1);
	}

	return arr;
}

// SMS�� ���Ϸ� �������� �Լ�
void WriteOutSMS(SMSHandler &mySMSbox) {
	std::ofstream outFile("sentsms.txt");
	std::list<SMS> tmpSMS = mySMSbox.SentSMS();
	for (std::list<SMS>::iterator itSMS = tmpSMS.begin(); itSMS != tmpSMS.end(); ++itSMS) {
		if (itSMS != tmpSMS.begin()) outFile << std::endl;
		outFile << (*itSMS).TargetNumber() << ' '
				<< (*itSMS).SMSText();
	}
}