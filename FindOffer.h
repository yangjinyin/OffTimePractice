#include <iostream>
#include <string>

using namespace std;
#define isON(n, i) ((n) & 1 << (i))  

//赋值运算符重载
class A
{
public:
	A(char* pData = NULL);
	bool operator==(const A &a)
	{
		return (this->m_pData == a.m_pData);
	}
	A& operator=(const A &a);
private:
	char* m_pData;
};
A& A::operator=(const A& a)
{
	if(this == &a)
		return *this;
	char *p = new char[strlen(a.m_pData)+1];
	strcpy(p,a.m_pData);
	delete m_pData;
	m_pData = p;

}

//二维数组查找；
bool FindNum(int **A,int x,int y,int num)
{
	if(A == NULL)
		return false;
	if(x<=0 || y<=0)
		return false;

	int j = 0;
	int i = x-1;
	while(j < y && i>=0)
	{
		if(num>A[j][i])
			j++;
		else if(num < A[j][i])
		{
			i--;
		}
		else
			return true;
	}
	return false;
}

//根据前序，中序重构原树
struct BinaryTreeNode
{
	int						m_nValue;
	BinaryTreeNode*			m_pLeft;
	BinaryTreeNode*			m_pRight;
};
BinaryTreeNode* Construct(int *startpre,int *endpre,int *startinorder,int *endinorder)
{
	int rootValue = startpre[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = NULL;
	root->m_pRight = NULL;

	if(startpre == endpre)
	{
		if(startinorder == endinorder)
			return root;
		else
			exception("Invalid Input.");
	}

	int *rootInorder = startinorder;
	while(rootInorder<endinorder && *rootInorder != rootValue)
		rootInorder++;
	if(rootInorder == endinorder && *rootInorder != rootValue)
		exception("Invalid Input.");

	int length = rootInorder - startinorder;
	int *leftpreend = startpre + length;

	if(length>0)
		root->m_pLeft = Construct(startpre+1,leftpreend,startinorder,rootInorder-1);
	if(length< endinorder - startinorder)
		root->m_pRight = Construct(leftpreend+1,endinorder,rootInorder+1,endinorder);

	return root;
}



//数字全排列

void print(char* num)
{
	int length = strlen(num);
	int i = 0;
	while(num[i]=='0')
		i++;
	if(i == length)
		cout<<0;
	else
	{
		for(;i<length;i++)
			cout<<num[i];
	}
	cout<<"   ";
}
void PrintRecurisice(char* number,int length, int index)
{
	if(index == length-1)
	{
		print(number);
		return;
	}
	for(int i = 0;i<10;i++)
	{
		number[index+1] = i + '0';
		PrintRecurisice(number,length,index+1);
	}

}

void PrintNum(int n) //n 是位数；
{
	char* num = new char[n+1];
	num[n] = 0;

	for(int i = 0;i < 10;i++)
	{
		num[0] = i + '0';
		PrintRecurisice(num,n,0);
	}
	delete[] num;
}



//3个只出现一次的数；
void findTheSingleNumber(int *arr, int size){  
	int tempA = 0, tempB = 0;  
	int countA = 0, countB = 0;//用来计数用  
	int i = 0, j = 0;  

	for(i = 0; i < 32; i++)
	{ //32位平台上，int只有32位   
		tempA = tempB = countA = countB = 0;  
		for(j = 0; j < size; j++)
		{//遍历数组   
			if(isON(arr[j], i))
			{  
				tempA ^= arr[j];  
				countA++;  
			}else
			{  
				tempB ^= arr[j];  
				countB++;     
			}  
		}  
		if(countA & 0x1)
		{//奇数   
			if(0 == tempB)
			{   
				continue;   
			}else
			{  
				printf("%d\n", tempA);//肯定是不同的数字   
				break;   
			}  
		}
		else
		{  
			if(0 == tempA)
			{  
				continue;  
			}
			else
			{  
				printf("%d\n", tempB);  
				break;   
			}  
		}  
	}  

}  

//字符的全排列
void perm(string &str, int k)  
{  
	int size = str.size();  
	if (k == size - 1)  
		cout<<str<<endl;  
	else  
	{  
		for (int i = k; i < size; ++i)  
		{  
			swap(str.at(i), str.at(k));  
			perm(str, k + 1);  
			swap(str[i], str[k]);  
		}  
	}  
} 
void combine(string &str, int index[], int k, const int m, int size)  
{  
	for (int i = size - 1; i >= k - 1; --i)  
	{  
		index[k - 1] = i;  
		if (k > 1)  
		{  
			combine(str, index, k - 1, m, i);  
		}  
		else  
		{  
			for(int i = 0; i < m; ++i)  
				cout << str[index[i]];  
			cout << endl;  
		}  
	}  
}  


//只能含有2,3,5的数称为丑数
int GetMinNum(int a,int b,int c)
{
	int min = a>b?b:a;
	return min>c?c:min;
}
int GetUglyNumber_Solution(int n)
{
	int *p = new int[n];
	p[0] = 1;
	int next = 1;
	int *p2 = p;
	int *p3 = p;
	int *p5 = p;

	while(next < n)
	{
		int min = GetMinNum(*p2*2,*p3*3,*p5*5);
		p[next] = min;

		while(*p2*2<=min)
			++p2;
		while(*p3*3<=min)
			++p3;
		while(*p5*5<=min)
			++p5;
		++next;

	}
	int getnum = p[next-1];
	delete[] p;
	return getnum;
}
