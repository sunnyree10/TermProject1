# TermProject1
**class addressBook**  
*member 변수*  
  entry 갯수
  
*member 함수*  
  Add  
  Remove  
  Sort
  
  
*생성자*  
  entry 갯수 초기화



###모든 입출력은 파일로 받기



#include <string>
#include <vector>

class Entry {
	std::string _name;
	std::string _number;
	std::string _email;

	Entry(std::string name, std::string number, std::string email) {
		name = _name;
		number = _number;
		email = _email;
	};
};

class AddressBook {
	std::vector<Entry> Entries;
	unsigned int EntriesNum;

	void Add();
	void Remove();
	void Sort();


};

class SMS {

};