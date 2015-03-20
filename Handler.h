#ifndef __HANDLER_H__
#define __HANDLER_H__
#include <fstream>
#include <vector>
class Handler
{
private:
	int personNum;
	std::ifstream file;
	std::vector < Entry > p1;
public:
	Handler(int num=0);
	void Display();
	void AddPerson();
	//void RemovePerson();
	void Sort();
};
std::string* read(std::ifstream &file);

#endif