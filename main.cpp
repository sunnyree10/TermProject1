#include <iostream>
#include <string>
#include <regex>

#include "Contacts.h"
#include "Message.h"
#include "Call.h"
#include "WriteFile.h"

using namespace std;

void AddressBook(ContactHandler &myContacts, bool &isContactDataLoaded);
void Messenger(ContactHandler &myContacts);
void Calls(ContactHandler &myContacts);

int main()
{
	bool isContactDataLoaded = false;
	ContactHandler myAddressBook;
	int command;
	while (true) {
		cout << endl;
		cout << "--------------------" << endl;
		cout << "1. 전화번호부" << endl;
		cout << "2. 메세지" << endl;
		cout << "3. 전화" << endl;
		cout << "4. 종료" << endl;
		cout << "--------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) AddressBook(myAddressBook, isContactDataLoaded);
		else if (command == 2) Messenger(myAddressBook);
		else if (command == 3) Calls(myAddressBook);
		else if (command == 4) break;
		else {
			cout << "잘못된 입력입니다.\n" << endl;
			continue;
		}
	}
	return 0;
}

void AddressBook(ContactHandler &myContacts, bool &isContactDataLoaded) {
	int command;
	while (true) {
		cout << endl;
		cout << "--------- 전화번호부 ---------" << endl;
		cout << "1. 파일에서 연락처 불러오기" << endl;
		cout << "2. 연락처 추가" << endl;
		cout << "3. 모든 연락처 출력" << endl;
		cout << "4. 연락처 검색" << endl;
		cout << "5. 종료" << endl;
		cout << "------------------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) {
			myContacts.import();
			isContactDataLoaded = true;
		}
		else if (command == 2) {
			if (!isContactDataLoaded) {
				cout << "경고: 파일을 한 번이라도 불러오지 않았다면 파일의 내용을 잃을 수 있습니다." << endl;
				cout << "계속하시겠습니까 ? (y, n) >> ";
				char op;
				cin >> op;
				if (op == 'n') continue;
				if (op != 'y') {
					cout << "잘못된 입력입니다." << endl;
					continue;
				}
			}
			myContacts.add();
			WriteOutContacts(myContacts);
		}
		else if (command == 3) myContacts.display();
		else if (command == 4) myContacts.find();
		else if (command == 5) break;
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}
	}
}

void Messenger(ContactHandler &myContacts) {
	int command;
	OutgoingSMS myOutgoingSMS;
	ImcomingSMS myIncomingSMS;
	while (true) {
		cout << endl;
		cout << "----------- 메세지 -----------" << endl;
		cout << "1. 보낸메세지함" << endl;
		cout << "2. 받은메세지함" << endl;
		cout << "3. 메세지 보내기" << endl;
		cout << "4. 종료" << endl;
		cout << "------------------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) {
			myOutgoingSMS.import();
			myOutgoingSMS.display(myContacts);
		}
		else if (command == 2) {
			myIncomingSMS.import();
			myIncomingSMS.display(myContacts);
		}
		else if (command == 3) {
			myOutgoingSMS.send();
			WriteOutSMS(myOutgoingSMS);
		}
		else if (command == 4) break;
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}
	}
}

void Calls(ContactHandler &myContacts) {
	int command;
	CallHandler myCalls;
	while (true) {
		cout << endl;
		cout << "----------- 전 화 -----------" << endl;
		cout << "1. 전화 수신 테스트" << endl;
		cout << "2. 통화 기록" << endl;
		cout << "3. 통화 기록 생성[dev]" << endl;
		cout << "4. 종료" << endl;
		cout << "------------------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) {			
			cout << "발신자 번호: ";
			string num;
			cin >> num;
			regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
			if (regex_match(num, rgx_num) == false) {
				cout << "입력에 실패했습니다." << endl;
				cout << "입력 예시) 010-1234-5678 / 02-123-4567" << endl;
				continue;
			}
			myCalls.simulate(num, myContacts);
		}
		else if (command == 2) {
			myCalls.import();
			myCalls.display(myContacts);
		}
		else if (command == 3) {
			myCalls.add_dev();
			WriteOutCallLogs(myCalls);
		}
		else if (command == 4) break;
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}
	}
}