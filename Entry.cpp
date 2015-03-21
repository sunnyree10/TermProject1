#include <iostream>
#include <fstream>
#include <string>
#include "Entry.h"

using namespace std;

Entry::Entry(string name, string number, string email)
{
	_name = name;
	_number = number;
	_email = email;
}

Entry::~Entry()
{
}

void Entry::ShowEntryInfo()
{
	cout << "이름: " << _name << endl;
	cout << "전화번호: " << _number << endl;
	cout << "이메일: " << _email << endl;
}

