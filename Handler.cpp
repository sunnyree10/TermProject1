#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "Handler.h"
#include "file.h"

// 연락처 정보를 저장
Entry::Entry(std::string name, std::string number, std::string email) {
	_name = name;
	_number = number;
	_email = email;
}


// 연락처 정보를 출력하는 함수
void Handler::DisplayEntries() {
	std::cout << "이름\t" << "전화번호\t" << "이메일" << std::endl;
	for (std::map<std::string, Entry>::iterator itEntries = Entries.begin(); itEntries != Entries.end(); ++itEntries) {
		std::cout << itEntries->second.EntryName() << "\t"
				  << itEntries->second.EntryNumber() << "\t"
				  << itEntries->second.EntryEmail() << std::endl;
	}
}

// 파일에서 연락처 정보를 가져오는 함수
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

// 이름으로 연락처를 검색하는 함수
std::map<std::string, Entry>::iterator Handler::FindEntryWithName() {
	std::string name;
	std::cout << "이름으로 검색: ";
	std::cin >> name;
	std::map<std::string, Entry>::iterator findEntry = Entries.find(name);
	if (findEntry != Entries.end()) {
		std::cout << "이름\t" << "전화번호\t" << "이메일" << std::endl;
		std::cout << findEntry->second.EntryName() << "\t"
				  << findEntry->second.EntryNumber() << "\t"
				  << findEntry->second.EntryEmail() << std::endl;
	}
	else {
		std::cout << "검색 결과가 없습니다." << std::endl;
	}

	return findEntry;
}