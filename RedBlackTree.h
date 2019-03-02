#include <iostream>

using namespace std;

#define RED  0
#define BLACK 1

template <class T>
class RedBlackTreeNode
{
public:
	T data;
	RedBlackTreeNode* leftchild;
	RedBlackTreeNode* rightchild;
	RedBlackTreeNode* parent;
	int color;

	RedBlackTreeNode(){};
	RedBlackTreeNode(T d)
	{
		data = d;
		leftchild = NULL;
		rightchild = NULL;
		parent = NULL;
		color = BLACK;

	};	
};


template <class T>
class RedBlackTree
{
private:
	RedBlackTreeNode<T> *m_root;       //根节点
	RedBlackTreeNode<T> *m_Null;       //叶子节点，无任何意义。仅表示叶子

	
	void InsertFixedUp(RedBlackTreeNode<T> *&pNode);  
	void DeleteFixdUp(RedBlackTreeNode<T> *&pNode);
	void RotateLeft(RedBlackTreeNode<T> *&pNode);  
	void RotateRight(RedBlackTreeNode<T> *&pNode); 
	void PrintTree(RedBlackTreeNode<T> * pNode);
public:
	RedBlackTree()
	{
		m_root = NULL;
		m_root =  NULL;
	}


	void Insert(T x);
	void EmptyTree(RedBlackTreeNode<T> *root);
	void Delete(T x);
	RedBlackTreeNode<T>* Find(T key); 
	void PrintTree();

};

template <class T>
void RedBlackTree<T>::EmptyTree(RedBlackTreeNode<T> *root)
{
	if(root->leftchild == NULL &&  root->rightchild == NULL)
	{
		root = NULL;
		return;
	}
	else
	{
		if(root->leftchild!=NULL)
			EmptyTree(root->leftchild);
		if(root->rightchild!=NULL)
			EmptyTree(root->rightchild);
	}	
}

template <class T>
void RedBlackTree<T>::Insert(T x)
{
	RedBlackTreeNode<T>* parent = m_Null;
	RedBlackTreeNode<T>* index = m_root;
	if(index == NULL)
	{
		RedBlackTreeNode<T>* p = new RedBlackTreeNode<T>(x);
		m_root = p;
		m_root->color = BLACK;
		return;
	}
	
	while(index !=NULL)
	{
		parent = index;			
		if(x < index->data)
			index = index->leftchild;
		else
			index = index->rightchild;
	}
	RedBlackTreeNode<T>* p = new RedBlackTreeNode<T>(x);
	if(m_root == NULL)
	{		
		m_root = p;
	}
	else
	{
		p->parent = parent;

		if(parent->data > x)
			parent->leftchild = p;
		else
			parent->rightchild = p;
	}
	p->color = RED;
	InsertFixedUp(p);	
}

template <class T>
void RedBlackTree<T>::InsertFixedUp(RedBlackTreeNode<T> *&pNode)
{
	while(pNode->parent->color == RED)
	{
		if(pNode->parent!=NULL && pNode->parent->parent!= NULL)
		{
			if((pNode->parent == pNode->parent->parent->leftchild)  )
			{
				RedBlackTreeNode<T> *p = new RedBlackTreeNode<T>;
				if(pNode->parent->parent->rightchild == NULL)
				{
					p->color = BLACK;
				}
				else
					p = pNode->parent->parent->rightchild;           //uncle

				if(p->color == RED)                                          //uncle = Read case 1
				{
					pNode->parent->color = BLACK;
					pNode->parent->parent->color = RED;
					pNode->parent->parent->rightchild->color = BLACK;
					pNode = pNode->parent->parent;
				}
				else               //case 2: unlce = Black 节点在右子树上
				{
					if(pNode == pNode->parent->rightchild)
					{
						pNode = pNode->parent;

						RotateLeft(pNode);
					}				
					pNode->parent->color = BLACK;
					pNode->parent->parent->color = RED;
					RotateRight(pNode->parent->parent);                  //case3:
				}

			}
			else if((pNode->parent == pNode->parent->parent->rightchild))    //添加的点在右子树上
			{
				RedBlackTreeNode<T> *p = new RedBlackTreeNode<T>;
				if(pNode->parent->parent->leftchild == NULL)
				{
					p->color = BLACK;
				}
				else
					p = pNode->parent->parent->leftchild;           //uncle

				if(p->color == RED)                                          //uncle = Read case 1
				{
					pNode->parent->color = BLACK;
					pNode->parent->parent->color = RED;
					pNode->parent->parent->leftchild->color = BLACK;
					pNode = pNode->parent->parent;
				}
				else                                                      //case 2: unlce = Black 节点在右子树上
				{
					if(pNode == pNode->parent->rightchild)
					{
						pNode = pNode->parent;

						RotateRight(pNode);
					}				
					pNode->parent->color = BLACK;
					pNode->parent->parent->color = RED;
					RotateLeft(pNode->parent->parent);                  //case3:
				}

			}
		}
		m_root->color = BLACK;
	}	
}

template <class T>
void RedBlackTree<T>::RotateLeft(RedBlackTreeNode<T> *&pNode)
{
	if(pNode == NULL || pNode->rightchild == NULL)
		return;
	RedBlackTreeNode<T> *p = pNode->rightchild;
	pNode->rightchild = p->leftchild;
	if(p->leftchild != NULL)
	{
		p->leftchild->parent = pNode;
		p->parent = pNode->parent;
	}
	pNode->parent->leftchild = p;
	//pNode->parent = p->parent;
	p->parent = pNode->parent;
	p->leftchild = pNode;
	pNode->parent = p;

}

template <class T>
void RedBlackTree<T>::RotateRight(RedBlackTreeNode<T> *&pNode)
{
	if(pNode == NULL || pNode->leftchild == NULL)
		return;
	RedBlackTreeNode<T> *p = pNode->leftchild;
	pNode->leftchild = p->rightchild;
	if(p->rightchild != NULL)
	{
		p->rightchild->parent = pNode;
		p->parent = pNode->parent;
	}
	if(pNode->parent == NULL)                    //pNode为根节点
	{
		p->rightchild = pNode;
		pNode->parent = p;
		m_root = p;
		return;
	}
	p->parent = pNode->parent;
	p->rightchild = pNode;
	pNode->parent = p;
}

template<class T>
RedBlackTreeNode<T>* RedBlackTree<T>::Find(T key)
{
	RedBlackTreeNode<T>* p = m_root;
	while(p!=NULL)
	{
		if(key < p->data)
			p = p->leftchild;
		else if(key > p->data)
			p = p->rightchild;
		else if(key == p->data)
			return p;	
	}
	return NULL;
}

template <class T>
void RedBlackTree<T>::Delete(T x)
{
	if(m_root == NULL)
		return;
	else
	{
		RedBlackTreeNode<T> *p = Find(x);
		RedBlackTreeNode<T> *child;
		while(p != NULL)
		{		
			if(p->leftchild == NULL && p->rightchild == NULL)     //leaf
			{
				if(p->color == RED)
				{
					delete p;
					return;
				}
				delete p;
			}
			else if(p->leftchild && p->rightchild)              
			{
				child = p->leftchild;
				while(child->rightchild)
					child = child->rightchild;
				T tmp = p->data;
				p->data = child->data;
				child->data = tmp;
				
				p = child;
				delete p ;
				return;
			}
			else
			{
				if(p->leftchild)
					child = p->leftchild;
				else
					child = p->rightchild;
					
				if(child->parent == NULL)
					m_root = child;
				else
				{
					child->parent = p->parent;
						
					if(child->parent->leftchild)
						child->parent->leftchild = child;
					else
						child->parent->rightchild = child;

					if(p->color == RED)
					{
						delete p;
						return;
					}
					delete p;

					DeleteFixdUp(child);	
				}

			}
		}
	
	}
}

template <class T>
void RedBlackTree<T>::DeleteFixdUp(RedBlackTreeNode<T> *&pNode)
{
	while(pNode!=m_root && pNode->color == BLACK)
	{
		if(pNode == pNode->parent->leftchild)                       //左子树上
		{
			RedBlackTreeNode<T> *brother = pNode->parent->rightchild;
			
			if(brother->color == RED)                                 //case1
			{
				brother->color = BLACK;
				pNode->parent = RED;
				RotateLeft(pNode->parent);
			}
			else
			{
				if(brother->leftchild->color == BLACK && brother->rightchild->color == BLACK) //case2 brother=Black,brother->left = brother->right= Black
				{
					brother->color = RED;
					pNode = pNode->parent;
				}
				else
				{
					if(brother->rightchild->color == BLACK)                      //case 3 brother = Black,brother->left = Red;brother->right = black
					{
						brother->leftchild->color = BLACK;
						brother->color = RED;

						RotateRight(brother);
						brother = pNode->parent->rightchild;
					}
					brother->color = pNode->parent->color;
					pNode->parent->color = BLACK;
					brother->rightchild->color= BLACK;
					RotateLeft(pNode->parent);

					pNode = m_root;
				}
			}
			
		}
		else if(pNode == pNode->parent->rightchild)                   //在右子树上
		{
			RedBlackTreeNode<T> *brother = pNode->parent->leftchild;

			if(brother->color == RED)                                 //case1
			{
				brother->color = BLACK;
				pNode->parent = RED;
				RotateRight(pNode->parent);
			}
			else
			{
				if(brother->leftchild->color == BLACK && brother->rightchild->color == BLACK) //case2 brother=Black,brother->left = brother->right= Black
				{
					brother->color = RED;
					pNode = pNode->parent;
				}
				else
				{
					if(brother->leftchild->color == BLACK)                      //case 3 brother = Black,brother->left = Red;brother->right = black
					{
						brother->rightchild->color = BLACK;
						brother->color = RED;

						RotateLeft(brother);
						brother = pNode->parent->leftchild;
					}
					brother->color = pNode->parent->color;
					pNode->parent->color = BLACK;
					brother->leftchild->color= BLACK;
					RotateRight(pNode->parent);

					pNode = m_root;
				}
			}
		}
	}
	pNode->color = BLACK;
};

template <class T>
void RedBlackTree<T>::PrintTree()
{
	PrintTree(m_root);
}

template<class T>
void RedBlackTree<T>::PrintTree(RedBlackTreeNode<T> * pNode)
{
	if(pNode)
	{
		cout<<pNode->data<<"  ";
		PrintTree(pNode->leftchild);
		PrintTree(pNode->rightchild);
	}
}