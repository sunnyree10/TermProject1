#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "Handler.h"
#include "file.h"

// Entry 생성자: 연락처 정보를 저장
Entry::Entry(std::string name, std::string number, std::string email) {
	_name = name;
	_number = number;
	_email = email;
}


// 연락처를 추가하는 함수
void Handler::AddEntry() {
	std::string *data;
	data = new std::string[3];
	std::cout << "연락처를 추가합니다." << std::endl;
	
	// 수정 필요
	std::cout << "이름: ";
	
	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::getline(std::cin, data[0]);
	
	while (true) {
		std::cout << "전화번호: ";
		std::cin >> data[1];
		std::regex num("\\d{2,3}-\\d{3,4}-\\d{4}");
		if (std::regex_match(data[1], num) != true) {
			std::cout << "입력이 잘못되었습니다. 입력 예시: 010-1234-5678" << std::endl;
			continue;
		}
		else break;
	}
	while (true) {
		std::cout << "이메일: ";
		std::cin >> data[2];
		std::regex em("\\w+@\\w+\\.\\w+\\.?\\w*");
		if (std::regex_match(data[2], em) != true) {
			std::cout << "입력이 잘못되었습니다. 입력 예시: example@example.com 또는 .co.kr" << std::endl;
			continue;
		}
		else break;
	}
	Entry tmpEntry(data[0], data[1], data[2]);
	Entries.insert(std::pair<std::string, Entry>(data[0], tmpEntry));
	++personNum;
}

// 연락처 정보를 출력하는 함수
void Handler::DisplayEntries() {
	std::cout << std::endl;
	std::cout << "총 " << personNum << "개의 연락처" << std::endl;
	std::cout << "이름\t\t" << "전화번호\t" << "이메일" << std::endl;
	for (std::map<std::string, Entry>::iterator itEntries = Entries.begin(); itEntries != Entries.end(); ++itEntries) {
		std::cout << itEntries->second.EntryName() << "\t\t"
				  << itEntries->second.EntryNumber() << "\t"
				  << itEntries->second.EntryEmail() << std::endl;
	}
}

// 파일의 내용을 내부 메모리에 불러오는 함수
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
	std::cout << "동기화 완료!" << std::endl;
}

// 이름 또는 전화번호로 연락처를 검색하는 함수
std::map<std::string, Entry>::iterator Handler::FindEntry() {
	std::string data;
	std::regex num("\\d{2,3}-\\d{3,4}-\\d{4}");
	std::map<std::string, Entry>::iterator findEntry;

	std::cout << std::endl;
	std::cout << "이름 또는 전화번호로 연락처를 검색합니다." << std::endl;
	std::cout << "전화번호는 하이픈(-)을 포함하여 입력해주세요." << std::endl;
	
	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "이름 또는 전화번호: ";
	std::getline(std::cin, data);
	
	std::cout << std::endl;

	// 입력 데이터가 전화번호일 경우
	if (std::regex_match(data, num) == true) {
		for (findEntry = Entries.begin(); findEntry != Entries.end() && data.compare(findEntry->second.EntryNumber()); ++findEntry);
		if (findEntry != Entries.end()) {
			std::cout << "이름\t\t" << "전화번호\t" << "이메일" << std::endl;
			std::cout << findEntry->second.EntryName() << "\t\t"
					  << findEntry->second.EntryNumber() << "\t"
					  << findEntry->second.EntryEmail() << std::endl;
		}
		else{
			std::cout << "검색 결과가 없습니다." << std::endl;
		}
	}
	// 입력 데이터가 전화번호가 아닐 경우 이름으로 간주
	else {
		findEntry = Entries.find(data);
		if (findEntry != Entries.end()) {
			std::cout << "이름\t\t" << "전화번호\t" << "이메일" << std::endl;
			std::cout << findEntry->second.EntryName() << "\t\t"
					  << findEntry->second.EntryNumber() << "\t"
					  << findEntry->second.EntryEmail() << std::endl;
		}
		else {
			std::cout << "검색 결과가 없거나 입력 형식이 올바르지 않습니다." << std::endl;
		}
	}

	return findEntry;
}

// 전화번호에 해당하는 이름을 리턴하는 함수
std::string Handler::GetNameFromNumber(std::string number) {
	std::map<std::string, Entry>::iterator findEntry;
	for (findEntry = Entries.begin(); findEntry != Entries.end() && number.compare(findEntry->second.EntryNumber()); ++findEntry);
	if (findEntry != Entries.end()) return findEntry->first;
	else return number;
}