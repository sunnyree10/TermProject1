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
	cout << "�̸�: " << _name << endl;
	cout << "��ȭ��ȣ: " << _number << endl;
	cout << "�̸���: " << _email << endl;
}

