#ifndef __TABLE_H__
#define __TABLE_H__

#include <string>
#include <vector>
#include "list.h"

using namespace std;

const int MaxSize = 100;

template <class T> struct TRecord
{
	T data;
	int key;
	TRecord() {};
	TRecord(T _data, int _key) : data(_data), key(_key) {};
	TRecord& operator=(TRecord<T> &tmp)
	{
		data = tmp.data;
		key = tmp.key;
		return *this;
	}
};

template <class T> class TableLine
{
	TRecord <T> data[MaxSize];
	int count = 0;
public:
	void Insert(T _data, int _key)
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
					throw (string("Key is set"));
			}

			data[count].key = _key;
			data[count].data = _data;
			count++;

		}
	}
	void Delete(int _key)
	{
		bool flag = true;
		if (count == 0)
			throw(string("Table is empty"));
		else
		{
			if (count == 1)
			{
				count--;
			}
			for (int i = 0; i < count; i++)
			{
				if (data[i].key == _key)
				{
					data[i].key = data[count-1].key;
					data[i].data = data[count-1].data;
					flag = false;
				}
			}
			if (flag)
				throw(string("Key is not found!"));
			count--;
		}
	}
	T Search(int _key)
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

template <class T> class TableSort
{
	TRecord<T>data[MaxSize];
	int count = 0;
public:
	void Sort(TRecord <T> *_data, int _count)
	{
		TRecord<T> tmp;
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
	void Insert(T _data, int _key)
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
			}
			data[count].key = _key;
			data[count].data = _data;
			count++;
		}
		Sort(data, count);
	}
	void Delete(int _key)
	{
		if (count == 0)
			throw("Table is empty");
		else
		{
			for (int i = 0; i < count; i++)
			{
				if (data[i].key == _key)
				{
					data[i].key = data[count-1].key;
					data[i].data = data[count-1].data;
				}
			}
			count--;
			Sort(data, count);
		}
	}
	T Search(int _key)
	{
		if (count == 0)
			throw("Table is empty");
		else
		{
			bool flag = false;
			int l = 0;
			int r = count;
			int mid;
			while ((l <= r) && (flag != true))
			{
				mid = (l + r) / 2;
				if (data[mid].key == _key)
					flag = true;
				if (data[mid].key > _key)
					r = mid - 1;
				else l = mid + 1;
			}
			if (flag == false)
				throw("Key isn`t found");
			return data[mid].data;
		}
	}
	void PrintTable()
	{
		for (int i = 0; i < count; i++)
			cout << data[i].key << "|" << data[i].data << endl;
	}
};

template <class T> class TableList
{
	TList<TRecord<T>> data;
public:
	void Insert(T _data, int _key)
	{
		TRecord<T> tmp;
		tmp.data = _data;
		tmp.key = _key;
		data.Push_back(tmp);
	}
	void Delete(int _key)
	{
		int count = 0;
		Node<TRecord<T>> *first = data.begin();
		while (first!= nullptr)
		{
			if (first->key.key == _key)
			{
				data.DeleteEl(count);
				return;
			}
			count++;
			first = first->pNext;
		}
	}
	T Search(int _key)
	{
		Node<TRecord<T>> *first = data.begin();
		while (first != nullptr)
		{
			if (first->key.key == _key)
				return first->key.data;
			first = first->pNext;
		}
		throw("Keys isn`t found");
	}
	void Show()
	{
		for (int i = 0; i < data.GetSize(); i++)
		{
			cout << data[i].key << "|";
			cout << data[i].data << endl;
		}
	}
};

template <class T> struct node
{
	int key;
	int height;
	T data;
	node<T> *parent;
	node<T> *left_child;
	node<T> *right_child;

	node(int _key, node<T> *_parent, node<T> *_left_child, node<T> *_right_child)
	{
		key = _key;
		parent = _parent;
		left_child = _left_child;
		right_child = _right_child;
		height = this->calc_height();
	}

	node(int _key, node *_parent)
	{
		key = _key;
		parent = _parent;
		height = 1;
		left_child = nullptr;
		right_child = nullptr;
	}

	~node() {}


	int get_balance_factor() //возвращает балланс-фактор для данного узла (return balance-factor for this node)
	{
		int lh = left_child ? left_child->height : 0;
		int rh = right_child ? right_child->height : 0;
		return (rh - lh);
	}

	int calc_height() //рассчитывает высоту узла (исходя из условия что высота потомков уже рассчитана) (calculating height of node (only if we know height of children))
	{
		int lh = left_child ? left_child->height : 0;
		int rh = right_child ? right_child->height : 0;
		height = ((lh > rh) ? lh : rh) + 1;
		return height;
	}
};

template <class T> class AVL_tree
{
private:
	node<T> *root;
	int num_nodes; //кол-во узлов в дереве (counts of nodes in tree)

	node<T> *GetMinChild(node<T> *_node) //возвращает указатель на минимального потомка узла. 
	{
		node<T> *cur_node = _node;

		while (cur_node->left_child) {
			cur_node = cur_node->left_child;
		}

		return cur_node;
	}

	void RecursPrintTree(node<T> *_node)
	{
		if (_node != nullptr)
		{
			RecursPrintTree(_node->left_child);
			RecursPrintTree(_node->right_child);
			cout << _node->key << "|" << _node->data << endl;
		}
	}

	void DeleteSimpleNode(node<T> *del_node) //удаление узла, у которого не более одного дочернего узла (deleting node which dont have more than one child node)
	{
		if (!del_node->right_child) {  //если у узла del_node нет правого дочернего узла (if node "del_node" have no right child node) 
			if (del_node == root) {
				root = del_node->left_child;
				if (!root) {
					root = new node<T>(0, nullptr);
				}
			}
			else if (del_node == del_node->parent->left_child) {
				del_node->parent->left_child = del_node->left_child;
			}
			else if (del_node == del_node->parent->right_child) {
				del_node->parent->right_child = del_node->left_child;
			}

			if (del_node->left_child) {
				del_node->left_child->parent = del_node->parent;
			}
		}
		else if (!del_node->left_child) {  //если у узла del_node нет левого дочернего узла (if node "del_node" have no left child node)
			if (del_node == root) {
				root = del_node->right_child;
				if (!root) {
					root = new node<T>(0, nullptr);
				}
			}
			else if (del_node == del_node->parent->left_child) {
				del_node->parent->left_child = del_node->right_child;
			}
			else if (del_node == del_node->parent->right_child) {
				del_node->parent->right_child = del_node->right_child;
			}

			if (del_node->right_child) {
				del_node->right_child->parent = del_node->parent;
			}
		}
		node<T> *cur_node = del_node->parent;
		delete del_node;

		while (cur_node)
		{  //баллансируем. (balancing)
			cur_node->calc_height();
			Balance(cur_node);
			cur_node = cur_node->parent;
		}
	}
	
	void ClearRecursion(node<T>* start_clear_node) //вызывается деструктором. (called by destructor)
	{
		node<T>*cur_clear_node = start_clear_node;
		if (cur_clear_node) {
			ClearRecursion(cur_clear_node->left_child);
			ClearRecursion(cur_clear_node->right_child);
			delete cur_clear_node;
		}
	}

	node<T>* Rotate(node<T>* rotate_node, bool left)  // поворот влево или вправо (rotate left/right)
	{
		node<T>* tmp;
		if (left)
		{
			tmp = rotate_node->right_child;
			rotate_node->right_child = rotate_node->left_child;
			rotate_node->left_child = tmp;
		}
		else
		{
			tmp = rotate_node->left_child;
			rotate_node->left_child = rotate_node->right_child;
			rotate_node->right_child = tmp;
		}

		rotate_node->calc_height();
		//tmp->calc_height();
		return rotate_node;
	}
	void Balance(node<T>* b_node) //балансировка узла (balancing of node)
	{
		if (b_node->get_balance_factor() == -2) {
			if (b_node->left_child->get_balance_factor() < 0) {
				Rotate(b_node->left_child, true);
			}
			else if (b_node->left_child->get_balance_factor() > 0) {
				Rotate(b_node->left_child, false);
			}
			Rotate(b_node, true);
		}
		else if (b_node->get_balance_factor() == 2) {
			if (b_node->right_child->get_balance_factor() < 0) {
				Rotate(b_node->right_child, true);
			}
			else if (b_node->right_child->get_balance_factor() > 0) {
				Rotate(b_node->right_child, false);
			}
			Rotate(b_node, false);
		}
	}

public:
	AVL_tree()
	{
		root = new node<T>(0, nullptr);
		num_nodes = 0;
	}
	~AVL_tree()
	{
		ClearRecursion(root);
	}
	void Insert_node(T _data, int ins_key)
	{
		if (num_nodes==0)
		{
			root->key = ins_key;
			root->data = _data;
			num_nodes++;
			return;
		}

		node<T> *cur_node = root;
		while (true) {
			if (ins_key < cur_node->key) {
				if (cur_node->left_child!=nullptr) {
					cur_node = cur_node->left_child;
				}
				else {
					cur_node->left_child = new node<T>(ins_key, cur_node);
					cur_node->left_child->data = _data;
					break;
				}
			}
			else {
				if (cur_node->right_child!=nullptr) {
					cur_node = cur_node->right_child;
				}
				else {
					cur_node->right_child = new node<T>(ins_key, cur_node);
					cur_node->right_child->data = _data;
					break;
				}
			}
		}
		num_nodes++;

		while (cur_node)
		{ //баллансируем. (balancing)
			cur_node->calc_height();
			Balance(cur_node);
			cur_node = cur_node->parent;
		}
	}
	bool Delete_node(int del_key)  //дерево баллансируется в функции DeleteSimpleNode. (tree is balanced in function "...")
	{
		node<T> *del_node = SearchByKey(del_key);

		if ((num_nodes!=0) && (del_node!=nullptr)) { //если такой узел присутствует в дереве. (if such node assist in tree)
			if (!del_node->left_child || !del_node->right_child) { //если у узла del_node не более одного дочерних узла. (if node "del_node" dont have more than one child node)
				DeleteSimpleNode(del_node);
			}
			else {   //если у узла del_node два дочерних узла. (if node "del_node" two child node)
				node<T> *successor_node = GetMinChild(del_node->right_child);
				del_node->key = successor_node->key;

				DeleteSimpleNode(successor_node);
			}
			num_nodes--;
			return true;
		}
		else {
			return false;
		}
	}
	node<T>* SearchByKey(int seek_key)
	{
		node<T> *cur_node = root;
		while ((cur_node!=nullptr) && (cur_node->key != seek_key)) {
			if (seek_key < cur_node->key)
				cur_node = cur_node->left_child;
			else
				cur_node = cur_node->right_child;
		}
		return cur_node;
	}
	void Clear_tree()
	{
		ClearRecursion(root->left_child);
		ClearRecursion(root->right_child);
		num_nodes = 0;
		root->left_child = nullptr;
		root->right_child = nullptr;
		root->height = 1;
	}
    void Print_tree()
	{
		RecursPrintTree(root);
	}
};

inline int Hash(int key)
{
	return key % MaxSize;
}

template <class T> class HashTable
{
private:
	TList<TRecord<T>> table[100];
public:
	void Delete(int key_)
	{
		int tmp = Hash(key_);
		for (int i = 0; i < table[tmp].GetSize(); i++)
		{
			if (table[tmp][i].key == key_)
			{
				table[tmp].DeleteEl(i);
				return;
			}
		}
		throw "Key is not found";
	}
	void Insert(T elem, int key_)
	{
		int tmp = Hash(key_);
		TRecord<T> El(elem, key_);
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
		throw "Key is not found";
	}
	void Show()
	{
		for (int i = 0; i < MaxSize; i++)
		{
			for (int j = 0; j < table[i].GetSize(); j++)
			{
				cout << table[i][j].key << "|" << table[i][j].data << endl;
			}
		}
	}
};
template <class T> struct tab
{
	int key;
	T rec;
	bool flag = false;
	tab() {};
};
template <class T> class Hash_Table
{
private:
	tab<T> table[MaxSize];
public:
	Hash_Table() {};
	void Delete(int key_)
	{
		int tmp = Hash(key_);
		if (table[tmp].key == key_ && table[tmp].flag)
		{
			table[tmp].flag = false;
			return;
		}
		else
		{
			while (table[tmp].key != key_ && table[tmp].flag)
			{
				tmp++;
				if (tmp == (MaxSize + 1))
					throw "Key is not found";
			}
			if (table[tmp].key == key_)
			{
				table[tmp].flag = false;
				return;
			}
		}
		throw "Key is not found";
	}
	void Insert(T elem, int key_)
	{
		int tmp = Hash(key_);
		while (table[tmp].flag)
		{
			tmp++;
		}
		if (!table[tmp].flag)
		{
			table[tmp].rec = elem;
			table[tmp].key = key_;
			table[tmp].flag = true;
		}
	}
	T Search(int key_)
	{
		int tmp = Hash(key_);
		while (table[tmp].flag)
		{
			if (table[tmp].key == key_)
				return table[tmp].rec;
			tmp++;
			if (tmp == (MaxSize + 1))
				throw "Key is not found";
		}
		if (!table[tmp].flag)
			throw "Key is not found";
	}
	void Show()
	{
		for (int i = 0; i < MaxSize; i++)
		{
			if (table[i].flag)
				cout << table[i].key << "|" << table[i].rec << "|" << endl;
		}
	}
};

#endif