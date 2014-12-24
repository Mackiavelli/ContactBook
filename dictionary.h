#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <vector>
using namespace std;

template <typename K, typename V>
class Dictionary
{
public:
	//constructors and destructor
	Dictionary();
	Dictionary(K, V);
	Dictionary(Dictionary&);
	~Dictionary();

	//get and set methods for keys and values
	K getKey(unsigned int) const;
	V getValue(unsigned int) const;
	bool setKey(K, unsigned int);
	bool setValue(V, unsigned int);

	//adding and removing elements
	void addElement(K, V);
	void addKey(K);
	void addValue(V);
	bool removeElement(K);
	bool removeElement(unsigned int);

	//sorting
	void sortByKey();
	void swapElements(unsigned int, unsigned int);

	//utility
	unsigned int size() const;	
	void replaceValue(K, V);	
	bool checkExisting(K);	
	V searchByKey(K);
	void deleteDictionary();

	//operators
	friend ostream& operator<<(ostream& os, Dictionary& dict)
	{
		if (dict.key.size())
			dict.sortByKey();

		for (unsigned int a = 0; a < dict.key.size(); a++)
			os << "Key: " << dict.key[a] << "\tValue: " << dict.value[a] << endl;

		return os;
	}
	Dictionary& operator=(const Dictionary&);

private:
	vector<K> key;
	vector<V> value;
	unsigned int dictionarySize;

}; //end class Dictionary


//begin template function definitions
//constructors and destructor
template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{
	dictionarySize = 0;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(K newKey, V newValue)
{
	key.push_back(newKey);
	value.push_back(newValue);
	dictionarySize = 1;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(Dictionary& dict)
{
	unsigned int a;
	for (a = 0; a < dict.size(); a++)
	{
		this->key.push_back(dict.key[a]);
		this->value.push_back(dict.value[a]);
	}
	dictionarySize = ++a;
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
	key.clear();
	value.clear();
}


//get and set methods for keys and values
template <typename K, typename V>
bool Dictionary<K, V>::setKey(K element, unsigned int position)
{
	key[position] = element;
	return true;
}

template <typename K, typename V>
bool Dictionary<K, V>::setValue(V element, unsigned int position)
{
	value[position] = element;
	return true;
}

template < typename K, typename V >
K Dictionary<K, V>::getKey(unsigned int position) const
{
	return key[position];
}

template < typename K, typename V>
V Dictionary<K, V>::getValue(unsigned int position) const
{
	return value[position];
}


//adding and removing elements
template <typename K, typename V>
void Dictionary<K, V>::addElement(K newKey, V newValue)
{
	if (checkExisting(newKey))
	{
		cout << "An element with that key already exists!\n\n";
		return;
	}

	else
	{
		addKey(newKey);
		addValue(newValue);
		++dictionarySize;
	}
}

template <typename K, typename V>
void Dictionary <K, V>::addKey(K newKey)
{
	key.push_back(newKey);
}

template <typename K, typename V>
void Dictionary<K, V>::addValue(V newValue)
{
	value.push_back(newValue);
}

template <typename K, typename V>
bool Dictionary<K, V>::removeElement(K removeKey)
{
	for (unsigned int a = 0; a < this->size(); a++)
	{
		if (this->key[a] == removeKey)
		{
			this->key.erase(key.begin() + a);
			this->value.erase(value.begin() + a);
			--dictionarySize;
			return true;
		}
	}
	return false;
}

template <typename K, typename V>
bool Dictionary<K, V>::removeElement(unsigned int removePos)
{
	this->key.erase(key.begin() + removePos);
	this->value.erase(value.begin() + removePos);
	--dictionarySize;
	return true;
}


//sorting
template <typename K, typename V>
void Dictionary<K, V>::sortByKey()
{

	for (unsigned int a = 0; a < key.size() - 1; a++)
	{
		if (key[a] > key[a + 1])
		{
			swapElements(a, a + 1);
			a--;
		}
	}
}

template <typename K, typename V>
void Dictionary<K, V>::swapElements(unsigned int firstPos, unsigned int secondPos)
{
	K kTemp = this->key[firstPos];
	V vTemp = this->value[firstPos];

	this->key[firstPos] = this->key[secondPos];
	this->value[firstPos] = this->value[secondPos];

	this->key[secondPos] = kTemp;
	this->value[secondPos] = vTemp;
}


//utility
template <typename K, typename V>
void Dictionary<K, V>::replaceValue(K tempKey, V newValue)
{
	for (unsigned int a = 0; a < this->size(); a++) //this added for logical clarity
	{
		if (key[a] == tempKey)
		{
			value[a] = newValue;
		}
	}
}

template <typename K, typename V>
void Dictionary<K, V>::deleteDictionary()
{
		key.clear();
		value.clear();
}

template <typename K, typename V>
unsigned int Dictionary<K, V>::size() const
{
	return dictionarySize;
}

template <typename K, typename V>
bool Dictionary<K, V>::checkExisting(K newKey)
{
	for (unsigned int a = 0; a < size(); a++) 
	{
		if (key[a] == newKey)
		{
			return true;
		}
	}

	return false;

}

template <typename K, typename V>
V Dictionary<K, V>::searchByKey(K searchKey)
{
	for (int a = 0; a < this->size(); a++)
	{
		if (searchKey == key[a])
		{
			return value[a];
		}
	}

	return NULL; //has to be handled in the calling function
}


//operators
template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::operator=(const Dictionary& dict)
{
	unsigned int a;
	this->key.clear();
	this->value.clear();

	for (a = 0; a < dict.size(); a++)
	{
		this->key.push_back(dict.key[a]);
		this->value.push_back(dict.value[a]);
	}
	dictionarySize = a;

	return *this;
}

#endif