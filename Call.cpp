#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>

#include "Contacts.h"
#include "Call.h"


// 파일 내용을 내부 메모리에 로드
void CallHandler::import() {
	_record.clear();
	std::ifstream openFile("Calls.txt");
	if (openFile.is_open() == false) {
		std::cout << "Calls.txt 파일을 열지 못했습니다. 작업을 중단합니다." << std::endl;
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

// 수신전화 테스트
void CallHandler::simulate(std::string sender_number, ContactHandler &myContacts) const {
	int state;
	std::string name = myContacts.find(sender_number);
	
	std::cout << "수신 중..." << std::endl;
	if (sender_number == name)
		std::cout << sender_number << " [모르는 번호]" << std::endl;
	else
		std::cout << name << " [" << sender_number << ']' << std::endl;

	std::cout << "0 <- 거절 | |  통화 -> 1" << std::endl;
	std::cout << ">> ";
	std::cin >> state;
	if (state == 0)
		std::cout << "전화를 거절했습니다." << std::endl;
	else if (state == 1)
		std::cout << "전화를 받았습니다." << std::endl;
	else
		std::cout << "잘못된 입력입니다." << std::endl;

	std::cout << "\n" << "전화 수신 테스트를 종료합니다." << std::endl;
}

// 통화목록 출력
void CallHandler::display(ContactHandler &myContacts) const {
	if (_record.empty()) {
		std::cout << "통화 기록이 없습니다." << std::endl;
		return;
	}
	for (std::list<CallEntry>::const_iterator it = _record.begin(); it != _record.end(); ++it) {
		switch (it->state()) {
		case 0:
			std::cout << "거절함";
			break;
		case 1:
			std::cout << "수 신";
			break;
		case 2:
			std::cout << "발 신";
			break;
		case 3:
			std::cout << "부재중";
			break;
		case 4:
			std::cout << "취소됨";
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

// 통화기록 추가
void CallHandler::add_dev() {
	int state;
	std::string number;
	std::cout << "통화 기록을 추가합니다." << std::endl;
	std::cout << "상태 - 0: 거절함 / 1 : 수신 / 2 : 발신 / 3 : 부재중 / 4 : 취소됨" << std::endl;
	std::cout << ">> ";
	std::cin >> state;
	if (state < 0 || state > 4) {
		std::cout << "잘못된 입력입니다." << std::endl;
		return;
	}
	std::cout << "전화번호: ";
	std::cin >> number;
	std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
	if (regex_match(number, rgx_num) == false) {
		std::cout << "입력에 실패했습니다." << std::endl;
		std::cout << "입력 예시) 010-1234-5678 / 02-123-4567" << std::endl;
		return;
	}
	CallEntry tmpCall(state, number);
	_record.push_front(tmpCall);
}