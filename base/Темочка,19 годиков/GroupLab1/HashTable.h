#pragma once
#include "list.h"
#include "polinom.h"
#include <string>
#include <vector>
#define HASH_SIZE 100
using namespace std;
struct Pair
{
	int key;
	TList<TPolinom> values;
};
int Hash(int key)
{
	return key % HASH_SIZE;
}
template <class TList, class ValType>
class HashTable
{
private:
	Pair table[HASH_SIZE];
	int count;
public:
	HashTable()
	{
		count = 0;
	}
	void Delete(ValType first_key,int key_)
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
			if (p-> == first_key)
				table[tmp].values.DeleteEl(index);
		}
	}
	void Add(T elem,int key_)
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
