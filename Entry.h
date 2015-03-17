#include <string>

class Entry{
private:
	std::string name;
	std::string number;
	std::string email;

public:
	Entry(std::string name, std::string number, std::string email);
	void ShowEntryInfo();
};