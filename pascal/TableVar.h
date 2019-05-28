#pragma once

#include <string>

using namespace std;

template<class T> struct Var
{
	T value;
	bool sconst;
	Var() :sconst(false) {};
};

template <class T> struct TRecord
{
	T data;
	string key;
	TRecord() {};
	TRecord(T _data, string _key) : data(_data), key(_key) {};
};

template <class T> class TableLine
{
	TRecord <T> data[100];
	int count = 0;
public:
	void Insert(T _data, string _key)
	{
		data[count].key = _key;
		data[count].data = _data;
		count++;
	}
	void Delete(string _key)
	{
		bool flag = true;
		if (count == 0)
			throw(string("Table is empty"));
		else
		{
			if (count == 1)
			{
				count--;
				return;
			}
			for (int i = 0; i < count; i++)
			{
				if (data[i].key == _key)
				{
					data[i].key = data[count - 1].key;
					data[i].data = data[count - 1].data;
					flag = false;
				}
			}
			if (flag)
				throw(string("Key is not found!"));
			count--;
		}
	}
	T Search(string _key)
	{
		if (count == 0)
			throw(string("Table is empty"));
		else {
			for (int i = 0; i < count; i++)
				if (data[i].key == _key)
					return data[i].data;
			throw(string("Key isn`t found"));
		}
	}
	void PrintTable()
	{
		for (int i = 0; i < count; i++)
			cout << data[i].key << "|" << data[i].data << endl;
	}
};


struct TableVar
{
	TableLine<int> tabint;
	TableLine<int> tabintc;
	TableLine<double> tabdoub;
	TableLine<double> tabdoubc;
	void* Find()
	{
	}
};