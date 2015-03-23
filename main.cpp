#include <iostream>
#include <string>

#include "Handler.h"
#include "message.h"
#include "file.h"

using namespace std;

void AddressBook(Handler &myHandler);
void Messenger(SMSHandler &mySMSbox, Handler &myHandler);

int main()
{
	Handler myAddressBook;
	SMSHandler mySMSbox;
	int command;
	while (true) {
		cout << "--------------------" << endl;
		cout << "1. 전화번호부" << endl;
		cout << "2. 메세지" << endl;
		cout << "3. 전화" << endl;
		cout << "4. 종료" << endl;
		cout << "--------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) AddressBook(myAddressBook);
		else if (command == 2) Messenger(mySMSbox, myAddressBook);
		else if (command == 3) continue;
		else if (command == 4) break;
		else {
			cout << "잘못된 입력입니다.\n" << endl;
			continue;
		}
	}
	return 0;
}

void AddressBook(Handler &myHandler) {
	int command;
	while (true) {
		cout << endl;
		cout << "---- 전화번호부 ----" << endl;
		cout << "1. 파일에서 연락처 불러오기" << endl;
		cout << "2. 모든 연락처 출력" << endl;
		cout << "3. 연락처 추가" << endl;
		cout << "4. 연락처 검색" << endl;
		cout << "5. 전화번호부 종료" << endl;
		cout << "--------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) myHandler.GetEntriesFromFile();
		else if (command == 2) myHandler.DisplayEntries();
		else if (command == 3) {
			myHandler.AddEntry();
			WriteOutEntries(myHandler);
		}
		else if (command == 4) myHandler.FindEntry();
		else if (command == 5) {
			cout << endl;
			break;
		}
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}
	}
}

void Messenger(SMSHandler &mySMSbox, Handler &myHandler) {
	int command;
	while (true) {
		cout << endl;
		cout << "------ 메세지 ------" << endl;
		cout << "1. 보낸메세지함" << endl;
		cout << "2. 받은메세지함" << endl;
		cout << "3. 메세지 보내기" << endl;
		cout << "4. 메세지 종료" << endl;
		cout << "--------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) {
			mySMSbox.GetSMSFromFile(true);
			while (true)
				if (!mySMSbox.DisplaySMSList(true, myHandler)) break;
		}
		else if (command == 2) {
			mySMSbox.GetSMSFromFile(false);
			while (true)
				if (!mySMSbox.DisplaySMSList(false, myHandler)) break;
		}
		else if (command == 3) {
			mySMSbox.SendSMS();
			WriteOutSMS(mySMSbox);
		}
		else if (command == 4) {
			cout << endl;
			break;
		}
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}
	}
}