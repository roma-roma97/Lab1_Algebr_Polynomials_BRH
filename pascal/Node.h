#include"stack.h"

template<class T> class node
{
	node<T>* pNext;
	node<T>* pPrev;
	node<T>* pDown;
	node<T>* pUp;
	int level;
	node() :pNext(nullptr), pPrev(nullptr), pDown(nullptr), pUp(nullptr), level(0) {};
	void Clear(node<T>* pFirst)
	{
		node<T>* cur = pFirst;
		node<T>* tmp;
		TStack<node<T>*> st;
		if (pFirst == nullptr)
			return;
		while (cur->pDown != nullptr || cur->pNext != nullptr)
		{
			if (cur->pDown != nullptr)
			{
				st.Push(cur);
				cur = cur->pDown;
			}
			else
			{
				st.Push(cur);
				cur = cur->pNext;;
			}
		}
	}
};


