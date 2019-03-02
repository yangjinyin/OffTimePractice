#include <iostream>
#define  M  4
//外查找树，它是一种平衡的多叉树，称为B树（或B-树、B_树）
namespace BTree
{

	template <class T>
	class TreeNode
	{
		int n;                          //指示该结点的关键字个数  
		T *keys;                      //该结点关键字数组(n)             [m-1,2m-1]  
		bool isLeaf;                    //该结点是否是叶子结点  
		TreeNode<T>  **child ;          //该结点的所有孩子结点 (n+1)         [m,2m];

		TreeNode<T>* AllocateNode()
		{ 
			TreeNode<T> *p = new TreeNode<T>;
			p->isLeaf = true;
			p->n = 0;
			p->keys = new T(2*M-1);
			p->child = new TreeNode<T>[2*M];
			for(int i = 0; i < 2*T;i++)
				p->child[i] = NULL;
			return p;

		}
	};

	template <class T>
	class BTree
	{
	private:
		TreeNode *root;
		TreeNode<T>* Search(TreeNode<T> *root,T x ,int &index);
		void BTreeInsertNonfull(TreeNode<T>*& p,T x);
		bool BTreeDeleteInNode(TreeNode<T>*& deleteNode, T x,int index);       
		bool BTreeDeleteInParentNode(TreeNode<T>*& parentNode, T x,int indexparent);
		void PrintTree(TreeNode<T>* root);
	public:
		bool Search(T x);
		void SplitChild(TreeNode<T> *&splitNode, TreeNode<T>* &parent,int indexchild);
		void BTreeInsert(T x);
		void BTreeDelete(T x);
		void PrintTree();
	};


	template <class T>
	bool BTree<T>::Search(T x)
	{
		int index;
		return Search(root,x,index);
	}

	//index 索引
	template <class T>
	TreeNode<T>* BTree::Search(TreeNode<T> *root,T x ,int &index)
	{
		int i = 0;
		while(i < root->n && x > root->keys[i])
		{
			i++;
		}
		if(i < root->n && x == root->keys[i])
		{
			index = i;
			return root->keys[i];
		}
		if(root->isLeaf)
			return NULL;
		Search(root->child[i],x,index);
	}

	//indexchild 是待分裂节点在父亲节点的编号索引
	template <class T>
	void BTree<T>::SplitChild(TreeNode<T> *&splitNode, TreeNode<T>* &parent,int indexchild)
	{
		TreeNode<T> *p = AllocateNode();

		p->isLeaf = splitNode->isLeaf;
		p->n = M-1;

		for(int j = 0;j < p->n;j++)
			p->keys[j] = splitNode->keys[j+M];  //将splitNode的后一半赋值给p；
		
		if(splitNode->isLeaf)
		{
			for(int j = 0; j < M; j++)
				p->child[j] = splitNode->child[M+j];
		}

		splitNode->n = M-1;

		for (int j = parent->n;j>indexchild+1;j--)
		{
			parent->child[j+1] = parent->child[j];
		}

		parent->child[j] = p;

		for(int j = parent->n-1;j>indexchild;j--)
			parent->keys[j+1] = parent->keys[j];
		parent->keys[j+1] = p->keys[j];
		
		++parent->n;  
	}

	//把x插入p节点中且该节点不满
	template <class T>
	void BTree<T>::BTreeInsertNonfull(TreeNode<T>*& p,T x)
	{
		int i = p->n - 1;
		
		if(p->isLeaf)
		{
			while (i>=0 && x < p->keys[i])
			{
				p->keys[i+1] = p->keys[i];
				i = i - 1;
			}
			p->keys[i+1] = k;
			++p->n;
			
		}
		else
		{
			while(i>=0 && k < p->keys[i])
				i--;
			i++;

			if(p->child[i]->n == 2*M-1)
			{
				SplitChild(p->child[i],p,i);

				if(x > p->keys[i])
					i++;

				BTreeInsertNonfull(p->child[i],x);
			}
		}
	}

	template <class T>
	void BTree<T>::BTreeInsert(T x)
	{
		TreeNode<T> *p = root;
		if(root->n == 2*M-1)
		{
			TreeNode<T>* newRoot = AllocateNode();
			root = newRoot;
			newRoot->isLeaf = false;
			newRoot->n = 0;
			newRoot->child[0] = p;
			SplitChild(newRoot->child,newRoot,0);
			BTreeInsertNonfull(newRoot,x);
		}
		else
		{
			BTreeInsertNonfull(p,x);
		}
	}

	template <class T>
	void BTree<T>::BTreeDelete(T x)
	{
		TreeNode<T>* p_root = root;
	
		//找到该点所在的节点
		TreeNode<T>* parent = p_root;
		int num = 0;
		int i = 0;
		while(x > p_root->keys[i] && i < p_root->n)
		{
			i++;
		}
		if(i < p_root->n && x == root->keys[i])
		{
			BTreeDelete(p_root,x,i);            //待删除的数在根节点
			return;
		}
		p_root = p_root->child[i];

		int index = 0;
		while(p_root)
		{
			int i = 0;


			while(x > p_root->keys[i] && i < p_root->n)
			{
				i++;
			}
			if(i < p_root->n && x == root->keys[i])
			{
				BTreeDeleteInParentNode(parent,x,index);    //待删除的在非根节点上
				return;
			}
			parent = p_root;
			p_root = p_root->child[i];
			index = i;
		}

	}

	//待删除的在节点上；
	template <class T>
	bool BTree<T>::BTreeDeleteInNode(TreeNode<T>*& deleteNode, T x,int index)   
	{
		if(deleteNode->isLeaf)                                        //待删除的在叶节点上；
		{
			for(int i = index;i+1<deleteNode->n;i++)
				deleteNode[i] = deleteNode[i+1];
			--deleteNode->n;

			return;
		}
		else                                                         //在内节点上；        
		{
			if(deleteNode->child[index]->n>=M)                       //它的前驱子树至少有M个关键字；找到前驱并且替换他.然后递归删除
			{
				swap(deleteNode->keys[index],deleteNode->child[index]->key[deleteNode->child[index]->n]);
				BTreeDeleteInNode(deleteNode->child[index],x,deleteNode->child[index]->n);
			}
			else 
			{
				if(deleteNode->child[index+1]->n>=M)                 //它的后驱子树至少有M个关键字；找到第一个后驱并且替换他.然后递归删除      
				{
					swap(deleteNode->keys[index],deleteNode->child[index+1]->key[0]);
					BTreeDeleteInNode(deleteNode->child[index+1],x,0);
				}
				else                                          //前后子树都是M-1个，然后合并前后子树以及x到前子树中，删除deleteNode中x以及指向后子树的指针.然后递归删除x
				{
					
					deleteNode->child[index]->key[M-1] = x;
					for(int i = 0;i<M-1;i++)
					{
						deleteNode->child[index]->key[M+i] = deleteNode->child[index+1]->key[i];
						deleteNode->child[index]->n = 2*M-1;
					}	
					for(int i = index;i+1<deleteNode->n;i++)
						deleteNode[i] = deleteNode[i+1];
					--deleteNode->n;

					for(int i = index+1;i < deleteNode->n+1;i++)
						deleteNode->child[i] = deleteNode->child[i+1];

					BTreeDeleteInNode(deleteNode->child[index+1],x,M-1);
				}

			}
		}
	}

	//待删除的在孩子节点上
	template <class T>
	bool BTree<T>::BTreeDeleteInParentNode(TreeNode<T>*& parentNode, T x,int indexparent)
	{
		int i = 0;
		while(i<parentNode->child[indexparent]->n && x != parentNode->child[indexparent]->key[i])
			i++;
		if(parentNode->child[indexparent]->n>=M)
		{			
			BTreeDeleteInNode(parentNode->child[indexparent],x,i);
		}
		else
		{
			if(indexparent-1>=0 && parentNode->child[indexparent+1]->n>= M)        //case3.a
			{
				parentNode->child[indexparent]->key[M-1] = parentNode->keys[indexparent-1];
				parentNode->child[indexparent]->n += 1;

				parentNode->keys[indexparent-1] = parentNode->child[indexparent-1]->key[ (parentNode->child[indexparent-1]->n)-1];

				parentNode->child[indexparent+1]->n -=1;

				BTreeDeleteInNode(parentNode->child[indexparent],x,i);
			}
			else
			{
				if(indexparent+1<parentNode->n && parentNode->child[indexparent+1]->n>= M) //case 3.a
				{
					parentNode->child[indexparent]->key[M-1] = parentNode->keys[indexparent];
					parentNode->child[indexparent]->n += 1;

					parentNode->keys[indexparent] = parentNode->child[indexparent+1]->key[0];

					for(int i = 0;i+1 < parentNode->child[indexparent+1]->n;i++)
						parentNode->child[indexparent+1]->key[i] = parentNode->child[indexparent+1]->key[i+1];
					parentNode->child[indexparent+1]->n -=1;

					BTreeDeleteInNode(parentNode->child[indexparent],x,i);
				}
			}
		}
	}

	template <class T>
	void BTree<T>::PrintTree()
	{
		PrintTree(root);
	}


	template<class T>
	void BTree<T>::PrintTree(TreeNode<T>* root)
	{
		if(NULL == root)  
			return;  

		//输出当前节点所有关键字  
		cout << "[";  
		for(int i = 0;i < root->n;++i)  
		{  
			cout << root->keys[i];  
			if(t->n - 1 != i)  
				cout << " ";  
		}  
		cout << "]" << endl;  

		//递归输出所有子树  
		for(int i = 0;i <= t->n;++i)  
			PrintTree(root->child[i]);  
	}
}

