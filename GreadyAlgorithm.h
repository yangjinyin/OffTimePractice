#include <iostream>

using namespace std;

//s 活动开始时间;f 活动结束时间; flag 存储符合最多活动序列；length：活动总数 返回最多活动序列的个数
int GreadyActivitySelector(int* s,int* f, int* flag ,int length)
{
	int j = 0;
	int num = 0;
	for(int i = 0; i < length; i++)
	{
		if(s[i] >f[j] || s[i] == f[j])
		{
			j = i;
			flag[num++] = i;
		}
	}
	return num;
}

int maxProfit(int* prices, int pricesSize)
{
	int profit=0;
	int buy = prices[0];
	int sell = 0;

	for(int i = 0;i<pricesSize-1;i++)
	{
		if(prices[i+1]>prices[i])
		{
			profit += prices[i+1]-prices[i];
		}
	}
	return profit;
}