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

struct Pair
{
	int key;
	TList<T> values;
};
int Hash(int key)
{
	return key % HASH_SIZE;
}
class HashTable
{

 private:
	Pair table[MaxSize];
 public:
	 HashTable();
	void Delete(string first_key, int key_)
	{
		int index = 0;
		int tmp = Hash(key_);
		Node *p = table[tmp].values->pFirst;
		while (p != nullptr)
		{
			if (p->key != first_key)
			{
				p = p->pNext;
				index++;
			}
			if (p->key == first_key)
				table[tmp].values.DeleteEl(index);
		}
	}
	void Add(T elem, int key_)
	{
		int tmp = Hash(key_);
		table[tmp].values.push_back(elem);

	}
	TPolinom Get(ValType first_key, int key_)
	{
		int tmp = Hash(key_);
		Node *p = table[tmp].values->pFirst;
		while (p != nullptr)
		{
			if (p->key != first_key)
			{
				p = p->pNext;
				index++;
			}
			if (p-> == first_key)
				return table[tmp].values[index];
		}
	}
};




