#ifndef __HANDLER_H__
#define __HANDLER_H__
#include <fstream>
#include <vector>
#include <map>
#include <string>
class Handler
{
private:
	int personNum;
	std::ifstream file;
	std::vector<Entry> v1;
	std::map<std::string, Entry> Entries;
public:
	Handler(int num=0);
	~Handler();
	void Display();
	void AddPerson();
	//void RemovePerson();
	void Sort();
	std::map<std::string, Entry> EntryData() { return Entries; }
};
std::string* read(std::ifstream &file);
void WriteOutEntries(std::string fileName, Handler *myHandler);

#endif