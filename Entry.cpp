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
	cout << "�̸�: " << name << endl;
	cout << "��ȭ��ȣ: " << number << endl;
	cout << "�̸���: " << email << endl;
}
