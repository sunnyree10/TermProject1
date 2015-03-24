#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

#include "Contacts.h"


// ¿¬¶ôÃ³ Ãß°¡
void ContactHandler::add() {
	std::string name, number, email;

	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "ÀÌ¸§: ";
	std::getline(std::cin, name);
	std::regex rgx_name("([a-zA-Z]+(\\s*[a-zA-Z])+)");
	if (std::regex_match(name, rgx_name) == false) {
		std::cout << "ÀÔ·Â¿¡ ½ÇÆÐÇß½À´Ï´Ù." << std::endl;
		std::cout << "ÀÔ·Â ¿¹½Ã) Suntae / Ko Ji Hun" << std::endl;
		return;
	}
	std::cout << "ÀüÈ­¹øÈ£: ";
	std::cin >> number;
	std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
	if (std::regex_match(number, rgx_num) == false) {
		std::cout << "ÀÔ·Â¿¡ ½ÇÆÐÇß½À´Ï´Ù." << std::endl;
		std::cout << "ÀÔ·Â ¿¹½Ã) 010-1234-5678 / 02-123-4567" << std::endl;
		return;
	}
	std::cout << "ÀÌ¸ÞÀÏ ÁÖ¼Ò: ";
	std::cin >> email;
	std::regex rgx_email("\\w+@\\w+\\.\\w+\\.?\\w*");
	if (std::regex_match(email, rgx_email) == false) {
		std::cout << "ÀÔ·Â¿¡ ½ÇÆÐÇß½À´Ï´Ù." << std::endl;
		std::cout << "ÀÔ·Â ¿¹½Ã) admin@example.com / admin@example.co.kr" << std::endl;
		return;
	}

	Contact tmpContact(name, number, email);
	_contacts.insert(std::pair<std::string, Contact>(name, tmpContact));
}

// ÆÄÀÏ ³»¿ëÀ» ³»ºÎ ¸Þ¸ð¸®¿¡ ·Îµå
void ContactHandler::import() {
	_contacts.clear();
	std::ifstream openFile("Contacts.txt");
	if (openFile.is_open() == false) {
		std::cout << "contacts.txt ÆÄÀÏÀ» ¿­Áö ¸øÇß½À´Ï´Ù. ÀÛ¾÷À» Áß´ÜÇÕ´Ï´Ù." << std::endl;
	}
	else {
		while (!openFile.eof()){
			std::string data[3], oneLine;
			std::getline(openFile, oneLine);
			std::smatch m;
			std::regex rgx_name("([a-zA-Z]+(\\s*[a-zA-Z])+)|[°¡-ÆR]+");
			std::regex rgx_num("\\d{2,3}-\\d{3,4}-\\d{4}");
			std::regex rgx_email("\\w+@\\w+\\.\\w+\\.*\\w*");
			std::regex rgx[3] = { rgx_name, rgx_num, rgx_email };
			for (int i = 0; i < 3; ++i) {
				std::regex_search(oneLine, m, rgx[i]);
				data[i] = m.str();
			}
			Contact tmpContact(data[0], data[1], data[2]);
			_contacts.insert(std::pair<std::string, Contact>(data[0], tmpContact));
		}
		openFile.close();
		std::cout << "¿¬¶ôÃ³¸¦ ¼º°øÀûÀ¸·Î ºÒ·¯¿Ô½À´Ï´Ù." << std::endl;
	}
}

// ¿¬¶ôÃ³ ¸ñ·Ï Ãâ·Â
void ContactHandler::display() const {
	if (_contacts.empty()) {
		std::cout << "¿¬¶ôÃ³°¡ ¾ø½À´Ï´Ù." << std::endl;
		return;
	}
	std::cout << "ÃÑ " << _contacts.size() << "°³ÀÇ ¿¬¶ôÃ³" << std::endl;
	std::cout << "ÀÌ¸§" << "\t\t" << "ÀüÈ­¹øÈ£" << "\t" << "ÀÌ¸ÞÀÏ" << std::endl;
	for (std::map<std::string, Contact>::const_iterator it = _contacts.begin(); it != _contacts.end(); ++it) {
		std::cout << it->second.name() << "\t\t"
				  << it->second.number() << "\t"
				  << it->second.email() << std::endl;
	}
}

// ÀÌ¸§, ÀüÈ­¹øÈ£·Î ¿¬¶ôÃ³ °Ë»ö
std::map<std::string, Contact>::const_iterator ContactHandler::find() const {
	std::string data;
	std::regex num("\\d{2,3}-\\d{3,4}-\\d{4}");
	std::map<std::string, Contact>::const_iterator findContact;

	std::cin.clear();
	while (std::cin.get() != '\n') continue;

	std::cout << "ÀÌ¸§ ¶Ç´Â ÀüÈ­¹øÈ£·Î ¿¬¶ôÃ³¸¦ °Ë»öÇÕ´Ï´Ù." << std::endl;
	std::cout << "ÀüÈ­¹øÈ£´Â ÇÏÀÌÇÂ(-)À» Æ÷ÇÔÇÏ¿© ÀÔ·ÂÇØÁÖ¼¼¿ä." << std::endl;
	std::cout << "ÀÌ¸§ ¶Ç´Â ÀüÈ­¹øÈ£: ";
	std::getline(std::cin, data);

	std::cout << std::endl;

	// ÀÔ·Â µ¥ÀÌÅÍ°¡ ÀüÈ­¹øÈ£ÀÏ °æ¿ì
	if (std::regex_match(data, num) == true) {
		for (findContact = _contacts.begin(); findContact != _contacts.end() && data.compare(findContact->second.number()); ++findContact);
		if (findContact != _contacts.end()) {
			std::cout << "ÀÌ¸§" << "\t\t" << "ÀüÈ­¹øÈ£" << "\t" << "ÀÌ¸ÞÀÏ" << std::endl;
			std::cout << findContact->second.name() << "\t\t"
					  << findContact->second.number() << "\t"
					  << findContact->second.email() << std::endl;
		}
		else{
			std::cout << "°Ë»ö °á°ú°¡ ¾ø½À´Ï´Ù." << std::endl;
		}
	}
	// ÀÔ·Â µ¥ÀÌÅÍ°¡ ÀüÈ­¹øÈ£°¡ ¾Æ´Ò °æ¿ì ÀÌ¸§À¸·Î °£ÁÖ
	else {
		findContact = _contacts.find(data);
		if (findContact != _contacts.end()) {
			std::cout << "ÀÌ¸§" << "\t\t" << "ÀüÈ­¹øÈ£" << "\t" << "ÀÌ¸ÞÀÏ" << std::endl;
			std::cout << findContact->second.name() << "\t\t"
					  << findContact->second.number() << "\t"
					  << findContact->second.email() << std::endl;
		}
		else {
			std::cout << "°Ë»ö °á°ú°¡ ¾ø°Å³ª ÀÔ·Â Çü½ÄÀÌ ¿Ã¹Ù¸£Áö ¾Ê½À´Ï´Ù." << std::endl;
		}
	}

	return findContact;
}

// ÀüÈ­¹øÈ£¸¦ °Ë»öÇÏ¿© ÇØ´çÇÏ´Â ÀÌ¸§ ¸®ÅÏ
std::string ContactHandler::find(std::string number) const {
	std::map<std::string, Contact>::const_iterator findContact;
	for (findContact = _contacts.begin(); findContact != _contacts.end() && number.compare(findContact->second.number()); ++findContact);
	if (findContact != _contacts.end()) return findContact->first;
	else return number;
}