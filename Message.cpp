#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>

#include "Contacts.h"
#include "Message.h"


// 메세지 목록 출력
void SMSHandler::display(ContactHandler &myContacts) const {
	if (_messages.empty()) {
		std::cout << "메세지가 없습니다." << std::endl;
		return;
	}
	while (true) {
		int n, index = 1;
		std::cout << "번호" << "\t" << "이름/전화번호" << "\t" << "메세지" << std::endl;
		for (std::list<SMS>::const_iterator it = _messages.begin(); it != _messages.end(); ++it, ++index) {
			std::cout << index << "\t" << myContacts.find(it->number()) << "\t";
			if (it->text().length() <= 20) {
				std::cout << it->text() << std::endl;
			}
			else {
				std::cout << it->text().substr(0, 20);
				std::cout << " …" << std::endl;
			}
		}
		std::cout << "\n" << "읽을 메세지의 번호를 입력하세요." << std::endl;
		std::cout << "잘못된 번호를 입력할 경우 상위 메뉴로 돌아갑니다." << std::endl;
		std::cout << ">> ";
		std::cin >> n;
		if (0 < n && n < index) displaySMS(n, myContacts);
		else break;
	}
}

// 단일 메세지 보기
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

// 메세지 전송
void OutgoingSMS::send() {
	std::string targetNum, text;

	std::cout << "받는 사람(전화번호): ";
	std::cin >> targetNum;

	std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
	if (std::regex_match(targetNum, rgx_num) == false) {
		std::cout << "입력에 실패했습니다." << std::endl;
		std::cout << "입력 예시) 010-1234-5678 / 02-123-4567" << std::endl;
		return;
	}

	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "메세지 내용" << std::endl;
	std::cout << ">> ";
	std::getline(std::cin, text);
	SMS tmpSMS(targetNum, text);
	_messages.push_front(tmpSMS);
}

// 보낸 메세지 파일의 내용을 내부 메모리에 로드
void OutgoingSMS::import() {
	_messages.clear();
	std::ifstream openFile("OutgoingSMS.txt");
	if (openFile.is_open() == false) {
		std::cout << "OutgoingSMS.txt 파일을 열지 못했습니다. 작업을 중단합니다." << std::endl;
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

// 받은 메세지 파일의 내용을 내부 메모리에 로드
void ImcomingSMS::import() {
	_messages.clear();
	std::ifstream openFile("IncomingSMS.txt");
	if (openFile.is_open() == false) {
		std::cout << "IncomingSMS.txt 파일을 열지 못했습니다. 작업을 중단합니다." << std::endl;
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