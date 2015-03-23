#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <list>

#include "Handler.h"

// SMS ����
class SMS {
private:
	std::string _myNumber;
	std::string _targetNumber;
	std::string _text;

public:
	SMS() { _myNumber = "010-5287-3807"; };
	SMS(std::string targetNumber, std::string text) { _targetNumber = targetNumber; _text = text; }
	~SMS() {};
	const std::string MyNumber() { return _myNumber; }
	const std::string TargetNumber() { return _targetNumber; }
	const std::string SMSText() { return _text; }
};

// �޼��� ������
class SMSHandler {
private:
	std::list<SMS> _receivedSMS;
	std::list<SMS> _sentSMS;

public:
	SMSHandler() {};
	~SMSHandler() {};
	void SendSMS();
	bool DisplaySMSList(bool isSentSMS, Handler &myHandler);
	void ShowSMS(int index, bool isSentSMS, Handler &myHandler);
	void GetSMSFromFile(bool isSentSMS);
	std::list<SMS> ReceivedSMS() { return _receivedSMS; }
	std::list<SMS> SentSMS() { return _sentSMS; }
};

#endif