#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>

#include "Contacts.h"
#include "Message.h"


// �޼��� ��� ���
void SMSHandler::display(ContactHandler &myContacts) const {
	if (_messages.empty()) {
		std::cout << "�޼����� �����ϴ�." << std::endl;
		return;
	}
	while (true) {
		int n, index = 1;
		std::cout << "��ȣ" << "\t" << "�̸�/��ȭ��ȣ" << "\t" << "�޼���" << std::endl;
		for (std::list<SMS>::const_iterator it = _messages.begin(); it != _messages.end(); ++it, ++index) {
			std::cout << index << "\t" << myContacts.find(it->number()) << "\t";
			if (it->text().length() <= 20) {
				std::cout << it->text() << std::endl;
			}
			else {
				std::cout << it->text().substr(0, 20);
				std::cout << " ��" << std::endl;
			}
		}
		std::cout << "\n" << "���� �޼����� ��ȣ�� �Է��ϼ���." << std::endl;
		std::cout << "�߸��� ��ȣ�� �Է��� ��� ���� �޴��� ���ư��ϴ�." << std::endl;
		std::cout << ">> ";
		std::cin >> n;
		if (0 < n && n < index) displaySMS(n, myContacts);
		else break;
	}
}

// ���� �޼��� ����
void SMSHandler::displaySMS(int index, ContactHandler &myContacts) const {
	int i = 1;
	std::list<SMS>::const_iterator findSMS;
	for (findSMS = _messages.begin(); i != index; ++findSMS, ++i);
	if (findSMS->number() == myContacts.find(findSMS->number()))
		std::cout << findSMS->number() << std::endl;
	else
		std::cout << myContacts.find(findSMS->number()) << " [" << findSMS->number() << ']' << std::endl;
	std::cout << findSMS->text() << "\n" << std::endl;
}

// �޼��� ����
void OutgoingSMS::send() {
	std::string targetNum, text;

	std::cout << "�޴� ���(��ȭ��ȣ): ";
	std::cin >> targetNum;

	std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
	if (std::regex_match(targetNum, rgx_num) == false) {
		std::cout << "�Է¿� �����߽��ϴ�." << std::endl;
		std::cout << "�Է� ����) 010-1234-5678 / 02-123-4567" << std::endl;
		return;
	}

	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "�޼��� ����" << std::endl;
	std::cout << ">> ";
	std::getline(std::cin, text);
	SMS tmpSMS(targetNum, text);
	_messages.push_front(tmpSMS);
}

// ���� �޼��� ������ ������ ���� �޸𸮿� �ε�
void OutgoingSMS::import() {
	_messages.clear();
	std::ifstream openFile("OutgoingSMS.txt");
	if (openFile.is_open() == false) {
		std::cout << "OutgoingSMS.txt ������ ���� ���߽��ϴ�. �۾��� �ߴ��մϴ�." << std::endl;
	}
	else {
		while (!openFile.eof()) {
			std::string oneLine;
			std::getline(openFile, oneLine);
			std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
			std::smatch m;
			std::regex_search(oneLine, m, rgx_num);
			SMS tmpSMS(m.str(), oneLine.substr(m.str().length() + 1));
			_messages.push_back(tmpSMS);
		}
		openFile.close();
	}
}

// ���� �޼��� ������ ������ ���� �޸𸮿� �ε�
void ImcomingSMS::import() {
	_messages.clear();
	std::ifstream openFile("IncomingSMS.txt");
	if (openFile.is_open() == false) {
		std::cout << "IncomingSMS.txt ������ ���� ���߽��ϴ�. �۾��� �ߴ��մϴ�." << std::endl;
	}
	else {
		while (!openFile.eof()) {
			std::string oneLine;
			std::getline(openFile, oneLine);
			std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
			std::smatch m;
			std::regex_search(oneLine, m, rgx_num);
			SMS tmpSMS(m.str(), oneLine.substr(m.str().length() + 1));
			_messages.push_back(tmpSMS);
		}
		openFile.close();
	}
}