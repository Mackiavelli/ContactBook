#ifndef CONTACTS_H
#define CONTACTS_H

#include "dictionary.h"
#include "dictionary.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Contact
{
public:

	string getName() const; //selectors
	string getNumber() const;
	unsigned short getID() const;

	bool changeName(string); //mutators
	bool changeNumber(string);
	void changeID(unsigned int);
	void enterInfo();

	friend ostream& operator<<(ostream& os, const Contact* ptr)
	{
		os << "Name: " << ptr->getName() << endl
			<< "Number: " << ptr->getNumber() << endl
			<< "ID: " << ptr->getID() << endl;

		return os;
	}

	Contact();
	Contact(string, string, unsigned int);

private:
		string name;
		string phoneNumber;
		unsigned int ID;
};

class ContactBook
{
public:
	ContactBook();
	void addContact();
	const Contact* findContact(unsigned int) const;
	const Contact* findContact(string) const;
	void sortContactBook(unsigned int);
	void removeContact();
	void printBook();
	void sortByName();
	void sortByNumber();
	void sortByID();
	void requestNewCriterion();
	void swapElements(unsigned int);
	void findMenu();
	~ContactBook();

	vector<Contact> bookContacts;

	Dictionary<string, Contact*> name;
	Dictionary<string, Contact*> phoneNumber;
	Dictionary<unsigned short, Contact*> ID;
};

#endif

