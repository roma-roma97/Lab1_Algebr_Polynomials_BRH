#include <cstring>

const int MaxSize = 100;

template <class T, class K> struct Cell
{
	T data;
	K key;
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



