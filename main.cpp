#include "Sort.h"
#include "BinarySearchTree.h"
#include "BalancedBinaryTree.h"
#include "RedBlackTree.h"
#include "Graphics.h"
#include "KMP.h"
#include "FindOffer.h"
#include "LeetCode.h"
#include "GreadyAlgorithm.h"
#include "dfs.h"
#include "map.h"
#include "union_set.h"
#include "Maxfilp.h"
#include <stdlib.h>
#include "ListNode.h"
#include <stdio.h>
#include<string>
#include <cstring>

int getArrMax(int arr[],int begin,int end)
{
	int max=0;
	int Min=arr[begin];
	for(int i = begin+1;i<=end;i++)
	{
		if(Min>arr[i])
			Min = arr[i];
		if(arr[i]-Min>max)
			max = arr[i]-Min;
		return max;
	}
}

class B
{

public:
	void fun(){cout<<"b";}
};
class C:public B
{
public:
	void fun(){cout<<"c";};
};
int main()
{
	/*int map[5][5] = 
	{                     
	{0, 10, INT_MAX, INT_MAX, 5},  
	{INT_MAX, 0, 1, INT_MAX, 2},  
	{INT_MAX, INT_MAX, 0, 4, INT_MAX},  
	{7, INT_MAX, 6, 0, INT_MAX},  
	{INT_MAX, 3, 9, 2, 0}  
	}; 
	int distance[5];  
	int preVertex[5]; 
	Dijkstra(5, 0, map, distance, preVertex);

	cout<<distance[2]<<endl;
	cout<<preVertex[2]<<preVertex[1];*/
	//InversePairs();
	//Edmonds_Karp();
	//cout<<MinimumRepresentation("bacad",4);
	//Prim();
	/*int A[5]={3,30,34,5,9};
	vector<int> v(A,A+5);
	largestNumber(v);*/
	/*char str[10] = "abcdefg";
	cout<<sizeof(str)<<endl;
	cout<<sizeof(&str);
	cout<<strlen(str);*/
	//int shares[5] = {2,5,10,14,18};
	//int m1,m2,Max;
	//for(int j=1;j<5-1;j++)  
	//{  
	//	m1=getArrMax(shares,0,j);  
	//	m2=getArrMax(shares,j,5-1);  
	//	Max=max(Max,m1+m2);  
	//}
	//cout<<Max;
	/*char* s= "babad";
	cout<<longestPalindrome(s);*/
	//getTopKFromTwoArrays(A,3,B,3,4);

	char c1 = '(';
	char c2 = ')';
	cout<<c2+1<<endl;

}







