#include <iostream>
#include <string>
#include "Entry.h"
#include "Handler.h"

using namespace std;


int main()
{
	Handler h1;
	h1.AddPerson();
	h1.Display();
	
	return 0;
}