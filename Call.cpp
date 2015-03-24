#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>

#include "Contacts.h"
#include "Call.h"


// ���� ������ ���� �޸𸮿� �ε�
void CallHandler::import() {
	_record.clear();
	std::ifstream openFile("Calls.txt");
	if (openFile.is_open() == false) {
		std::cout << "Calls.txt ������ ���� ���߽��ϴ�. �۾��� �ߴ��մϴ�." << std::endl;
	}
	else {
		while (!openFile.eof()){
			std::string oneLine;
			std::getline(openFile, oneLine);
			CallEntry tmpEntry(oneLine[0]-'0', oneLine.substr(2));
			_record.push_back(tmpEntry);
		}
		openFile.close();
	}
}

// ������ȭ �׽�Ʈ
void CallHandler::simulate(std::string sender_number, ContactHandler &myContacts) const {
	int state;
	std::string name = myContacts.find(sender_number);
	
	std::cout << "���� ��..." << std::endl;
	if (sender_number == name)
		std::cout << sender_number << " [�𸣴� ��ȣ]" << std::endl;
	else
		std::cout << name << " [" << sender_number << ']' << std::endl;

	std::cout << "0 <- ���� | |  ��ȭ -> 1" << std::endl;
	std::cout << ">> ";
	std::cin >> state;
	if (state == 0)
		std::cout << "��ȭ�� �����߽��ϴ�." << std::endl;
	else if (state == 1)
		std::cout << "��ȭ�� �޾ҽ��ϴ�." << std::endl;
	else
		std::cout << "�߸��� �Է��Դϴ�." << std::endl;

	std::cout << "\n" << "��ȭ ���� �׽�Ʈ�� �����մϴ�." << std::endl;
}

// ��ȭ��� ���
void CallHandler::display(ContactHandler &myContacts) const {
	if (_record.empty()) {
		std::cout << "��ȭ ����� �����ϴ�." << std::endl;
		return;
	}
	for (std::list<CallEntry>::const_iterator it = _record.begin(); it != _record.end(); ++it) {
		switch (it->state()) {
		case 0:
			std::cout << "������";
			break;
		case 1:
			std::cout << "�� ��";
			break;
		case 2:
			std::cout << "�� ��";
			break;
		case 3:
			std::cout << "������";
			break;
		case 4:
			std::cout << "��ҵ�";
			break;
		}
		std::cout << "\t";
		if (it->number() == myContacts.find(it->number()))
			std::cout << it->number() << std::endl;
		else
			std::cout << myContacts.find(it->number()) << " [" << it->number() << ']' << std::endl;
	}
	std::cout << std::endl;
}

// ��ȭ��� �߰�
void CallHandler::add_dev() {
	int state;
	std::string number;
	std::cout << "��ȭ ����� �߰��մϴ�." << std::endl;
	std::cout << "���� - 0: ������ / 1 : ���� / 2 : �߽� / 3 : ������ / 4 : ��ҵ�" << std::endl;
	std::cout << ">> ";
	std::cin >> state;
	if (state < 0 || state > 4) {
		std::cout << "�߸��� �Է��Դϴ�." << std::endl;
		return;
	}
	std::cout << "��ȭ��ȣ: ";
	std::cin >> number;
	std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
	if (regex_match(number, rgx_num) == false) {
		std::cout << "�Է¿� �����߽��ϴ�." << std::endl;
		std::cout << "�Է� ����) 010-1234-5678 / 02-123-4567" << std::endl;
		return;
	}
	CallEntry tmpCall(state, number);
	_record.push_front(tmpCall);
}