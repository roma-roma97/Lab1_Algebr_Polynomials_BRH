#ifndef __TABLE_H__
#define __TABLE_H__

#include <string>

using namespace std;

const int MaxSize = 100;

template <class T> struct TRecord
{
	T data;
	int key;
	TRecord(T _data = NULL, int key = NULL) : data(_data), key(_key) {};
};

template <class T> class TableLine
{
	TRecord <T> data[MaxSize];
	int count = 0;
public:
	void Insert(T _data, int _key)
	{
		if (count == MaxSize)
			throw("Don't memory");
		data[count].key = _key;
		data[count].data = _data;
		count++;
	}
	void Delete(int _key)
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
			return;
		}
		throw("File don't search");
	}
	T Search(int _key)
	{
		if (count == 0)
			throw("Table is empty");
		else {
			for (int i = 0; i < count; i++)
				if (data[i].key == _key)
					return data[i].data;
			throw("File don't search");
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

	void Sort(TRecord *_data, int _count)
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
		if (count == MaxSize)
			throw("Don't memory");
		if (count == 0)
			throw("Table is empty");
		else {
			data[count].data = _data;
			data[count].key = _key;
			Sort(data, count);
			count++;
		}
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
					data[i].key = data[count].key;
					data[i].data = data[count].data;
					count--;
					Sort(data, count);
					return;
				}
			}
			throw("File don't search");
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
	TableList()
	{

	}
	void Insert(T _data, int _key)
	{
	}
	void Delete(int _key)
	{

	}
	T Search(int _key)
	{

	}
};

template <class T> class AVL_tree
{
	struct node
	{
		int key;
		int height;
		node *parent;
		node *left_child;
		node *right_child;
		node(int _key, node *_parent)
		{
			key = _key;
			height = 1;
			parent = _parent;
			left_child = nullptr;
			right_child = nullptr;
		}
		node(int, int, node*, node*, node*);
		~node() {}
		void calc_height() 
		{
			if (left_child && right_child) {
				height = max(left_child->height, right_child->height) + 1;
			}
			else if (left_child) {
				height = left_child->height + 1;
			}
			else if (right_child) {
				height = right_child->height + 1;
			}
			else {
				height = 1;
			}
		}
		int get_balance_factor() 
		{
			int l_h = left_child ? left_child->height : 0;
			int r_h = right_child ? right_child->height : 0;
			return r_h - l_h;
		}
	};
	node * root;
	int num_nodes;
	node * GetMinChild(node *_node) 
	{
		node *cur_node = _node;

		while (cur_node->left_child) {
			cur_node = cur_node->left_child;
		}
		return cur_node;
	}
	void RecursPrintTree(node *_node)
	{
		node *cur_node = _node;
		cout << cur_node->key << "(" << cur_node->height << "): ";
		if (cur_node->left_child) {
			cout << cur_node->left_child->key << "(l) ";
		}
		else {
			cout << "     ";
		}
		if (cur_node->right_child) {
			cout << cur_node->right_child->key << "(r) ";
		}
		cout << '\n';
		if (cur_node->left_child) {
			RecursPrintTree(cur_node->left_child);
		}
		if (cur_node->right_child) {
			RecursPrintTree(cur_node->right_child);
		}
	}
	void DeleteSimpleNode(node *del_node)
	{
		if (!del_node->right_child) {  
			if (del_node == root) {
				root = del_node->left_child;
				if (!root) {
					root = new node(0, nullptr);
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
		else if (!del_node->left_child) {  
			if (del_node == root) {
				root = del_node->right_child;
				if (!root) {
					root = new node(0, nullptr);
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
		node *cur_node = del_node->parent;
		delete del_node;
	}
	void ClearRecursion(node *start_clear_node) 
	{
		node *cur_clear_node = start_clear_node;
		if (cur_clear_node) {
			ClearRecursion(cur_clear_node->left_child);
			ClearRecursion(cur_clear_node->right_child);
			delete cur_clear_node;
		}
	}
public:
	AVL_tree()
	{
		root = new node(0, nullptr);
		num_nodes = 0;
	}
	~AVL_tree()
	{
		ClearRecursion(root);
	}
	void Insert_node(int ins_key)
	{
		if (!num_nodes)
		{
			root->key = ins_key;
			num_nodes++;
			return;
		}

		node *cur_node = root;
		while (true) {
			if (ins_key < cur_node->key) {
				if (cur_node->left_child) {
					cur_node = cur_node->left_child;
				}
				else {
					cur_node->left_child = new node(ins_key, cur_node);
					break;
				}
			}
			else {
				if (cur_node->right_child) {
					cur_node = cur_node->right_child;
				}
				else {
					cur_node->right_child = new node(ins_key, cur_node);
					break;
				}
			}
		}
		num_nodes++;
	}
	bool Delete_node(int del_key)  
	{
		node *del_node = SearchByKey(del_key);

		if (num_nodes && del_node) { 
			if (!del_node->left_child || !del_node->right_child) { 
				DeleteSimpleNode(del_node);
			}
			else {  
				node *successor_node = GetMinChild(del_node->right_child);
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
	node* SearchByKey(int seek_key)
	{
		node *cur_node = root;
		while (cur_node && cur_node->key != seek_key) {
			if (seek_key < cur_node->key) {
				cur_node = cur_node->left_child;
			}
			else {
				cur_node = cur_node->right_child;
			}
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
		if (num_nodes) {
			RecursPrintTree(root);
		}
		else {
			cout << "Äåðåâî ïóñòî.\n";
		}
	}
};

template <class T> class HashTable
{
private:
	TList<TRecord<T>> table[MaxSize];
	int Hash(int key)
	{
		return key % MaxSize;
	}
public:
	void Delete(int key_)
	{
		int tmp = Hash(key_);
		if (table[tmp].GetSize() == 0)
			throw("Free");
		for (int i = 0; i < table[tmp].GetSize(); i++)
			if (table[tmp][i].key == key_)
			{
				table[tmp].DeleteEl(i);
				return;
			}
	 	throw("File don't search");
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
	int count = 0;
	tab<T> GetTab()
	{
		return table;
	}
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
		{
			table[tmp].flag = false;
			count--;
		}
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
			count++;
		}
	}
	T Search(int key_)
	{
		tmp = Hash(key_);
		while (table[tmp].key != key_)
		{
			tmp++;
		}
		if (table[tmp].key == key_)
			return table[tmp].rec;
		else
			throw"key is not found";
	}
	friend ostream& operator<<(ostream &out, const Hash_Table &t)
	{
		int tmp = MaxSize;
		for (int i = MaxSize; i > 0; i--)
		{
			i -= tmp;
			out << i << "|" << t.Search(i) << "|";
			tmp--;
		}
		return out;
	}
};

#endif