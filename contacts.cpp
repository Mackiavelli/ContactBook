#ifndef CONTACTS_CPP
#define CONTACTS_CPP

#include "contacts.h"

string Contact::getName() const
{
	return this->name;
}

string Contact::getNumber() const
{
	return this->phoneNumber;
}

unsigned short Contact::getID() const
{
	return this->ID;
}

bool Contact::changeName(string newName)
{
	if (newName != "")
	{
		this->name = newName;
		return true;
	}
	else
	{
		cout << "You can't change the name to an empty string!\n";
		return false;
	}
}



bool Contact::changeNumber(string newNumber)
{
	if (newNumber != "")
	{
		this->phoneNumber = newNumber;
		return true;
	}
	else
	{
		cout << "You can't change the number to an empty string!\n";
		return false;
	}
}

void Contact::changeID(unsigned int newID)
{
	this->ID = newID;
}

Contact::Contact(string newName, string newNumber, unsigned int newID)
{
	this->name = newName;
	this->phoneNumber = newNumber;
	this->ID = newID;
}

Contact::Contact()
{
}


void Contact::enterInfo()
{
	string newName;
	string newNumber;
	unsigned short newID;

	cout << "Please enter a contact name: ";
	cin >> newName;
	if (!changeName(newName))
	{
		cout << "Error. You will have to create the contact again!";
		return;
	}

	cout << "Please enter a phone number: ";
	cin >> newNumber;
	if (!changeNumber(newNumber))
	{
		cout << "Error. You will have to create the contact again!";
		return;
	}

	cout << "Please enter an ID: ";
	cin >> newID;
	changeID(newID);
}

ContactBook::~ContactBook()
{
	bookContacts.clear(); // dictionary objects clear from their own destructors

}

ContactBook::ContactBook()
{
}

void ContactBook::addContact()
{
	Contact* temp = new Contact();
	temp->enterInfo();
	name.addElement(temp->getName(), temp);
	phoneNumber.addElement(temp->getNumber(), temp);
	ID.addElement(temp->getID(), temp);
	
	bookContacts.push_back(*temp);
}

//swaps two consecutive elements in the arrays
void ContactBook::swapElements(unsigned int position)
{
	string swapName;
	string swapNumber;
	unsigned short swapID;
	Contact swapContacts;
	Contact* swapContact;

	swapName = name.key[position];
	name.key[position] = name.key[position + 1];
	name.key[position + 1] = swapName;

	swapNumber = phoneNumber.key[position];
	phoneNumber.key[position] = phoneNumber.key[position + 1];
	phoneNumber.key[position + 1] = swapNumber;

	swapID = ID.key[position];
	ID.key[position] = ID.key[position + 1];
	ID.key[position + 1] = swapID;

	swapContacts = bookContacts[position];
	bookContacts[position] = bookContacts[position + 1];
	bookContacts[position + 1] = swapContacts;

	swapContact = name.value[position];
	name.value[position] = name.value[position + 1];
	name.value[position + 1] = swapContact;

}

void ContactBook::sortByName()
{
	for (unsigned int a = 0; a < name.key.size() - 1; a++)
	{
		if (name.key[a] > name.key[a + 1])
		{
			swapElements(a);
			a = -1;
		}
	}
}

void ContactBook::sortByNumber()
{
	for (unsigned int a = 0; a < phoneNumber.key.size() - 1; a++)
		if (phoneNumber.key[a] > phoneNumber.key[a + 1])
		{
		swapElements(a);
		a = -1;
		}
}

void ContactBook::sortByID()
{
	for (unsigned int a = 0; a < ID.key.size() - 1; a++)
		if (ID.key[a] > ID.key[a + 1])
		{
		swapElements(a);
		a = -1;
		}
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

void ContactBook::printBook()
{
	requestNewCriterion();

	for (unsigned int a = 0; a < name.key.size(); a++)
	{
		cout << " Name: " << name.key[a] << endl
			<< "Number: " << phoneNumber.key[a] << endl
			<< "ID: " << ID.key[a] << endl;
	}
}

const Contact* ContactBook::findContact(unsigned int searchID) const
{
	for (unsigned int a = 0; a < ID.key.size(); a++)
	{
		if (ID.key[a] == searchID)
		{
			return ID.value[a];
		}
	}

	return 0;

}

const Contact* ContactBook::findContact(string searchParameter) const
{
	for (unsigned int a = 0; a < name.key.size(); a++)
	{
		if (!(name.key[a].compare(searchParameter)))
		{
			return name.value[a];
		}

		else if (!(phoneNumber.key[a].compare(searchParameter)))
		{
			return phoneNumber.value[a];
		}
	}

	return 0;
}

void ContactBook::removeContact()
{
	int choice;
	string findString;
	unsigned short findID;

	cout << "How do you wish to find the contact which you want to delete?" << endl
		<< "1. Name or Phone" << endl
		<< "2. ID " << endl
		<< "Enter your choice: " << endl;

	cin >> choice;

	if (choice == 1)
	{
		cout << "Enter the name or the number: ";
		cin >> findString;

		if (findContact(findString))
		{
			for (unsigned int a = 0; a < name.key.size(); a++)
			{
				if (name.key[a] == findString)
				{
					name.key.erase(name.key.begin() + a);
					name.value.erase(name.value.begin() + a);

					phoneNumber.key.erase(phoneNumber.key.begin() + a);
					phoneNumber.value.erase(phoneNumber.value.begin() + a);

					ID.key.erase(ID.key.begin() + a);
					ID.value.erase(ID.value.begin() + a);

					bookContacts.erase(bookContacts.begin() + a);

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

		if (findContact(findID))
		{
			for (unsigned int a = 0; a < name.key.size(); a++)
			{
				if (ID.key[a] == findID)
				{
					name.key.erase(name.key.begin() + a);
					name.value.erase(name.value.begin() + a);

					phoneNumber.key.erase(phoneNumber.key.begin() + a);
					phoneNumber.value.erase(phoneNumber.value.begin() + a);

					ID.key.erase(ID.key.begin() + a);
					ID.value.erase(ID.value.begin() + a);

					bookContacts.erase(bookContacts.begin() + a);

					break;
				}
			}
			cout << "Contact successfully removed!\n";
		}
	}


}

void ContactBook::findMenu()
{
	cout << "Enter your search criteria: " << endl
		<< "1. Name" << endl
		<< "2. Phone Number" << endl
		<< "3. ID" << endl;

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
		unsigned int temp;
		cout << "Enter the ID of the number which you want to find: ";
		cin >> temp;
		this->findContact(temp);
		break;
	}
	default: return; break;
	}
}

#endif // CONTACTS_CPP

