#ifndef __HANDLER_H__
#define __HANDLER_H__

#include <fstream>
#include <vector>
#include <map>
#include <string>

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
	std::ifstream file;
	std::map<std::string, Entry> Entries;

public:
	Handler(int num=0);
	~Handler() {};
	void Display();
	void AddPerson();
	//void RemovePerson();

	friend void WriteOutEntries(std::string fileName, Handler *myHandler);
};

std::string* read(std::ifstream &file);

#endif