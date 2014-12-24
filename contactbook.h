#include <iostream>
#include <vector>

#include "contacts.h"

using namespace std;

class ContactBook
{
public:
	//constructors
	ContactBook();
	ContactBook(Dictionary<string, Contact*>,
		Dictionary<string, Contact*>, Dictionary<string, Contact*>);
	ContactBook(ContactBook&);
	~ContactBook();

	// add\remove contacts
	void addContact();
	void addContact(Contact);
	void removeContact();

	//find contacts
	const Contact* findContact(string);
	
	//sorting
	void sort(Dictionary<string, Contact*>);
	void sortContactBook(unsigned int);
	void sortByName();
	void sortByNumber();
	void sortByID();
	void requestNewCriterion();
	void swapElements(unsigned int, unsigned int);

	//utility
	bool displayMenu();
	void displayFindMenu();
	void printBook();
	unsigned int size();

	//save and load
	void deleteContactBook();
	void loadContactBook();
	void saveContactBook();

	//operators
	friend ostream& operator<<(ostream& os, ContactBook& temp)
	{
		if (temp.size())
		{
			for (unsigned int a = 0; a < temp.bookContacts.size(); a++)
			{
				os << temp.bookContacts[a] << endl;
			}
		}
		else
		{
			cout << "No contacts found!!!\n\n";
		}
		return os;
	}


private:
	vector<Contact> bookContacts;

	Dictionary<string, Contact*> name;
	Dictionary<string, Contact*> phoneNumber;
	Dictionary<string, Contact*> ID;

	unsigned int numberOfContacts;
};