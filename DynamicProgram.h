#include <iostream>

using namespace std;

//最大数组和
int MaxStringSum(int A[], int n)
{
	//way 1
	/*int Start = A[0];
	int All = A[0];

	for(int i = 1;i<n;i++)
	{
	Start = max(A[i],A[i]+Start);
	All = max(All,Start);
	}
	return All;*/


	////way 2
	//int Max = -100000;
	//int dp = A[0];
	//for(int i = 1;i < n;i++)
	//{
	//	if(dp<0)
	//		dp = A[i];
	//	else
	//	{
	//		dp = dp + A[i];
	//	}
	//	Max = max(Max,dp); 
	//}
	//return Max;

	//way 3
	int s = A[0];
	int Max = A[0];
	for(int i = 1;i < n;i++)
	{
		s = max(A[i],s+A[i]);
		Max = max(Max,s);
	}
	return Max;
}

//最长递增子序列
int StringAscent(int A[],int n)
{
	int s = 1,Max = 1;
	for(int i = 1;i<n;i++)
	{
		if(A[i]>A[i-1])
			s = s + 1;
		else
			s = 1;
		Max = max(Max,s);
	}
	return Max;
}

//LCS
int LCS(int A[],int B[],int m,int n)
{
	/*int** f = new int*[m];
	for(int i= 0;i<m;i++)
	{
		f[i] = new int[n];
	}*/
	int f[10][10];
	for(int i = 0;i < m;i++)
	{
		
			f[i][0] = 0;
	}
	for(int j = 0;j<n;j++)
		f[0][j] = 0;
	int Max = 0;

	for(int i = 0;i <m;i++)
	{
		for(int j = 0;j <n;j++)
		{
			if(A[i] == B[j])
				f[i+1][j+1] = f[i][j] + 1;
			else 
				f[i+1][j+1] = max(f[i][j+1],f[i+1][j]);
			cout<<f[i][j]<<"   ";
			Max = max(Max,f[i+1][j+1]);
		}
		cout<<endl;
	}
	return Max;
}