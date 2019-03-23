#include <cstring>

const int MaxSize = 100;

void gotoxy(int x, int y);

template <class T> struct TRecord
{
	T data;
	K key;
};

template <class T> struct Node
{
	TRecord<T> record;
	Node<T> *pNext;
	Node<T>() : pNext = nullptr{};
};

template <class T> class TableLine
{
	TRecord<T>record[MaxSize];
public:
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};

template <class T> class TableSort
{
	TRecord<T>record[MaxSize];
public:
	void Insert(T _data, K _key);
	void Delete(K _key);
	bool Search(K _key, TRecord &value);
};

template <class T> class TableList
{
	Node<T> *pFirst;
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
	<T>data[MaxSize];
public:
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};

template <class T> class TableHash
{
public:
	void Insert(T _data, string _key);
	void Delete(string _key);
	T Search(string _key);
};



