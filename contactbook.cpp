#ifndef CONTACTBOOK_CPP
#define CONTACTBOOK_CPP

#include <string>
#include <fstream>

#include "contactbook.h"
#include "contacts.h"
#include "dictionary.h"

#define filename "contactbook.dat"

//constructors
ContactBook::ContactBook()
{
	loadContactBook();
}

ContactBook::ContactBook(Dictionary<string, Contact*> tempName,
	Dictionary<string, Contact*> tempNumber, Dictionary<string, Contact*> tempID)
{
	if (tempName.size() != tempNumber.size() || tempName.size() != tempID.size()
		|| tempNumber.size() != tempID.size())
	{
		return;
	}

	this->name = tempName;
	this->phoneNumber = tempNumber;
	this->ID = tempID;
	for (unsigned int a = 0; a < tempName.size(); a++)
	{
		bookContacts.push_back(*(tempName.getValue(a)));
		numberOfContacts++;
	}
}

ContactBook::ContactBook(ContactBook& temp)
{
	this->name = temp.name;
	this->phoneNumber = temp.phoneNumber;
	this->ID = temp.ID;
	for (unsigned int a = 0; a < temp.size(); a++)
	{
		bookContacts.push_back(*(temp.name.getValue(a)));
		numberOfContacts++;
	}
}

ContactBook::~ContactBook()
{
	bookContacts.clear(); // dictionary objects clear from their own destructors
}


//add\remove contacts
void ContactBook::addContact()
{
	Contact* temp = new Contact();
	temp->enterInfo();

	name.addElement(temp->getName(), temp);
	phoneNumber.addElement(temp->getNumber(), temp);
	ID.addElement(temp->getID(), temp);

	bookContacts.push_back(*temp);

	++numberOfContacts;
}

void ContactBook::addContact(Contact temp)
{
	Contact* newContact = new Contact(temp);

	name.addElement(temp.getName(), newContact);
	ID.addElement(temp.getID(), newContact);
	phoneNumber.addElement(temp.getNumber(), newContact);

	bookContacts.push_back(*newContact);

	++numberOfContacts;
}

void ContactBook::removeContact()
{
	int choice;
	string findString;
	string findID;

	cout << "How do you wish to find the contact which you want to delete?" << endl
		<< "1. Name or Phone" << endl
		<< "2. ID " << endl
		<< "Enter your choice: ";

	cin >> choice;

	if (choice == 1)
	{
		cout << "Enter the name or the number: ";
		cin.ignore();
		getline(cin, findString);

		if (findContact(findString))
		{
			for (unsigned int a = 0; a < name.size(); a++)
			{
				if (name.getKey(a) == findString)
				{
					name.removeElement(a);
					phoneNumber.removeElement(a);
					ID.removeElement(a);

					bookContacts.erase(bookContacts.begin() + a);

					--numberOfContacts;
					break;
				}
			}
			cout << "Contact successfully removed!\n";
		}
	}

	else if (choice == 2)
	{
		cout << "Enter the ID: ";
		cin >> findID;
		cout << endl;

		if (findContact(findID))
		{
			for (unsigned int a = 0; a < size(); a++)
			{
				if (ID.getKey(a) == findID)
				{
					name.removeElement(a);
					phoneNumber.removeElement(a);
					ID.removeElement(a);

					bookContacts.erase(bookContacts.begin() + a);

					--numberOfContacts;

					break;
				}
			}
			cout << "Contact successfully removed!\n";
		}
	}


}


//find contacts
const Contact* ContactBook::findContact(string searchParameter) 
{
	for (unsigned int a = 0; a < this->size(); a++)
	{
		if (!(name.getKey(a).compare(searchParameter)))
		{
			cout << name.getValue(a) << endl;
			return name.getValue(a);
		}

		else if (!(phoneNumber.getKey(a).compare(searchParameter)))
		{
			cout << phoneNumber.getValue(a) << endl;
			return phoneNumber.getValue(a);
		}

		else if (!(ID.getKey(a).compare(searchParameter)))
		{
			cout << phoneNumber.getValue(a) << endl;
			return ID.getValue(a);
		}
	}

	return 0;
}


//sorting
void ContactBook::swapElements(unsigned int source, unsigned int destination)
{
	Contact temp = bookContacts[source];
	bookContacts[source] = bookContacts[destination];
	bookContacts[destination] = temp;

	name.swapElements(source, destination);
	ID.swapElements(source, destination);
	phoneNumber.swapElements(source, destination);
	
}

void ContactBook::sort(Dictionary<string, Contact*> temp)
{//bubblesort
	int i;
	int k;
	int right = size() - 1;
	while (right > 0)
	{
		k = 0;
		for (i = 0; i < right; i++)
		{
			if (temp.getKey(i + 1) < temp.getKey(i))
			{
				swapElements(i, i + 1);
				k = i;
			}
		}
		right = k;
	}
}

void ContactBook::sortByName()
{
	sort(name);
}

void ContactBook::sortByNumber()
{
	sort(phoneNumber);
}

void ContactBook::sortByID()
{
	sort(ID);
}

void ContactBook::sortContactBook(unsigned int criterion)
{
	switch (criterion)
	{
	case 1:
		sortByName();
		break;
	case 2:
		sortByNumber();
		break;
	case 3:
		sortByID();
		break;
	default:
		requestNewCriterion();
		break;
	}
}

void ContactBook::requestNewCriterion()
{
	unsigned short newCriterion = 0;
	while ((newCriterion < 1) || (newCriterion > 3))
	{
		cout << "Please enter: " << endl
			<< "1 - For sorting the contacts book by name " << endl
			<< "2 - For sorting the contacts book by phone number " << endl
			<< "3 - For sorting the contacts book by ID " << endl
			<< "Enter your choice: ";

		cin >> newCriterion;
	}

	sortContactBook(newCriterion);
}


//utility
bool ContactBook::displayMenu()
{
	int choice = 0;

	while (choice > 7 || choice < 1)
	{
		cout << "1. Add new contact" << endl
			<< "2. Remove contact" << endl
			<< "3. Find a contact" << endl
			<< "4. Sort the contacts" << endl
			<< "5. Display all available contacts" << endl
			<< "6. Delete all contacts" << endl
			<< "7. Exit" << endl
			<< "\nEnter the number of your choice: ";
		cin >> choice;
		cout << endl << endl;

		switch (choice)
		{
		case 1:
			this->addContact();
			break;

		case 2:
			this->removeContact();
			break;

		case 3:
			this->displayFindMenu();
			break;

		case 4:
			this->requestNewCriterion();
			cout << endl << "Contacts successfully sorted!\n\n";
			break;

		case 5:
			cout << "\tCONTACTS:\n" << (*this);
			break;

		case 6:
			deleteContactBook();
			break;

		case 7:
			this->saveContactBook();
			return false;
			break;

		default:
			this->saveContactBook();
			return false;
			break;
		}
	}
	return true;

}

void ContactBook::printBook()
{
	requestNewCriterion();

	for (unsigned int a = 0; a < name.size(); a++)
	{
		cout << "Name: " << name.getKey(a) << endl
			<< "Number: " << phoneNumber.getKey(a) << endl
			<< "ID: " << ID.getKey(a) << endl;
	}
}

void ContactBook::displayFindMenu()
{
	cout << "1. Name" << endl
		<< "2. Phone Number" << endl
		<< "3. ID" << endl
		<< "Enter the digit corresponsing to your search criteria: ";

	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:{
		string name;
		cout << "Enter the name of the contact which you want find: ";
		cin >> name;
		this->findContact(name);
		break;
	}
	case 2:{
		string number;
		cout << "Enter the phone number of the contact which you want to find: ";
		cin >> number;
		this->findContact(number);
		break;
	}
	case 3:{
		string temp;
		cout << "Enter the ID of the number which you want to find: ";
		cin >> temp;
		this->findContact(temp);
		break;
	}
	default: return; break;
	}
}

unsigned int ContactBook::size()
{
	return numberOfContacts;
}


//save and load 
void ContactBook::deleteContactBook()
{
	
	ofstream out(filename, ios::trunc);

	name.deleteDictionary();
	ID.deleteDictionary();
	phoneNumber.deleteDictionary();
	bookContacts.clear();

	out.close();
}
void ContactBook::loadContactBook()
{
	ifstream in(filename, ios::in | ios::binary);
	Contact temp;
	
	unsigned int tempSize = 0;

	while (in.read((char*)&temp, sizeof(Contact)))
	{
		addContact(temp);
		++tempSize;
	}

	numberOfContacts = tempSize;

	in.close();
}

void ContactBook::saveContactBook()
{
	ofstream out(filename, ios::trunc | ios::binary);

	for (unsigned int a = 0; a < size(); a++)
	{
		bookContacts[a].saveContact();
	}

	out.close();
}

#endif