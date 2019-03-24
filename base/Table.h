#include <cstring>

const int MaxSize = 100;

#include <iostream>
#include <iomanip>

using namespace std;

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
	void calc_height() //рассчитывает высоту узла (исходя из условия что высота потомков уже рассчитана).
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
	int get_balance_factor() //возвращает балланс-фактор для данного узла.
	{
		int l_h = left_child ? left_child->height : 0;
		int r_h = right_child ? right_child->height : 0;
		return r_h - l_h;
	} 
};

class AVL_tree {
private:
	node * root;
	int num_nodes; //кол-во узлов в дереве.
	node * GetMinChild(node *_node) //возвращает указатель на минимального потомка узла.
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
	void DeleteSimpleNode(node *del_node) //удаление узла, у которого не более одного дочернего узла.
	{
		if (!del_node->right_child) {  //если у узла del_node нет правого дочернего узла.
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
		else if (!del_node->left_child) {  //если у узла del_node нет левого дочернего узла.
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
	void ClearRecursion(node *start_clear_node) //вызывается деструктором.
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
	bool Delete_node(int del_key)  //дерево баллансируется в функции DeleteSimpleNode(...).
	{
		node *del_node = SearchByKey(del_key);

		if (num_nodes && del_node) { //если такой узел присутствует в дереве.
			if (!del_node->left_child || !del_node->right_child) { //если у узла del_node не более одного дочерних узла.
				DeleteSimpleNode(del_node);
			}
			else {   //если у узла del_node два дочерних узла.
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
			cout << "Дерево пусто.\n";
		}
	}
};

//
//template <class T> class TableTree
//{
//	//Cell<T, string>data[MaxSize];
//public:
//	void Insert(T _data, string _key);
//	void Delete(string _key);
//	T Search(string _key);
//};
//

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



