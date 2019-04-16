#include <cstring>

const int MaxSize = 100;

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

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


template <class T> struct node
{
	int key;
	int height;
	T data;
	//node *parent;
	node *left_child;
	node *right_child;

	/*node(int _key, node *_parent, node *_left_child, node *_right_child)
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
	}*/

	~node() {}


	//int get_balance_factor() //возвращает балланс-фактор для данного узла (return balance-factor for this node)
	//{
	//	int lh = left_child ? left_child->height : 0;
	//	int rh = right_child ? right_child->height : 0;
	//	return (rh - lh);
	//}

	//int calc_height() //рассчитывает высоту узла (исходя из условия что высота потомков уже рассчитана) (calculating height of node (only if we know height of children))
	//{
	//	int lh = left_child ? left_child->height : 0;
	//	int rh = right_child ? right_child->height : 0;
	//	height = ((lh > rh) ? ln : rh) + 1;
	//	return height;
	//}
};

template <class T> class AVL_tree
{
private:
	node<T> *root;

	void makeEmpty(node* t)
	{
		if (t == NULL)
			return;
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	node* insert(int x, node* t)
	{
		if (t == NULL)
		{
			t = new node;
			t->data = x;
			t->height = 0;
			t->left = t->right = NULL;
		}
		else 
			if (x < t->data)
		{
			t->left = insert(x, t->left);
			if (height(t->left) - height(t->right) == 2)
			{
				if (x < t->left->data)
					t = singleRightRotate(t);
				else
					t = doubleRightRotate(t);
			}
		}
		else 
				if (x > t->data)
		{
			t->right = insert(x, t->right);
			if (height(t->right) - height(t->left) == 2)
			{
				if (x > t->right->data)
					t = singleLeftRotate(t);
				else
					t = doubleLeftRotate(t);
			}
		}

		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node* singleRightRotate(node* &t)
	{
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), t->height) + 1;
		return u;
	}

	node* singleLeftRotate(node* &t)
	{
		node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(t->right), t->height) + 1;
		return u;
	}

	node* doubleLeftRotate(node* &t)
	{
		t->right = singleRightRotate(t->right);
		return singleLeftRotate(t);
	}

	node* doubleRightRotate(node* &t)
	{
		t->left = singleLeftRotate(t->left);
		return singleRightRotate(t);
	}

	node* findMin(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	node* findMax(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}

	node* remove(int x, node* t)
	{
		node* temp;

		if (t == NULL)
			return NULL;
		// Element not found

		else if (x < t->data)
			t->left = remove(x, t->left);
		else if (x > t->data)
			t->right = remove(x, t->right);
		// Searching for element

		// Element found
		// With 2 children
		else if (t->left && t->right)
		{
			temp = findMin(t->right);
			t->data = temp->data;
			t->right = remove(t->data, t->right);
		}
		// With one or zero child
		else
		{
			temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			delete temp;
		}
		if (t == NULL)
			return t;

		t->height = max(height(t->left), height(t->right)) + 1;

		// If node is unbalanced
		// If left node is deleted, right case
		if (height(t->left) - height(t->right) == 2)
		{
			// right right case
			if (height(t->left->left) - height(t->left->right) == 1)
				return singleLeftRotate(t);
			// right left case
			else
				return doubleLeftRotate(t);
		}
		// If right node is deleted, left case
		else if (height(t->right) - height(t->left) == 2)
		{
			// left left case
			if (height(t->right->right) - height(t->right->left) == 1)
				return singleRightRotate(t);
			// left right case
			else
				return doubleRightRotate(t);
		}
		return t;
	}

	int height(node* t)
	{
		return (t == NULL ? -1 : t->height);
	}

	int getBalance(node* t)
	{
		if (t == NULL)
			return 0;
		else
			return height(t->left) - height(t->right);
	}

	void inorder(node* t)
	{
		if (t == NULL)
			return;
		inorder(t->left);
		cout << t->data << " ";
		inorder(t->right);
	}

public:
	AVL_tree()
	{
		root = NULL;
	}

	void insert(int x)
	{
		root = insert(x, root);
	}

	void remove(int x)
	{
		root = remove(x, root);
	}

	void display()
	{
		inorder(root);
		cout << endl;
	}

	//int num_nodes; //кол-во узлов в дереве (counts of nodes in tree)
	//	node *GetMinChild(node *_node)  //возвращает указатель на минимального потомка узла.
//	{
//		node *cur_node = _node;
//
//		while (cur_node->left_child) 
//		{
//			cur_node = cur_node->left_child;
//		}
//		return cur_node;
//	}
//
//	void RecursPrintTree(node *_node)
//	//{
//	//	if (_node != nullptr)
//	//	{
//	//		cout << "[" << _node->key << "]" << "\n";
//	//		cout << _node -> data << "\n";   // вывод хранимого полинома
//	//		RecursPrintTree(_node->left_child);
//	//		RecursPrintTree(_node->right_child);
//	//	}
//	//}
//
//	/*{
//		node *cur_node = _node;
//		cout << cur_node->key << "(" << cur_node->height << "): ";
//		if (cur_node->left_child)
//		{
//			cout << cur_node->left_child->key << "(l) ";
//		}
//		else
//		{
//			cout << "     ";
//		}
//		if (cur_node->right_child)
//		{
//			cout << cur_node->right_child->key << "(r) ";
//		}
//		cout << '\n';
//
//		if (cur_node->left_child)
//		{
//			RecursPrintTree(cur_node->left_child);
//		}
//		if (cur_node->right_child)
//		{
//			RecursPrintTree(cur_node->right_child);
//		}
//	}
//*/
//	void DeleteSimpleNode(node *del_node) //удаление узла, у которого не более одного дочернего узла (deleting node which dont have more than one child node)
//	{
//		if (!del_node->right_child) {  //если у узла del_node нет правого дочернего узла (if node "del_node" have no right child node) 
//			if (del_node == root)
//			{
//				root = del_node->left_child;
//				if (!root)
//				{
//					root = new node(0, nullptr);
//				}
//			}
//			else if (del_node == del_node->parent->left_child)
//			{
//				del_node->parent->left_child = del_node->left_child;
//			}
//			else if (del_node == del_node->parent->right_child)
//			{
//				del_node->parent->right_child = del_node->left_child;
//			}
//
//			if (del_node->left_child)
//			{
//				del_node->left_child->parent = del_node->parent;
//			}
//		}
//		else if (!del_node->left_child) {  //если у узла del_node нет левого дочернего узла (if node "del_node" have no left child node)
//			if (del_node == root)
//			{
//				root = del_node->right_child;
//				if (!root)
//				{
//					root = new node(0, nullptr);
//				}
//			}
//			else if (del_node == del_node->parent->left_child)
//			{
//				del_node->parent->left_child = del_node->right_child;
//			}
//			else if (del_node == del_node->parent->right_child)
//			{
//				del_node->parent->right_child = del_node->right_child;
//			}
//
//			if (del_node->right_child)
//			{
//				del_node->right_child->parent = del_node->parent;
//			}
//		}
//		node *cur_node = del_node->parent;
//		delete del_node;
//
//		while (cur_node)
//		{  //баллансируем. (balancing)
//			cur_node.calc_height();
//			Balance(cur_node);
//			cur_node = cur_node->parent;
//		}
//	}
//	void ClearRecursion(node *start_clear_node) //вызывается деструктором. (called by destructor)
//	{
//		node *cur_clear_node = start_clear_node;
//		if (cur_clear_node)
//		{
//			ClearRecursion(cur_clear_node->left_child);
//			ClearRecursion(cur_clear_node->right_child);
//			delete cur_clear_node;
//		}
//	}
//
//	void Rotate(node *rotate_node, bool left)  // поворот влево или вправо (rotate left/right)
//	{
//		node* tmp;
//		if (left)
//		{
//			tmp = rotate_node->right_child;
//			rotate_node->right_child = tmp->left_child;
//			tmp->left_child = rotate_node;
//		}
//		else
//		{
//			tmp = rotate_node->left_child;
//			rotate_node->left = tmp->right_child;
//			tmp->right_child = rotate_node;
//		}
//
//		rotate_node.calc_height();
//		tmp.calc_height();
//		return tmp;
//	}
//	void Balance(node *b_node) //балансировка узла (balancing of node)
//	{
//		if (b_node.get_balance_factor() == -2)
//		{
//			if (b_node->left_child.get_balance_factor() < 0)
//			{
//				Rotate(b_node->left_child, true);
//			}
//			else if (b_node->left_child.get_balance_factor() > 0)
//			{
//				Rotate(b_node->left_child, false);
//			}
//			Rotate(b_node, true);
//		}
//		else if (b_node.get_balance_factor() == 2)
//		{
//			if (b_node->right_child.get_balance_factor() < 0)
//			{
//				Rotate(b_node->right_child, true);
//			}
//			else if (b_node->right_child.get_balance_factor() > 0)
//			{
//				Rotate(b_node->right_child, false);
//			}
//			Rotate(b_node, false);
//		}
//	}
//
//public:
//	AVL_tree()
//	{
//		root = new node(0, nullptr);
//		num_nodes = 0;
//	}
//	~AVL_tree()
//	{
//		ClearRecursion(root);
//	}
//	void Insert_node(int ins_key, T _data)
//	{
//		if (!num_nodes)
//		{
//			root->key = ins_key;
//			root->data = _data;
//			num_nodes++;
//			return;
//		}
//
//		node<T> *cur_node = root;
//		while (true)
//		{
//			if (ins_key < cur_node->key)
//			{
//				if (cur_node->left_child != nullptr)
//				{
//					cur_node = cur_node->left_child;
//				}
//				else
//				{
//					cur_node->left_child = new node(ins_key, cur_node);
//					cur_node->left_child->data = _data;
//					break;
//				}
//			}
//			else
//			{
//				if (cur_node->right_child != nullptr)
//				{
//					cur_node = cur_node->right_child;
//				}
//				else
//				{
//					cur_node->right_child = new node(ins_key, cur_node);
//					cur_node->right_child->data = _data;
//					break;
//				}
//			}
//		}
//		num_nodes++;
//
//		while (cur_node)
//		{ //баллансируем. (balancing)
//			cur_node.calc_height();
//			Balance(cur_node);
//			cur_node = cur_node->parent;
//		}
//	}
//	bool Delete_node(int del_key)  //дерево баллансируется в функции DeleteSimpleNode. (tree is balanced in function "...")
//	{
//		node *del_node = SearchByKey(del_key);
//
//		if (num_nodes && del_node) { //если такой узел присутствует в дереве. (if such node assist in tree)
//			if (!del_node->left_child || !del_node->right_child) { //если у узла del_node не более одного дочерних узла. (if node "del_node" dont have more than one child node)
//				DeleteSimpleNode(del_node);
//			}
//			else {   //если у узла del_node два дочерних узла. (if node "del_node" two child node)
//				node *successor_node = GetMinChild(del_node->right_child);
//				/*del_node = successor_node;*/
//				del_node->key = successor_node->key;
//
//				DeleteSimpleNode(successor_node);
//			}
//			num_nodes--;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	node* SearchByKey(int seek_key)
//	{
//		node *cur_node = root;
//		while (cur_node && cur_node->key != seek_key)
//		{
//			if (seek_key < cur_node->key)
//				cur_node = cur_node->left_child;
//			else
//				cur_node = cur_node->right_child;
//
//		}
//		return cur_node;
//	}
//	void Clear_tree()
//	{
//		ClearRecursion(root->left_child);
//		ClearRecursion(root->right_child);
//		num_nodes = 0;
//		root->left_child = nullptr;
//		root->right_child = nullptr;
//		root->height = 1;
//	}
//
//	void Print_tree()
//	{
//		if (num_nodes)
//		{
//			RecursPrintTree(root);
//		}
//		else
//		{
//			cout << "Дерево пусто.\n";
//		}
//	}
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



