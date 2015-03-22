#ifndef __HANDLER_H__
#define __HANDLER_H__

#include <fstream>
#include <string>
#include <map>

// ����ó ����
class Entry {
private:
	std::string _name;
	std::string _number;
	std::string _email;

public:
	Entry(std::string name, std::string number, std::string email);
	~Entry() {};
	const std::string EntryName() { return _name; }
	const std::string EntryNumber() { return _number; }
	const std::string EntryEmail() { return _email; }
};

// ����ó ������
class Handler {
private:
	int personNum;
	std::map<std::string, Entry> Entries;

public:
	Handler() { personNum = 0; };
	~Handler() {};
	void DisplayEntries();
	void GetEntriesFromFile();
	std::map<std::string, Entry> EntryData() { return Entries; }
	std::map<std::string, Entry>::iterator FindEntryWithName();
	std::map<std::string, Entry>::iterator FindEntryWithNumber();
};

#endif