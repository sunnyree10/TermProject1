#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <list>

#include "Contacts.h"


class SMS {
private:
	std::string _targetNumber;
	std::string _text;

public:
	SMS(std::string targetNumber, std::string text) { _targetNumber = targetNumber; _text = text; }
	~SMS() {}
	std::string number() const { return _targetNumber; }
	std::string text() const { return _text; }
};

class SMSHandler {
protected:
	std::list<SMS> _messages;

public:
	SMSHandler() {}
	~SMSHandler() { _messages.clear(); }
	std::list<SMS> data() const { return _messages; }
	void display(ContactHandler &myContacts) const;
	void displaySMS(int index, ContactHandler &myContacts) const;
};

// 메세지 발신
class OutgoingSMS : public SMSHandler {
public:
	void send();
	void import();
};

// 메세지 수신
class ImcomingSMS : public SMSHandler {
public:
	void import();
};

#endif