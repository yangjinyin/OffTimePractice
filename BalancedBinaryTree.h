#include <iostream>
#include <stack>
using namespace std;


template<class T>
class TreeNode
{
public:
	TreeNode(){}
	TreeNode(T d){data = d; rightchild = NULL,leftchild = NULL;freg = 1;}
	T data;//值
	int hgt;             //以此节点为根的树的高度；叶子为0；空树为-1；
	int freg;             // 频率；
	
	TreeNode* rightchild;     //指向左儿子的地址
	TreeNode* leftchild;    //指向右儿子的地址
};
//平衡二叉树又称AVL数
template<class T>
class BlancedBinaryTree
{
private:
	
	void insert(TreeNode<T>* &node,T x);//插入
	TreeNode<T>* find(TreeNode<T>* node,T x);//查找
	void printTreeMid(TreeNode<T>* node);//中序遍历
	void Delete(TreeNode<T>* &node,T x);//删除
	int height(TreeNode<T>* node);//求树的高度
	void SingRotateLeft(TreeNode<T>* &k2);//左左情况下的旋转
	void SingRotateRight(TreeNode<T>* &k2);//右右情况下的旋转
	void DoubleRotateLR(TreeNode<T>* &k3);//左右情况下的旋转
	void DoubleRotateRL(TreeNode<T>* &k3);//右左情况下的旋转
	

public:
	TreeNode<T>* root;//根节点
	BlancedBinaryTree(){root = NULL;}
	void insert(T x);//插入接口
	TreeNode<T>* find(T x);//查找接口
	void Delete(T x);//删除接口
	void printTree();//遍历接口
	
	
};
template<class T>
bool isBalanced(TreeNode<T>* root,int *depth)
{
	if(root == NULL)
	{
		*depth = 0;
		return true;
	}
	int left ;
	int right ;
	if(isBalanced(root->leftchild,&left)&&isBalanced(root->rightchild,&right))
	{
		int diff = left - right;
		if(diff<=1 && diff>=-1)
		{
			*depth = 1+(left>right?left:right);
			return true;
		}
	}
	return false;
}
template<class T>

int BlancedBinaryTree<T>::height(TreeNode<T>* node)
{
	if (node!=NULL)
	{
		return node->hgt;
	}
	else
		return -1;
}
template <class T>

void BlancedBinaryTree<T>::insert(T x)
{
	insert(root,x);
}
template <class T>

void BlancedBinaryTree<T>::insert(TreeNode<T>* &node,T x)
{
	if (node == NULL)
	{
		TreeNode<T> *p = new TreeNode<T>(x);
		if(p == NULL)
			return;
		else
		{
			node = p;
			node->hgt = 0;
		}

	}
	else
	{
		if(x<node->data)
		{
			insert(node->leftchild,x);
			if((height(node->leftchild)-height(node->rightchild)) == 2)
			{
				if(x<node->leftchild->data)
					SingRotateLeft(node);               //LL rotate
				else
					DoubleRotateLR(node);               //LR rotate
			}
		}
		else if(x>node->data)
		{
			insert(node->rightchild,x);
			if((height(node->rightchild)-height(node->leftchild)) == 2)
			{
				if(x>node->rightchild->data)
					SingRotateRight(node);               //RR rotate
				else
					DoubleRotateRL(node);               //RL rotate
			}
			
		}
		else
			node->freg++;
		node->hgt=max(height(node->leftchild),height(node->rightchild))+1;
	}
}
template<class T>
void BlancedBinaryTree<T>::SingRotateLeft(TreeNode<T>* &k2)
{
	TreeNode<T>* k1;
	TreeNode<T>* tmp;
	tmp = k2;
	k1 = k2->leftchild;

	k2->leftchild = k1->rightchild;
	k1->rightchild = k2;
	k2 = k1;
	k1 = tmp;

	k1->hgt=max(height(k1->leftchild),height(k1->rightchild))+1;
	k2->hgt=max(height(k2->leftchild),height(k2->rightchild))+1;
	
}

template <class T>
void BlancedBinaryTree<T>::SingRotateRight(TreeNode<T>* &k2)
{
	TreeNode<T>* k1;
	TreeNode<T>* tmp;
	tmp = k2;
	k1 = k2->rightchild;
	k2->rightchild = k1->leftchild;
	k1->leftchild = k2;
	k2 = k1;
	k1 = tmp;

	k1->hgt=max(height(k1->leftchild),height(k1->rightchild))+1;
	k2->hgt=max(height(k2->leftchild),height(k2->rightchild))+1;
}
template<class T>
void BlancedBinaryTree<T>::DoubleRotateLR(TreeNode<T>* &k3)
{
	SingRotateRight(k3->leftchild);
	SingRotateLeft(k3);
}

template<class T>
void BlancedBinaryTree<T>::DoubleRotateRL(TreeNode<T>* &k3)
{
	SingRotateLeft(k3->rightchild);
	SingRotateRight(k3);
}
template<class T>
TreeNode<T>* BlancedBinaryTree<T>::find(T x)
{
	find(root,x);
}

template<class T>
TreeNode<T>* BlancedBinaryTree<T>::find(TreeNode<T>* node,T x)
{
	if(node ==NULL)
	{
		return;
	}
	else
	{
		if(x>node->data)
			return find(node->rightchild,x);
		else if(x<node->data)
			return find(node->leftchild,x);
		else
			return node;

	}

}
template<class T>
void BlancedBinaryTree<T>::Delete(T x)
{
	Delete(root,x);
}

template<class T>
void BlancedBinaryTree<T>::Delete(TreeNode<T>* &node,T x)
{
	if(node == NULL)
		return;
	else
	{
		if(x<node->data)
		{
			Delete(node->leftchild,x);

			if(height(node->rightchild)-height(node->leftchild)== 2)
			{
				if(node->rightchild->rightchild != NULL && (height(node->rightchild->leftchild)>height(node->rightchild->rightchild)))
					DoubleRotateRL(node);
				else
					SingRotateRight(node);
			}
		}

		else if(x>node->data)
		{
			Delete(node->rightchild,x);

			if(height(node->leftchild)-height(node->rightchild)== 2)
			{
				if(node->leftchild->leftchild != NULL && (height(node->leftchild->rightchild)>height(node->leftchild->leftchild)))
					DoubleRotateLR(node);
				else
					SingRotateLeft(node);
			}
		}
		else
		{
			if(node->leftchild && node->rightchild)               //左右不为空
			{
				TreeNode<T>* tmp = node->rightchild;
				while(tmp->leftchild)
					tmp = tmp->leftchild;
				node->hgt = tmp->hgt;
				node->data = tmp->data;
				Delete(node->rightchild,tmp->data);

				if((height(node->leftchild) - height(node->rightchild)) == 2)
				{
					if(node->leftchild->rightchild!=NULL&& (height(node->leftchild->rightchild)>height(node->leftchild->leftchild) ))
						DoubleRotateLR(node);
					else
						SingRotateLeft(node);
				}
			}

			else                //一个或者0个孩子
			{
				TreeNode<T> *tmp = node;
				if(node->rightchild == NULL)
					node = tmp->leftchild;
				else if(node->leftchild == NULL)
					node = tmp->rightchild;
				delete(tmp);
			}
		}

	}

	if(node == NULL)
		return;
	 node->hgt=max(height(node->leftchild),height(node->rightchild))+1;

	 return;
}

template<class T>
void BlancedBinaryTree<T>::printTree()
{
	printTreeMid(root);
}

template<class T>
void BlancedBinaryTree<T>::printTreeMid(TreeNode<T>*root)
{
	if(root == NULL)
		return;
	else
	{
		if(root->leftchild)
			printTreeMid(root->leftchild);
		cout<<root->data<<"  ";
		if(root->rightchild)
			printTreeMid(root->rightchild);
	}
}