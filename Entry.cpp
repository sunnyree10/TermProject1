#include <iostream>
#include <string>
#include "Entry.h"
using namespace std;


Entry::Entry(string name, string number,  string email)
{
	this->name = name;
	this->number = number;
	this->email = email;
}
void Entry::ShowEntryInfo()
{
	cout << "이름: " << name << endl;
	cout << "전화번호: " << number << endl;
	cout << "이메일: " << email << endl;
}
