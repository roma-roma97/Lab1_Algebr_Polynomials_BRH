#include <cstring>
#include "list.h"
const int MaxSize = 100;

template <class T> struct TRecord
{
	TList<T> data;
	int key;
};

template <class T> class TableLine
{
	Cell<T, string>data[MaxSize];
public:
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};

template <class T> class TableSort
{
	Cell<T, string>data[MaxSize];
public:
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};

template <class T> class TableList
{
	TList<Cell<T, string>> data;
public:
	TableList();
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};

template <class T> class TableTree
{
	//Cell<T, string>data[MaxSize];
public:
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};


template<class T> struct Cell
{
	T data;
	int key;
	Cell() 
	{
		data = NULL;
		key = 0;
	}
	Cell(T elem, int k)
	{
		data = elem;
		key = k;
	}
};
int Hash(int key)
{
	return key % MaxSize;
};
template <class T> class HashTable
{
private:
	TList<Cell<T>> table[MaxSize];
public:
	HashTable();
	void Delete(int key_)
	{
		int tmp = Hash(key_);
		for (int i = 0; i < table[tmp].GetSize(); i++)
		{
			if (table[tmp][i].key == key_)
				table[tmp].DeleteEl(i);
		}
	}
	void Insert(T elem, int key_)
	{
		int tmp = Hash(key_);
		Cell<T> El(elem, key_);
		table[tmp].Push_back(El);
	}
	T Search(int key_)
	{
		int tmp = Hash(key_);
		for (int i = 0; i < table[tmp].GetSize(); i++)
		{
			if (table[tmp][i].key == key_)
				return table[tmp][i].data;
		}
	}
};
template <class T> struct tab
{
	int key;
	T rec;
	bool flag = false;
};
template <class T> class Hash_Table
{
private:
	tab<T> table[MaxSize];
public:
	Hash_Table() {};
		void Delete(int key_)
	{
			tmp = Hash(key_);
			while (table[tmp].key != key_)
			{
				tmp++;
			}
			if (table[tmp].key == key_)
				table[tmp].flag = false;
	}
	void Insert(T elem, int key_)
	{
		tmp = Hash(key_);
		while (table[tmp].flag)
		{
			tmp++;
		}
		if (!table[tmp].flag)
		{
			table[tmp].rec = elem;
			table[tmp].key = key_;
		}
	}
	T Search(int key_)
	{
		for (int i = 0; i < MaxSize; i++)
		{
			if (table[i].key == key_)
				return table[i].rec;
			else
				cout << "Key is not found"<<endl;
		}

	}
};





