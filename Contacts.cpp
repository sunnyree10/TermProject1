#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

#include "Contacts.h"


// 연락처 추가
void ContactHandler::add() {
	std::string name, number, email;

	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "이름: ";
	std::getline(std::cin, name);
	std::regex rgx_name("([a-zA-Z]+(\\s*[a-zA-Z])+)");
	if (std::regex_match(name, rgx_name) == false) {
		std::cout << "입력에 실패했습니다." << std::endl;
		std::cout << "입력 예시) Suntae / Ko Ji Hun" << std::endl;
		return;
	}
	std::cout << "전화번호: ";
	std::cin >> number;
	std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
	if (std::regex_match(number, rgx_num) == false) {
		std::cout << "입력에 실패했습니다." << std::endl;
		std::cout << "입력 예시) 010-1234-5678 / 02-123-4567" << std::endl;
		return;
	}
	std::cout << "이메일 주소: ";
	std::cin >> email;
	std::regex rgx_email("\\w+@\\w+\\.\\w+\\.?\\w*");
	if (std::regex_match(email, rgx_email) == false) {
		std::cout << "입력에 실패했습니다." << std::endl;
		std::cout << "입력 예시) admin@example.com / admin@example.co.kr" << std::endl;
		return;
	}

	Contact tmpContact(name, number, email);
	_contacts.insert(std::pair<std::string, Contact>(name, tmpContact));
}

// 파일 내용을 내부 메모리에 로드
void ContactHandler::import() {
	_contacts.clear();
	std::ifstream openFile("Contacts.txt");
	if (openFile.is_open() == false) {
		std::cout << "contacts.txt 파일을 열지 못했습니다. 작업을 중단합니다." << std::endl;
	}
	else {
		while (!openFile.eof()){
			std::string data[3], oneLine;
			std::getline(openFile, oneLine);
			std::smatch m;
			std::regex rgx_name("([a-zA-Z]+(\\s*[a-zA-Z])+)|[가-힣]+");
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
		std::cout << "연락처를 성공적으로 불러왔습니다." << std::endl;
	}
}

// 연락처 목록 출력
void ContactHandler::display() const {
	if (_contacts.empty()) {
		std::cout << "연락처가 없습니다." << std::endl;
		return;
	}
	std::cout << "총 " << _contacts.size() << "개의 연락처" << std::endl;
	std::cout << "이름" << "\t\t" << "전화번호" << "\t" << "이메일" << std::endl;
	for (std::map<std::string, Contact>::const_iterator it = _contacts.begin(); it != _contacts.end(); ++it) {
		std::cout << it->second.name() << "\t\t"
				  << it->second.number() << "\t"
				  << it->second.email() << std::endl;
	}
}

// 이름, 전화번호로 연락처 검색
std::map<std::string, Contact>::const_iterator ContactHandler::find() const {
	std::string data;
	std::regex num("\\d{2,3}-\\d{3,4}-\\d{4}");
	std::map<std::string, Contact>::const_iterator findContact;

	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "이름 또는 전화번호로 연락처를 검색합니다." << std::endl;
	std::cout << "전화번호는 하이픈(-)을 포함하여 입력해주세요." << std::endl;
	std::cout << "이름 또는 전화번호: ";
	std::getline(std::cin, data);

	std::cout << std::endl;

	// 입력 데이터가 전화번호일 경우
	if (std::regex_match(data, num) == true) {
		for (findContact = _contacts.begin(); findContact != _contacts.end() && data.compare(findContact->second.number()); ++findContact);
		if (findContact != _contacts.end()) {
			std::cout << "이름" << "\t\t" << "전화번호" << "\t" << "이메일" << std::endl;
			std::cout << findContact->second.name() << "\t\t"
					  << findContact->second.number() << "\t"
					  << findContact->second.email() << std::endl;
		}
		else{
			std::cout << "검색 결과가 없습니다." << std::endl;
		}
	}
	// 입력 데이터가 전화번호가 아닐 경우 이름으로 간주
	else {
		findContact = _contacts.find(data);
		if (findContact != _contacts.end()) {
			std::cout << "이름" << "\t\t" << "전화번호" << "\t" << "이메일" << std::endl;
			std::cout << findContact->second.name() << "\t\t"
					  << findContact->second.number() << "\t"
					  << findContact->second.email() << std::endl;
		}
		else {
			std::cout << "검색 결과가 없거나 입력 형식이 올바르지 않습니다." << std::endl;
		}
	}

	return findContact;
}

// 전화번호를 검색하여 해당하는 이름 리턴
std::string ContactHandler::find(std::string number) const {
	std::map<std::string, Contact>::const_iterator findContact;
	for (findContact = _contacts.begin(); findContact != _contacts.end() && number.compare(findContact->second.number()); ++findContact);
	if (findContact != _contacts.end()) return findContact->first;
	else return number;
}