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
		cout << "1. ��ȭ��ȣ��" << endl;
		cout << "2. �޼���" << endl;
		cout << "3. ��ȭ" << endl;
		cout << "4. ����" << endl;
		cout << "--------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) AddressBook(myAddressBook, isContactDataLoaded);
		else if (command == 2) Messenger(myAddressBook);
		else if (command == 3) Calls(myAddressBook);
		else if (command == 4) break;
		else {
			cout << "�߸��� �Է��Դϴ�.\n" << endl;
			continue;
		}
	}
	return 0;
}

void AddressBook(ContactHandler &myContacts, bool &isContactDataLoaded) {
	int command;
	while (true) {
		cout << endl;
		cout << "--------- ��ȭ��ȣ�� ---------" << endl;
		cout << "1. ���Ͽ��� ����ó �ҷ�����" << endl;
		cout << "2. ����ó �߰�" << endl;
		cout << "3. ��� ����ó ���" << endl;
		cout << "4. ����ó �˻�" << endl;
		cout << "5. ����" << endl;
		cout << "------------------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) {
			myContacts.import();
			isContactDataLoaded = true;
		}
		else if (command == 2) {
			if (!isContactDataLoaded) {
				cout << "���: ������ �� ���̶� �ҷ����� �ʾҴٸ� ������ ������ ���� �� �ֽ��ϴ�." << endl;
				cout << "����Ͻðڽ��ϱ� ? (y, n) >> ";
				char op;
				cin >> op;
				if (op == 'n') continue;
				if (op != 'y') {
					cout << "�߸��� �Է��Դϴ�." << endl;
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
			cout << "�߸��� �Է��Դϴ�." << endl;
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
		cout << "----------- �޼��� -----------" << endl;
		cout << "1. �����޼�����" << endl;
		cout << "2. �����޼�����" << endl;
		cout << "3. �޼��� ������" << endl;
		cout << "4. ����" << endl;
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
			cout << "�߸��� �Է��Դϴ�." << endl;
			continue;
		}
	}
}

void Calls(ContactHandler &myContacts) {
	int command;
	CallHandler myCalls;
	while (true) {
		cout << endl;
		cout << "----------- �� ȭ -----------" << endl;
		cout << "1. ��ȭ ���� �׽�Ʈ" << endl;
		cout << "2. ��ȭ ���" << endl;
		cout << "3. ��ȭ ��� ����[dev]" << endl;
		cout << "4. ����" << endl;
		cout << "------------------------------" << endl;
		cout << ">> ";
		cin >> command;
		if (command == 1) {			
			cout << "�߽��� ��ȣ: ";
			string num;
			cin >> num;
			regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
			if (regex_match(num, rgx_num) == false) {
				cout << "�Է¿� �����߽��ϴ�." << endl;
				cout << "�Է� ����) 010-1234-5678 / 02-123-4567" << endl;
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
			cout << "�߸��� �Է��Դϴ�." << endl;
			continue;
		}
	}
}