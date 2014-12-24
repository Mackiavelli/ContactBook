---------------------------------------------------IDEA OF THE PROJECT----------------------------------------------------------

The main idea of the project is to create a program which handles phone contacts. The contacts are stored in binary files. The program offers some basic features, such as adding a name, phone number, and unique ID to each contact. You also have the option of sorting the contacts, adding/removing contacts, deleting the database, and finding the first contact that matches the selected criteria.

---------------------------------------------------REALIZATION------------------------------------------------------------------

There are several different parts that form the realization of the project. They are tighly connected with each other to create the functionality and interface of the Contact Book.

1. Dictionary - This is the base class that provides the storage for the information of the contacts. The Dictionary is basically a simplified Map structure. It is a template class and it has a key and a value. The class has functions for adding and removing elements, replacing values, checking if an element exists, as well as sorting. The Dictionary can hold a dynamic number of pairs within it. 

2. Contact - This is the class which creates the representation of a single contact in the program. There are 3 pieces of information that are important here - a name shorter than 100 characters, a phone number shorter than 10 digits, and an ID shorter than 10 digits. The latter are char arrays with a constant size. 
There is a predefined operator for outputting a single contact. There are functions that allow you to load and save the contact from a file, as well as setters/getters with validation for the information.

3. Contact Book - This is the class which gives us all of the functionality. Within the class we use the previously mentioned Dictionary to create maps of the three pieces of information in the Contact class (name, ID, phone number) with a contact. There is also a vector which stores all of the available contacts.
Each contact book is loaded from a file when the program is started. If the file is non-existent, then the program starts with an empty database. There are functions which allow saving and loading of all of the contacts from/to files.
There is a function which allows you to search for a contact by certain criteria. 
There are also several different sorting features which reorder the vector with the contacts, as well as all of the Dictionaries. 
The Contact Book class also has functions which display the menu through which the user interacts with the program. There is a predefined operator which allows you to output a whole contact book. 
