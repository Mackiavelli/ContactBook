#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <vector>
using namespace std;


template <typename K, typename V>
class Dictionary
{
public:
	Dictionary();
	Dictionary(K[], V[]);
	Dictionary(K, V);
	Dictionary(Dictionary&);
	~Dictionary();
	void addElement(K, V);
	void addKey(K);
	void addValue(V);
	void replaceValue(K, V);
	void sortByKey();
	bool checkExisting(K);
	V searchByKey(K);

	friend ostream& operator<<(ostream& os, Dictionary& dict)
	{
		if (dict.key.size())
			dict.sortByKey();

		for (unsigned int a = 0; a < dict.key.size(); a++)
			os << "Key: " << dict.key[a] << "\tValue: " << dict.value[a] << endl;

		return os;
	}
	Dictionary& operator=(const Dictionary&);

	vector<K> key;
	vector<V> value;

}; //end class Dictionary


//begin template function definitions
template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{

}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(K newKeys[], V newValues[])
{
	for (int a = 0; a < sizeof(newKeys); a++)
	{
		key.push_back(newKeys[a]);
		value.push_back(newValues[a]);
	}
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(K newKey, V newValue)
{
	key.push_back(newKey);
	value.push_back(newValue);
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(Dictionary& dict)
{
	for (int a = 0; a < dict.key.size(); a++)
	{
		this->key.push_back(dict.key[a]);
		this->value.push_back(dict.value[a]);
	}
}

template <typename K, typename V>
void Dictionary<K, V>::replaceValue(K newKey, V newValue)
{
	for (unsigned int a = 0; a < key.size(); a++)
	{
		if (key[a] == newKey)
		{
			value[a] = newValue;
		}
	}
}

template <typename K, typename V>
bool Dictionary<K, V>::checkExisting(K newKey)
{
	for (unsigned int a = 0; a < key.size(); a++)
	{
		if (key[a] == newKey)
		{
			return true;
		}
	}

	return false;

}

template <typename K, typename V>
void Dictionary<K, V>::sortByKey()
{
	K swapKey;
	V swapValue;

	for (unsigned int a = 0; a < key.size() - 1; a++)
	{
		if (key[a] > key[a + 1])
		{
			swapKey = key[a];
			key[a] = key[a + 1];
			key[a + 1] = swapKey;

			swapValue = value[a];
			value[a] = value[a + 1];
			value[a + 1] = swapValue;

			a = -1;
		}
	}
}

template <typename K, typename V>
void Dictionary<K, V>::addElement(K newKey, V newValue)
{
	if (checkExisting(newKey))
	{
		replaceValue(newKey, newValue);
	}

	else
	{
		addKey(newKey);
		addValue(newValue);
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
V Dictionary<K, V>::searchByKey(K searchKey)
{
	for (int a = 0; a < this->key.size(); a++)
	{
		if (searchKey == key[a])
		{
			return value[a];
		}
	}

	return NULL;
}

template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::operator=(const Dictionary& dict)
{
	this->key.clear();
	this->value.clear();

	for (unsigned int a = 0; a < dict.key.size(); a++)
	{
		this->key.push_back(dict.key[a]);
		this->value.push_back(dict.value[a]);
	}

	return *this;
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
	key.clear();
	value.clear();
}
#endif