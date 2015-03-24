#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

#include "Contacts.h"


// ����ó �߰�
void ContactHandler::add() {
	std::string name, number, email;

	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "�̸�: ";
	std::getline(std::cin, name);
	std::regex rgx_name("([a-zA-Z]+(\\s*[a-zA-Z])+)");
	if (std::regex_match(name, rgx_name) == false) {
		std::cout << "�Է¿� �����߽��ϴ�." << std::endl;
		std::cout << "�Է� ����) Suntae / Ko Ji Hun" << std::endl;
		return;
	}
	std::cout << "��ȭ��ȣ: ";
	std::cin >> number;
	std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
	if (std::regex_match(number, rgx_num) == false) {
		std::cout << "�Է¿� �����߽��ϴ�." << std::endl;
		std::cout << "�Է� ����) 010-1234-5678 / 02-123-4567" << std::endl;
		return;
	}
	std::cout << "�̸��� �ּ�: ";
	std::cin >> email;
	std::regex rgx_email("\\w+@\\w+\\.\\w+\\.?\\w*");
	if (std::regex_match(email, rgx_email) == false) {
		std::cout << "�Է¿� �����߽��ϴ�." << std::endl;
		std::cout << "�Է� ����) admin@example.com / admin@example.co.kr" << std::endl;
		return;
	}

	Contact tmpContact(name, number, email);
	_contacts.insert(std::pair<std::string, Contact>(name, tmpContact));
}

// ���� ������ ���� �޸𸮿� �ε�
void ContactHandler::import() {
	_contacts.clear();
	std::ifstream openFile("Contacts.txt");
	if (openFile.is_open() == false) {
		std::cout << "contacts.txt ������ ���� ���߽��ϴ�. �۾��� �ߴ��մϴ�." << std::endl;
	}
	else {
		while (!openFile.eof()){
			std::string data[3], oneLine;
			std::getline(openFile, oneLine);
			std::smatch m;
			std::regex rgx_name("([a-zA-Z]+(\\s*[a-zA-Z])+)|[��-�R]+");
			std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
			std::regex rgx_email("\\w+@\\w+\\.\\w+\\.*\\w*");
			std::regex rgx[3] = { rgx_name, rgx_num, rgx_email };
			for (int i = 0; i < 3; ++i) {
				std::regex_search(oneLine, m, rgx[i]);
				data[i] = m.str();
			}
			Contact tmpContact(data[0], data[1], data[2]);
			_contacts.insert(std::pair<std::string, Contact>(data[0], tmpContact));
		}
		openFile.close();
		std::cout << "����ó�� ���������� �ҷ��Խ��ϴ�." << std::endl;
	}
}

// ����ó ��� ���
void ContactHandler::display() const {
	if (_contacts.empty()) {
		std::cout << "����ó�� �����ϴ�." << std::endl;
		return;
	}
	std::cout << "�� " << _contacts.size() << "���� ����ó" << std::endl;
	std::cout << "�̸�" << "\t\t" << "��ȭ��ȣ" << "\t" << "�̸���" << std::endl;
	for (std::map<std::string, Contact>::const_iterator it = _contacts.begin(); it != _contacts.end(); ++it) {
		std::cout << it->second.name() << "\t\t"
				  << it->second.number() << "\t"
				  << it->second.email() << std::endl;
	}
}

// �̸�, ��ȭ��ȣ�� ����ó �˻�
std::map<std::string, Contact>::const_iterator ContactHandler::find() const {
	std::string data;
	std::regex num("\\d{2,3}-\\d{3,4}-\\d{4}");
	std::map<std::string, Contact>::const_iterator findContact;

	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "�̸� �Ǵ� ��ȭ��ȣ�� ����ó�� �˻��մϴ�." << std::endl;
	std::cout << "��ȭ��ȣ�� ������(-)�� �����Ͽ� �Է����ּ���." << std::endl;
	std::cout << "�̸� �Ǵ� ��ȭ��ȣ: ";
	std::getline(std::cin, data);

	std::cout << std::endl;

	// �Է� �����Ͱ� ��ȭ��ȣ�� ���
	if (std::regex_match(data, num) == true) {
		for (findContact = _contacts.begin(); findContact != _contacts.end() && data.compare(findContact->second.number()); ++findContact);
		if (findContact != _contacts.end()) {
			std::cout << "�̸�" << "\t\t" << "��ȭ��ȣ" << "\t" << "�̸���" << std::endl;
			std::cout << findContact->second.name() << "\t\t"
					  << findContact->second.number() << "\t"
					  << findContact->second.email() << std::endl;
		}
		else{
			std::cout << "�˻� ����� �����ϴ�." << std::endl;
		}
	}
	// �Է� �����Ͱ� ��ȭ��ȣ�� �ƴ� ��� �̸����� ����
	else {
		findContact = _contacts.find(data);
		if (findContact != _contacts.end()) {
			std::cout << "�̸�" << "\t\t" << "��ȭ��ȣ" << "\t" << "�̸���" << std::endl;
			std::cout << findContact->second.name() << "\t\t"
					  << findContact->second.number() << "\t"
					  << findContact->second.email() << std::endl;
		}
		else {
			std::cout << "�˻� ����� ���ų� �Է� ������ �ùٸ��� �ʽ��ϴ�." << std::endl;
		}
	}

	return findContact;
}

// ��ȭ��ȣ�� �˻��Ͽ� �ش��ϴ� �̸� ����
std::string ContactHandler::find(std::string number) const {
	std::map<std::string, Contact>::const_iterator findContact;
	for (findContact = _contacts.begin(); findContact != _contacts.end() && number.compare(findContact->second.number()); ++findContact);
	if (findContact != _contacts.end()) return findContact->first;
	else return number;
}