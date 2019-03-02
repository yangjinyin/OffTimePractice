#include <iostream>

using namespace std;

void Compute_Prefix(char* pattern,int length,int a[])
{
	a[0] = 0;
	int k = 0;
	for(int i = 1;i < length; i++)
	{
		while(k>0 && pattern[k]!=pattern[i])
			k = a[k-1];
		if(pattern[k] == pattern[i])
			k++;
		a[i] = k;
	}
}

//pattern:需要匹配项(abcdabd)；target：目标匹配项(ababxbababcdabdfdsss);
int KMP(char* pattern,char *target,int patternlength,int targetlength)
{
	int* next = new int[patternlength];
	for(int s = 0; s < patternlength;s++)
		next[s] = 0;
	Compute_Prefix(pattern,patternlength,next);
	int i = 0;
	int j = 0;
	for(;j<targetlength;j++)
	{
		while(i>0 && pattern[i]!=target[j])
		{
			i = next[i-1];
		}
		if(pattern[i]==target[j])
		{
			i++;
		}
		if(i == patternlength)
		{
			delete[] next;
			return j-patternlength+1;
		}
	}
	
	delete[] next;
	return -1;

}


