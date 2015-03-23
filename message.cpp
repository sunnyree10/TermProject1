#include <iostream>
#include <algorithm>
#include <string>
#include <regex>

#include "Handler.h"
#include "message.h"
#include "file.h"

void SMSHandler::SendSMS() {
	std::string targetNum, text;
	while (true) {
		std::cout << "�޴� ���(��ȭ��ȣ): ";
		std::cin >> targetNum;
		std::regex num("\\d{2,3}-\\d{3,4}-\\d{4}");
		if (std::regex_match(targetNum, num) != true) {
			std::cout << "�Է��� �߸��Ǿ����ϴ�. �Է� ����: 010-1234-5678" << std::endl;
			continue;
		}
		else break;
	}

	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "�޼��� ����: ";
	std::getline(std::cin, text);
	SMS tmpSMS(targetNum, text);
	_sentSMS.push_front(tmpSMS);
}

bool SMSHandler::DisplaySMSList(bool isSentSMS, Handler &myHandler) {
	int searchIndex;
	int i = 1;
	
	std::cout << std::endl;

	if (isSentSMS == true) {
		std::cout << "�����޼���" << std::endl;
		std::cout << "��ȣ\t" << "�̸�/��ȭ��ȣ\t" << "�޼��� ����" << std::endl;
		for (std::list<SMS>::iterator itSMS = _sentSMS.begin(); itSMS != _sentSMS.end(); ++itSMS, ++i) {
			std::cout << i << "\t" << myHandler.GetNameFromNumber(itSMS->TargetNumber()) << "\t";
			if (itSMS->SMSText().length() <= 15) std::cout << itSMS->SMSText() << std::endl;
			else std::cout << itSMS->SMSText().substr(0, 15) << "��" << std::endl;
		}
	}
	else {
		std::cout << "�����޼���" << std::endl;
		std::cout << "��ȣ\t" << "�̸�/��ȭ��ȣ\t" << "�޼��� ����" << std::endl;
		for (std::list<SMS>::iterator itSMS = _receivedSMS.begin(); itSMS != _receivedSMS.end(); ++itSMS, ++i) {
			std::cout << i << "\t" << myHandler.GetNameFromNumber(itSMS->TargetNumber()) << "\t";
			if (itSMS->SMSText().length() <= 15) std::cout << itSMS->SMSText() << std::endl;
			else std::cout << itSMS->SMSText().substr(0, 15) << "��" << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "��� �޼����� ��ȣ�� �Է��ϼ���." << std::endl;
	std::cout << "���� �޼����� ��ȣ�� 0�� �Է��ϸ� ���� �޴��� �����ϴ�." << std::endl;
	std::cout << ">> ";
	std::cin >> searchIndex;
	if (searchIndex >= i || searchIndex == 0) return false;
	else {
		ShowSMS(searchIndex, isSentSMS, myHandler);
		return true;
	}
}

void SMSHandler::ShowSMS(int index, bool isSentSMS, Handler &myHandler) {
	int i = 1;
	std::list<SMS>::iterator itSMS;
	if (isSentSMS == true) {
		for (itSMS = _sentSMS.begin(); i != index; ++itSMS, ++i);
		std::cout << myHandler.GetNameFromNumber(itSMS->TargetNumber()) << std::endl;
		std::cout << itSMS->SMSText() << std::endl;
	}
	else {
		for (itSMS = _receivedSMS.begin(); i != index; ++itSMS, ++i);
		std::cout << myHandler.GetNameFromNumber(itSMS->TargetNumber()) << std::endl;
		std::cout << itSMS->SMSText() << std::endl;
	}
}

void SMSHandler::GetSMSFromFile(bool inSentSMS) {
	if (inSentSMS == true) {
		_sentSMS.clear();
		std::ifstream openFile("sentsms.txt");
		while (!openFile.eof()) {
			std::string *data = NULL;
			data = ReadSMSFromFile(openFile);
			SMS tmpSMS(data[0], data[1]);
			_sentSMS.push_front(tmpSMS);
			delete[] data;
		}
		openFile.close();
	}
	else {
		_receivedSMS.clear();
		std::ifstream openFile("receivedSMS.txt");
		while (!openFile.eof()) {
			std::string *data = NULL;
			data = ReadSMSFromFile(openFile);
			SMS tmpSMS(data[0], data[1]);
			_receivedSMS.push_front(tmpSMS);
			delete[] data;
		}
		openFile.close();
	}
}