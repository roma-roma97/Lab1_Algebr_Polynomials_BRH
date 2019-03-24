#include <cstring>

const int MaxSize = 100;
using namespace std;

template <class T, typename K> struct TRecord
{
	T data;
	K key;
};

template <class T> class TableLine
{
	TRecord <T, string> data[MaxSize];
	int count = 0;
public:
	void Insert(T _data, string _key)
	{
		if (count == 0)
		{
			data[count].key = _key;
			data[count].data = _data;
			count++;
		}
		else {
			for (int i = 0; i < count; i++)
			{
				if (_key == data[i].key)
					throw ("Key is set");
				else {
					data[count].key = _key;
					data[count].data = _data;
					count++;
				}
			}
		}
	}
	void Delete(string _key)
	{
		if (count == 0)
			throw("Table is empty");
		else {
			for (int i = 0; i < count; i++)
			{
				if (data[i].key == _key)
				{
					data[i].key = data[count].key;
					data[i].data = data[count].data;
				}
			}
			count--;
		}
	}
	T Search(string _key)
	{
		if (count == 0)
			throw("Table is empty");
		else {
			for (int i = 0; i < count; i++)
				if (data[i].key == _key)
					return data[i].data;
		}
	}
};


template <class T> class TableSort
{
	TRecord<T, string>data[MaxSize];
	int count = 0;
public:

	void Sort(TRecord *_data, int _count)
	{
		TRecord <T, string> tmp;
		int ind;
		for (int i = 1; i < _count; i++)
		{
			tmp = _data[i];
			ind = i - 1;
			while (ind >= 0 && _data[ind].key > tmp.key)
			{
				_data[ind + 1] = _data[ind];
				_data[ind] = tmp;
				ind--;
			}
		}
	}
	void Insert(T _data, string _key)
	{
		if (count == 0)
		{
			data[count].key = _key;
			data[count].data = _data;
			count++;
		}
		else {
			for (int i = 0; i < count; i++)
			{
				if (_key == data[i].key)
					throw ("Key is set");
				else {
					data[count].key = _key;
					data[count].data = _data;
					count++;
				}
			}
			Sort(data, count);
		}
	}
	void Delete(string _key)
	{
		if (count == 0)
			throw("Table is empty");
		else
		{
			for (int i = 0; i < count; i++)
			{
				if (data[i].key == _key)
				{
					data[i].key = data[count].key;
					data[i].data = data[count].data;
				}
			}
			count--;
			Sort(data, count);
		}
	}
	T Search(string _key)
	{
		if (count == 0)
			throw("Table is empty");
		else {
			for (int i = 0; i < count; i++)
				if (data[i].key == _key)
					return data[i].data;
		}
	}
};

template <class T> class TableList
{
	TList<TRecord<T, string>> data;
public:
	TableList()
	{

	}
	void Insert(T _data, string _key)
	{
	}
	void Delete(string _key)
	{

	}
	T Search(string _key)
	{

	}
};

template <class T> class TableTree
{
	//Cell<T, string>data[MaxSize];
public:
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};

template <class T> class TableHashList
{
	Cell<T, string>data[MaxSize];
public:
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};

template <class T> class TableHash
{
	Cell<T, string>data[MaxSize];
public:
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};

template<class T>
inline void TableLine<T>::Insert(T _data, string _key)
{
}
