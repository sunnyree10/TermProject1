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
		cout << "1. ��ȭ��ȣ��" << endl;
		cout << "2. �޼���" << endl;
		cout << "3. ��ȭ" << endl;
		cout << "4. ����" << endl;
		cout << "--------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) AddressBook(myAddressBook);
		else if (command == 2) Messenger(mySMSbox, myAddressBook);
		else if (command == 3) continue;
		else if (command == 4) break;
		else {
			cout << "�߸��� �Է��Դϴ�.\n" << endl;
			continue;
		}
	}
	return 0;
}

void AddressBook(Handler &myHandler) {
	int command;
	while (true) {
		cout << endl;
		cout << "---- ��ȭ��ȣ�� ----" << endl;
		cout << "1. ���Ͽ��� ����ó �ҷ�����" << endl;
		cout << "2. ��� ����ó ���" << endl;
		cout << "3. ����ó �߰�" << endl;
		cout << "4. ����ó �˻�" << endl;
		cout << "5. ��ȭ��ȣ�� ����" << endl;
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
			cout << "�߸��� �Է��Դϴ�." << endl;
			continue;
		}
	}
}

void Messenger(SMSHandler &mySMSbox, Handler &myHandler) {
	int command;
	while (true) {
		cout << endl;
		cout << "------ �޼��� ------" << endl;
		cout << "1. �����޼�����" << endl;
		cout << "2. �����޼�����" << endl;
		cout << "3. �޼��� ������" << endl;
		cout << "4. �޼��� ����" << endl;
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
			cout << "�߸��� �Է��Դϴ�." << endl;
			continue;
		}
	}
}