#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <string>

class Entry {
private:
	std::string _name;
	std::string _number;
	std::string _email;

public:
	Entry(std::string name, std::string number, std::string email);
	~Entry();
	void ShowEntryInfo();
	const std::string EntryName() { return _name; }
	const std::string EntryNumber() { return _number; }
	const std::string EntryEmail() { return _email; }
};

#endif