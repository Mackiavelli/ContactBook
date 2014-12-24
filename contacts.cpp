#ifndef CONTACTS_CPP
#define CONTACTS_CPP

#include <fstream>

#include "contacts.h"

//constructors and destructor
Contact::Contact(string newName, string newNumber, string newID)
{
	this->changeName(newName);
	this->changeNumber(newNumber);
	this->changeID(newID);
}

Contact::Contact()
{
}

Contact::~Contact()
{

}


//setters and getters
string Contact::getName() const
{
	return name;
}

string Contact::getNumber() const
{
	return phoneNumber;
}

string Contact::getID() const
{
	return ID;
}

bool Contact::changeName(string newName)
{
	if (newName.size() > 100)
	{
		cout << "Name is greater than 100 characters. Saving only the first 100.\n";

		newName.resize(100); //resizes to contain only first 100 chars.
		strcpy(name, newName.c_str());
		return true;
	}
	else if (newName != "") //only assign name if it isn't empty
	{
		strcpy(name, newName.c_str());
		return true;
	}
	else //if the name is empty
	{
		cout << "You can't change the name to an empty string!\n";

		return false;
	}
}

bool Contact::changeNumber(string newNumber)
{
	if (newNumber.size() > 10)
	{
		cout << "The number of digits in the number is greater than 10."
			<< " You must enter a number shorter than 10 digits\n";
		return false;
	}
	else if (newNumber != "")
	{
		if (!validateNumber(newNumber))
		{
			return false;
		}
		strcpy(phoneNumber, newNumber.c_str());
		return true;
	}
	else
	{
		cout << "You can't change the number to an empty string!\n";
		return false;
	}
}

bool Contact::changeID(string newID)
{
	if (newID.size() > 10)
	{
		cout << "ID too big. Saving only first ten characters\n";
		newID.resize(10);
		strcpy(ID, newID.c_str());
		return true;
	}
	else if (newID != "")
	{
		if (!validateNumber(newID))
		{
			return false;
		}
		strcpy(ID, newID.c_str());
		return true;
	}
	else
	{
		return false;
	}
}

void Contact::enterInfo()
{
	string newName;
	string newNumber;
	string newID;

	cout << "Please enter a contact name shorter than 100 characters: ";
	cin.ignore();
	getline(cin, newName);
	if (!changeName(newName))
	{
		cout << "Error. You will have to create the contact again!\n\n";
		return;
	}

	cout << "Please enter a phone number shorter than 10 digits: ";
	cin >> newNumber;
	if (!changeNumber(newNumber))
	{
		cout << "Error. You will have to create the contact again!\n\n";
		return;
	}

	cout << "Please enter an ID shorter than 10 digits: ";
	cin >> newID;
	changeID(newID);

	cout << "Contact successfully added!" << endl << endl;
}

//save and load
void Contact::saveContact()
{
	ofstream out("contactbook.dat", ios::app | ios::binary);

	out.write((const char*)&(*this), sizeof(Contact));

	out.close();
}

//utility
bool Contact::validateNumber(string number)
{
	for (unsigned int a = 0; a < number.size(); a++)
	{
		if (number[a] < '0' || number[a] > '9')
		{
			cout << "You must only use digits for the number and ID, add the contact again\n";
			return false;
		}
	}
	return true;
}


#endif // CONTACTS_CPP

