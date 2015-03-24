#include <iostream>
#include <fstream>
#include <list>
#include <map>

#include "Contacts.h"
#include "Message.h"
#include "Call.h"
#include "WriteFile.h"


// 연락처를 파일로 내보내는 함수
void WriteOutContacts(ContactHandler &myContacts) {
	std::ofstream outFile("Contacts.txt");
	std::map<std::string, Contact> tmpContact = myContacts.data();
	for (std::map<std::string, Contact>::const_iterator it = tmpContact.begin(); it != tmpContact.end(); ++it) {
		if (it != tmpContact.begin()) outFile << std::endl;
		outFile << it->second.name() << ' ' << it->second.number() << ' ' << it->second.email();
	}
}

// SMS를 파일로 내보내는 함수
void WriteOutSMS(SMSHandler &myMessages) {
	std::ofstream outFile("OutGoingSMS.txt");
	std::list<SMS> tmpSMS = myMessages.data();
	for (std::list<SMS>::const_iterator it = tmpSMS.begin(); it != tmpSMS.end(); ++it) {
		if (it != tmpSMS.begin()) outFile << std::endl;
		outFile << it->number() << ' ' << it->text();
	}
}

// 통화 기록을 파일로 내보내는 함수
void WriteOutCallLogs(CallHandler &myCalls) {
	std::ofstream outFile("Calls.txt");
	std::list<CallEntry> tmpCall = myCalls.data();
	for (std::list<CallEntry>::const_iterator it = tmpCall.begin(); it != tmpCall.end(); ++it) {
		if (it != tmpCall.begin()) outFile << std::endl;
		outFile << it->state() << ' ' << it->number();
	}
}