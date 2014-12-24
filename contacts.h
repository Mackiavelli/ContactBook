#ifndef CONTACTS_H
#define CONTACTS_H

#include "dictionary.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Contact
{
public:
	//constructors and destructor
	Contact();
	Contact(string, string, string);
	~Contact();

	//getters and setters
	string getName() const; //selectors
	string getNumber() const;
	string getID() const;
	bool changeName(string); //mutators
	bool changeNumber(string);
	bool changeID(string);
	void enterInfo();

	//save
	void saveContact();

	//utility
	bool validateNumber(string);

	//operators
	friend ostream& operator<<(ostream& os, const Contact* ptr)
	{
		os << endl 
			<< "Name: " << ptr->getName() << endl
			<< "Number: " << ptr->getNumber() << endl
			<< "ID: " << ptr->getID() << endl;

		return os;
	}

	friend ostream& operator<<(ostream& os, const Contact ptr)
	{
		os << endl
			<< "Name: " << ptr.getName() << endl
			<< "Number: " << ptr.getNumber() << endl
			<< "ID: " << ptr.getID() << endl;

		return os;
	}
	
private:
	//all the chars have an extra space for the null character
	char name[101];
	char phoneNumber[11];
	char ID[11];
};
	
#endif