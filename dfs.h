#include <iostream>
#include <list>
#include <math.h>
#include <vector>

using namespace std;

int matrix[8][8];
int count1 = 0;
//检验列和对角线是否有重合；
bool check(int row,int col)
{
	for(int i = 0;i<row;i++)
	{
		int j = matrix[i][0];
		if(j == col ||abs(row-i) == abs(col-j))
			return false;
	}
	return true;
}
//第row行放入皇后；
void eightQueueDfs(int row)
{
	if(row>=8)
		count1++;
	else
	{
		for(int j = 0;j < 8;j++)
		{
			matrix[row][j] = 1;
			if(check(row,j))
			{
				matrix[row][0] = j;
				eightQueueDfs(row+1);
			}
			matrix[row][j] = 0;
		}
	}
}

void eightQueue()
{
	eightQueueDfs(0);
	cout<<count1;
}

//前i个数字和sum，共有n个数字，是否存在一种组合使得和为k
int dfs(int i,int sum,int n,int k,int* a)
{
	if(i == n)
		return sum==k;
	if(dfs(i+1,sum,n,k,a))
		return 1;
	if(dfs(i+1,sum+a[i],n,k,a))
		return 1;
	return 0;
}

