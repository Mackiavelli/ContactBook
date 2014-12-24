#include <iostream>

#include "contacts.h"
#include "contactbook.h"

//using namespace std;

int main()
{
	ContactBook *myContacts = new ContactBook();
	while (myContacts->displayMenu()){}
}
