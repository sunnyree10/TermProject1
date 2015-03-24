#ifndef __CONTACTHANDLER_H__
#define __CONTACTHANDLER_H__

#include <string>
#include <map>

class Contact {
private:
	std::string _name;
	std::string _number;
	std::string _email;

public:
	Contact(std::string name, std::string number, std::string email) { _name = name; _number = number; _email = email; }
	~Contact() {};
	std::string name() const { return _name; }
	std::string number() const { return _number; }
	std::string email() const { return _email; }
};

class ContactHandler {
private:
	std::map<std::string, Contact> _contacts;

public:
	ContactHandler() {}
	~ContactHandler() { _contacts.clear(); }
	std::map<std::string, Contact> data() const { return _contacts; }
	void add();
	void import();
	void display() const;
	std::map<std::string, Contact>::const_iterator find() const;
	std::string find(std::string number) const;
};

#endif