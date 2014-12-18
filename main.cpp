#include <iostream>

#include "contacts.h"

//using namespace std;

bool menu(ContactBook *myContacts)
{
	cout << "1. Add new contact" << endl
		<< "2. Remove contact" << endl
		<< "3. Find a contact" << endl
		<< "4. Exit" << endl
		<< "Enter the number of your choice: ";

	int choice = 0;

	while (choice > 3 || choice < 1)
	{
		cin >> choice;
		cout << endl << endl;
		switch (choice)
		{
		case 1: myContacts->addContact(); break;
		case 2: myContacts->removeContact(); break;
		case 3: myContacts->findMenu(); break;
		case 4: return false; break;
		default: break;
		}
	}
	return true;
}

int main()
{
	ContactBook *myContacts = new ContactBook();
	while (menu(myContacts)){}

}
