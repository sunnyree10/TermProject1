#ifndef __CALLER_H__
#define __CALLER_H__

#include <string>
#include <map>
#include <list>

#include "Contacts.h"

class CallEntry {
private:
	int _state;
	std::string _targetNumber;

public:
	CallEntry(int state, std::string targetNumber) { _state = state; _targetNumber = targetNumber; }
	~CallEntry() {}
	int state() const { return _state; }
	std::string number() const { return _targetNumber; }
};

class CallHandler {
private:
	std::list<CallEntry> _record;
public:
	CallHandler() {}
	~CallHandler() { _record.clear(); }
	std::list<CallEntry> data() const { return _record; }
	void add_dev();
	void import();
	void display(ContactHandler &myContacts) const;
	void simulate(std::string sender_number, ContactHandler &myContacts) const;
};

#endif