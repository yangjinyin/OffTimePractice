#include <iostream>
#include <string>
#include <xstring>
#include <vector>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <algorithm>
#include "ListNode.h"
#include <stdlib.h>
using namespace std;


//正则表达式匹配；
bool isMatch(string s, string p) 
{
	char* ss =const_cast<char*>(s.c_str());
	char* pp = const_cast<char*>(p.c_str());
	if(ss == NULL || pp == NULL)
		return false;
	if(*ss == 0 && *pp == 0)
		return true;
	if(*ss != 0 && *pp == 0)
		return false;

	if(*(pp+1) == '*')
	{
		if(*pp == *ss || (*pp == '.' && *ss != 0))
			return isMatch(ss+1,pp+2) || isMatch(ss+1,p) || isMatch(s,pp+2);
		else
			return isMatch(s,pp+2);
	}

	if(*ss == *pp || (*pp == '.'&& *ss != 0))
		return isMatch(ss+1,pp+1);

	return false;
}

//First Unique Character in a String
int firstUniqChar(string s)
{
	int hash[26]={0};
	if(s=="")
		return -1;
	for(int i = 0;i < s.length();i++)
	{
		if(s[i])			
		{
			int j = s[i]-'a';
			hash[j]++;
		}
	}
	for(int i = 0;i < s.length();i++)
	{
		if(hash[s[i]-'a'] == 1)
			return i;
	}

	return -1;
}

//数组中找出两个数的和为target的值
vector<int> twoSum(vector<int>& nums, int target)
{
	map<int, int> hash;
	vector<int> result;
	for (int i = 0; i < nums.size(); i++) {
		int numberToFind = target - nums[i];
	
		if (hash.find(numberToFind) != hash.end()) 
		{	
			result.push_back(hash[numberToFind]);
			result.push_back(i);			
			return result;
		}	
		hash[nums[i]] = i;
	}
	return result;

}

string reverseString(string s)
{
	if(s ==""|| s.empty())
		return "";
	int n = s.length();
	char tmp;
	for(int i = 0;i<n/2;i++)
	{
		tmp = s[i];
		s[i] = s[n-1-i];
		s[n-1-i] = tmp;
	}
	return s;
}

int singleNumber(vector<int>& nums) 
{
	int num = nums.size();

	if(num == 0)
		return 0;
	if(num == 1)
		return nums[0];
	int single = 0;
	for(int i=0;i<num;i++)
	{
		int j = nums[i];
		single = single^nums[i];
	}
	return single;
}
//两个string中不同的一个字符；
char findTheDifference(string s, string t)
{
	char tmp = 0;
	for(int i = 0;i<s.length();i++)
	{
		tmp = tmp^s[i];
	}
	for(int i = 0;i<t.length();i++)
	{
		tmp = tmp^t[i];
	}
	return (char)tmp;

}

int addDigits(int num) 
{
	if(num == 0)
		return 0;
	if(num%9 == 0)
		return 9;
	return num%9;
}
void moveZeroes(int* nums, int numsSize)
{
	if(numsSize == 0)
		return;
	int i = 0;
	int j =0;
	for(;i<numsSize;i++)
	{
		if(nums[i]!=0)
		{
			nums[j] = nums[i];
			j++;
		}
	}
	for(;j<numsSize;j++)
		nums[j] = 0;
}
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) 
{
	int** f = (int**)malloc((nums1Size+1)*sizeof(int*));
	for(int i= 0;i<=nums1Size;i++)
	{
		f[i] = (int*)malloc((nums2Size+1)*sizeof(int));
	}
	for(int i= 0;i<=nums1Size;i++)
	{
		for(int j = 0;j<=nums2Size;j++)
			f[i][j] = 0;
	}
	int max = 0;
	returnSize =(int*)malloc(sizeof(int));
	returnSize = &max;
	if(nums1Size==0 || nums2Size == 0)
		return returnSize;
	for(int i = 0;i<nums1Size;i++)
	{
		for(int j = 0;j<nums2Size;j++)
		{
			if(nums1[i] == nums2[j])
			{
				f[i+1][j+1] = f[i][j]+1;
				max = max>f[i+1][j+1]?max:f[i+1][j+1];
			}
		}
	}
	for(int i= 0;i<=nums1Size;i++)
	{
		free (f[i]);
	}
	free (f);
	return returnSize;

}

//超过1/2的数；
int majorityElement(int* nums, int numsSize) 
{
	int tmp = nums[0];
	int count = 1;
	for(int i = 0;i < numsSize;i++)
	{
		if(nums[i] == tmp)
			count++;
		else
		{
			count--;

			if(count == 0)
			{
				tmp = nums[i];
				count++;
			}
		}
	}

	return tmp;
}
//Valid Anagram
bool isAnagram(char* s, char* t) 
{
	int alphabet[26]={0};
	for(int i = 0; i < strlen(s); i++) 
		alphabet[s[i] - 'a']++;
	for(int i = 0; i < strlen(t); i++) 
		alphabet[t[i] - 'a']--;
	for(int i=0;i<26;i++) 
		if (alphabet[i]!= 0) 
			return false;
	return true;
}

//n的二进制的1个个数
int hammingWeight(unsigned n)
{
	int num = 0;
	while(n)
	{
		num++;
		n = n&(n-1);
	}
	return num;
}
int exgcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;
	}
	int r=exgcd(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-a/b*y;
	return r;
}

int aplusb(int a, int b) 
{
	if(b == 0)
		return a;
	else 
	{
		int c=a^b;
		int d=(a&b)<<1;
		return aplusb(c,d);
	}
}

int maxDepth(BinaryTree* root)
{

	if(root == NULL)
		return 0;
	int left=1;
	int right=1;
	left+=maxDepth(root->leftNode);
	right+=maxDepth(root->rightNode);

	return left>right?left:right;
}
BinaryTree* invertTree(BinaryTree* root) 
{
	if(root==NULL)
		return root;
	if(root->leftNode || root->rightNode)
	{
		BinaryTree* tmp;
		tmp = root->leftNode;
		root->leftNode = root->rightNode;
		root->rightNode = tmp;
	}
	if(root->leftNode)
		invertTree(root->leftNode);
	if(root->rightNode)
		invertTree(root->rightNode);
}
bool isSymmetric(BinaryTree* left,BinaryTree* right) 
{
	if(left && right)
	{
		if(left->m_element == right->m_element)
		{
			return isSymmetric(left->leftNode,right->rightNode) && isSymmetric(left->rightNode,right->leftNode);
		}
		return false;
	}
	if(left==NULL && right==NULL)
		return true;
	return false;
}
bool isSymmetric(BinaryTree* root) 
{
	if(root==NULL)
		return true;
	if(root->leftNode&&root->rightNode)
	{
		return(isSymmetric(root->leftNode,root->rightNode));
	}
	if(root->leftNode == NULL && root->rightNode == NULL)
		return true;
	return false;
}
string addBinary(string a, string b)
{
	int a_length = a.size();
	int b_length = b.size();
	string sum = "";
	sum.resize(a_length>b_length?a_length:b_length);

	int i = a_length-1;
	int j = b_length-1;
	int flag = 0; //进位
	int n = i>j?i:j;
	while(i>=0&&j>=0)
	{
		sum[n] = ((a[i]-'0')^(b[j]-'0')^flag) + '0';
		if(((a[i]-'0')+(b[j]-'0')+flag)>1)
			flag = 1;
		else
			flag = 0;
		i--;
		j--;
		n--;
	}
	while(i>=0)
	{
		sum[n] = (a[i]-'0')^0^flag + '0';
		if(((a[i]-'0')+flag)>1)
			flag = 1;
		else
			flag = 0;
		i--;
		n--;
	}
	while(j>=0)
	{
		sum[n] = (b[j]-'0')^0^flag + '0';
		if(((b[j]-'0')+flag)>1)
			flag = 1;
		else
			flag = 0;
		j--;
		n--;
	}
	if(flag == 1)
	{
		sum = "1"+ sum;
	}
	return sum;
}

bool hasPathSum(BinaryTree* root, int sum) 
{
	if(root==NULL )
		return false;
	if(root->leftNode==NULL && root->rightNode==NULL && root->m_element == sum)
		return true;
	if(root->leftNode || root->rightNode)
	{
		return hasPathSum(root->leftNode,sum-(root->m_element))|| hasPathSum(root->rightNode,sum-root->m_element);
	}

	return false;
}

int minDepth(BinaryTree* root) 
{
	if(root==NULL)
		return 0;
	int left = 1;
	int right = 1;
	
	left+=minDepth(root->leftNode);
	right+=minDepth(root->rightNode);

	return left>right?right:left;
}
string shortestPalindrome(string s) 
{
	string rev_s = s;
	reverse(rev_s.begin(), rev_s.end());
	string l = s + "#" + rev_s;

	vector<int> p(l.size(), 0);
	for (int i = 1; i < l.size(); i++) {
		int j = p[i - 1];
		while (j > 0 && l[i] != l[j])
			j = p[j - 1];
		p[i] = (j += l[i] == l[j]);
	}

	return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;
}
ListNode* swapPairs(ListNode* head)
{
	if(head == NULL || head->m_pNext ==NULL)
		return head;
	ListNode* p1,*p2,*p3,*p4;
	p1 = head;

	p2 = p1->m_pNext;
	head = p2;
	while(p2)
	{
		p3 = p2->m_pNext;
		
		p2->m_pNext = p1;

		if(p3)
		{
			p1->m_pNext = p3;
			p4 = p3->m_pNext;
			if(p4)
				p1->m_pNext = p4;
			p1 = p3;
			p2 = p4;
		}
		else
		{
			p1->m_pNext = NULL;
			p2 = NULL;
		}
	}
	return head;
}
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
{
	ListNode *phead;
	ListNode * p1;
	if(l1==NULL&&l2==NULL)
		return NULL;
	if(l1&&l2==NULL)
		return l1;
	if(l1==NULL && l2)
		return l2;
	if(l1->m_nKey<l2->m_nKey)
	{
		phead = l1;
		l1 = l1->m_pNext;
	}
	else
	{
		phead = l2;
		l2 = l2->m_pNext;
	}
	p1 = phead;
	while(l1 && l2)
	{
		if(l1->m_nKey<l2->m_nKey)
		{
			p1->m_pNext = l1;
			p1 = l1;
			l1 = l1->m_pNext;
		}
		else
		{
			p1->m_pNext = l2;
			p1 = l2;
			l2 = l2->m_pNext;
		}
	}
	if(l1)
	{
		p1->m_pNext = l1;
	}
	if(l2)
	{
		p1->m_pNext = l2;
	}
	return phead;
}
int myAtoi(char* str) 
{
	int sign = 1, base = 0, i = 0;
	while (str[i] == ' ') { i++; }
	if (str[i] == '-' || str[i] == '+') {
		sign = 1 - 2 * (str[i++] == '-'); 
	}
	while (str[i] >= '0' && str[i] <= '9') {
		if (base >  INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7)) 
		{
			if (sign == 1) 
				return INT_MAX;
			else 
				return INT_MIN;
		}
		base  = 10 * base + (str[i++] - '0');
	}
	return base * sign;
}
bool isUgly(int num) 
{
	while(num%2==0)
		num /=2;
	while(num%3==0)
		num/=3;
	while(num%5==0)
		num /=5;
	if(num==1)
		return true;
	return false;
}
void rotate(int* nums, int numsSize, int k) 
{
	k = k%numsSize;
	for(int i = 0;i<numsSize/2;i++)
	{
		int temp = nums[i];
		nums[i] = nums[numsSize-1-i];
		nums[numsSize-1-i] = temp;
	}
	for(int i = 0;i<k/2;i++)
	{
		int temp = nums[i];
		nums[i] = nums[k-1-i];
		nums[k-1-i] = temp;
	}
	for(int n = 0;n<(numsSize-k)/2;n++)
	{
		int i = k;
		int temp = nums[i+n];
		nums[i+n] = nums[numsSize-1-n];
		nums[numsSize-1-n] = temp;
	}
	for(int i = 0;i<numsSize;i++)
		cout<<nums[i];
}

int reverse(int x) 
{   
	int result = 0;

	while (x != 0)
	{
		int tail = x % 10;
		int newResult = result * 10 + tail;
		if ((newResult - tail) / 10 != result)   //overflow处理的很巧妙；
		{ return 0; }
		result = newResult;
		x = x / 10;
	}

	return result;

}
string convertToTitle(int n) 
{
	string res = "";
	while(n != 0) {
		char ch = (char)((n - 1) % 26 + 65);
		n = (n - 1) / 26;
		res = ch + res;
	}
	return res;
}
int titleToNumber(string s)
{
	if( s=="")
		return 0;
	int length = s.length();
	int n = 0;
	int e = 1;
	for(int i = length-1;i>=0;i--)
	{
		n = n+e*(s[i]-('A'-1));
		e = e*26;
	}
	return n;
}
int countPrimes(int n)
{
	int* A = new int[n+1];
	for(int i = 0;i<=n;i++)
		A[i] = 1;
	for(int i = 2;i<=sqrt(double(n));i++)
	{
		if(A[i]==1)
		{
			int temp = 2;
			while(i*temp<=n)
			{
				A[i*temp] = 0;
				temp++;
			}
		}
	}
	int sum = 0;
	for(int i = 2;i<=n;i++)
	{
		if(A[i]==1)
		{
			cout<<i<<"   ";
			sum++;
		}
	}
	return sum;
}
int lengthOfLastWord(string s)
{
	if(s.length()==0||s == " ")
		return 0;
	int i = s.find_last_of(' ');
	if(i == 0)
		return s.length()-1;
	int j = s.length();
	return j-i-1;
}
int sumOfLeftLeaves(BinaryTree* root)
{
	int sum = 0;
	if(root == NULL)
		return 0;
	if(root->leftNode== NULL && root->rightNode == NULL)
		return root->m_element;
	if(root->leftNode)
		sum+=sumOfLeftLeaves(root->leftNode);
	if(root->rightNode && (root->rightNode->leftNode || root->rightNode->rightNode))
		sum+=sumOfLeftLeaves(root->rightNode);
	return sum;
}
int romanToInt(string s) 
{
	int dic[26];
	dic['I'-'A']=1;
	dic['V'-'A']=5;
	dic['X'-'A']=10;
	dic['L'-'A']=50;
	dic['C'-'A']=100;
	dic['D'-'A']=500;
	dic['M'-'A']=1000;

	int intValue = 0; 
	int prev = 0; 
	for(int i = s.size() - 1; i >= 0; i--) {
		int addOrSubtract = dic[s[i] - 'A']; 
		intValue += (prev > addOrSubtract) ? -addOrSubtract : addOrSubtract; 
		prev = addOrSubtract; 
	}
	return intValue; 

}
int* singleNumber(int* nums, int numsSize, int* returnSize)
{
	int xor = 0;
	for(int i = 0;i<numsSize;i++)
	{
		xor = xor^nums[i];
	}

	xor&=-xor;
	returnSize = new int[2];
	returnSize[0] = 0;
	returnSize[1] = 0;
	for(int j = 0;j<numsSize;j++)
	{
		if(xor&nums[j])
		{
			returnSize[0]^=nums[j];
		}
		else
		{
			returnSize[1] ^=nums[j];
		}
	}
	return returnSize;
}
int countNumbersWithUniqueDigits(int n)
{
	int sum = 0;
	int count = 9;
	if(n == 1)
		return 10;
	for(int i =1 ;i<n;i++)
	{
		count  = count*(10-i);
	}
	sum = countNumbersWithUniqueDigits(n-1)+count;

}

int InversePairs(int a[],int begin,int end,int temp[])
{
	if(begin==end)
	{
		temp[begin] = a[begin];
		return 0;
	}
	int length = (end-begin)/2;
	int left = InversePairs(a,begin,begin+length,temp);
	int right = InversePairs(a,begin+length+1,end,temp);

	int count = 0;
	int i = begin+length;              //左边的最大元素；
	int j = end;						//右边最大的元素；
	int index = j;
	while(i>=begin && j>=(begin+length+1))
	{
		if(a[i]>a[j])
		{
			count+=(j-begin-length);
			temp[index--] = a[i--];
		}
		else
			temp[index--] = a[j--];
	}
	while(i>=begin)
		temp[index--] = a[i--];
	while(j>=(begin+length+1))
		temp[index--] = a[j--];
	for(int i = 0;i<(end-begin+1);i++)
		a[begin+i] = temp[begin+i];

	return count+left+right;
}
void InversePairs()
{
	int n;
	int a[10000];
	int b[10000];
	
	while(!cin.eof())
	{
		cin>>n;
		for(int i = 0;i<n;i++)
		{
			cin>>a[i];
			b[i] = a[i];
		}

		cout<<InversePairs(a,0,n-1,b);
	}
	
}
typedef pair<int, int> PAIR; 
bool compare_by_value(const PAIR& l,const PAIR& s)
{
	return l.second>s.second;
}
vector<int> topKFrequent(vector<int>& nums, int k) 
{
	map<int,int> map;
	for(int i = 0;i<nums.size();i++)
	{
		if(map.find(nums[i])==map.end())
			map.insert(make_pair(nums[i],1));
		else
			map[nums[i]]++;
	}

	vector<PAIR>v(map.begin(),map.end());

	sort(v.begin(),v.end(),compare_by_value);
	nums.clear();
	if(nums.empty())
	{
		for(int i = 0;i<k;i++)
		{
			nums.push_back(v[i].second);
		}
	}
	return nums;
}
int integerBreak(int n) 
{
	int sum = 1;
	if(n == 1)
		return 0;
	if(n == 2)
		return 1;
	if(n == 3)
		return 3;
	while(n>3)
	{
		n-=3;
		sum*=3;
	}
	if(n==1)
	{
		sum/=3;
		sum*=4;
	}
	else
	{
		sum *= n;
	}
	return sum;
}
int missingNumber(int* nums, int numsSize) 
{
	int sum = 0;
	for(int i= 0;i<numsSize;i++)
	{
		sum+=(i+1);
		sum-=nums[i];
	}
	return sum;
}
void TopKUseQueue(int *a,int size,int k)
{
	priority_queue<int> q; //栈顶元素最大；
	
	for(int i = 0;i<size;i++)
		q.push(a[i]);
	for(int i = 0;i<k;i++)
	{
		cout<<q.top();
		q.pop();
	}
}
int compar_words(const void *p, const void *q)
{
	return strcmp(*(char **)p, *(char **)q);
}
bool cmp(const string &a, const string &b) {
	return a + b > b + a;
}
string largestNumber(vector<int>& nums) 
{
	vector<string> v;
	char c[64];
	for(int i  = 0;i<nums.size();i++)
	{
		sprintf(c,"%c",nums[i]);
		string temp(c);
		v.push_back(temp);
	}

	sort(v.begin(),v.end(),cmp);
	string ans;
	for (int i = 0; i < v.size(); ++i) 
	{
		ans += v[i];
	}

	if (-1 == ans.find_first_not_of('0')) 
	{
		return "0";
	} else
	{
		return ans;
	}
	
}

//vector<pair<int,int>>getTopKFromTwoArrays(int* A,int n,int *B,int m,int k)
//{
//	
//	priority_queue<int,pair<int,int>,vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;
//	set<int,int> s;
//	vector<pair<int,int>> ans;
//	q.push(make_pair(A[0] + B[0], make_pair(0, 0)));
//	s.insert(make_pair(0,0));
//	int i = 0,j = 0;
//	while(k && !q.empty())
//	{
//		pair p = q.top();
//		ans.push_back(make_pair(A[p.second.first],B[p.second.second]));
//		q.pop();
//
//		if(i+1<n && s.find(make_pair(i+1,j))== s.end())
//		{
//			i++;
//			s.insert(make_pair(i+1,j));
//			q.push(make_pair(A[i+1] + B[j], make_pair(i+1, j)));
//		}
//		if(j+1<m && s.find(make_pair(i,j+1))== s.end())
//		{
//			j++;
//			s.insert(make_pair(i,j+1));
//			q.push(make_pair(A[i] + B[j+1], make_pair(i, j+1)));
//		}
//	}
//	return ans;
//}

//414
int thirdMax(int* nums, int numsSize) 
{
	int max = INT_MIN,secondmax = INT_MIN,thirdmax = INT_MIN;
	int flag;
	for(int i = 0;i<numsSize;i++)
	{
		if( INT_MIN == nums[i])
			flag == 1;
		if(max==nums[i] || secondmax == nums[i] || thirdmax == nums[i])
		{
			continue;
		}
		if(nums[i]>thirdmax)
		{
			thirdmax = nums[i];
			if(thirdmax>secondmax)
			{
				swap(thirdmax,secondmax);
				if(secondmax>max)
					swap(max,secondmax);
			}
		}
	}
	if(max == INT_MIN || secondmax == INT_MIN || thirdmax == INT_MIN && flag==0)
		return max;
	return thirdmax;
}

int GetMinLength(int *a,int s,int n)
{
	int *b = new int[n];
	b[0] = 0;
	for(int i = 0; i < n;i++)
		b[i+1] = b[i]+a[i];

	int i = 0;
	int length = 0;
	for(int j = 0;i<n;i++)
	{
		if(b[j]-b[i]<s)
			continue;
		while(b[j]-b[i]>s)
			i++;
		length = min(length,(j-i));
	}
	return length;
}

int searchInsert(int* nums, int numsSize, int target) 
{
	int middle;
	int left = 0;
	int right = numsSize -1;
	if(numsSize <1 )
		return 0;
	if(numsSize == 1)
	{
		if(nums[0] < target)
			return 1;
		else
			return 0;
	}

	while(left < right)
	{
		if(right == left + 1 )
		{
			if(nums[left] < target && nums[right] > target)
				return right;
			if(nums[left] > target || nums[left] == target)
				return left;
			if(nums[right] < target)
				return right+1;
			if(nums[right] == target)
				return right;
		}

		middle = (left + right)/2;
		if(nums[middle] > target)
			right = middle;
		else if(nums[middle] == target)
			return middle;
		else
			left = middle;


	}
	return left;
}

string longestPalindrome(string s) 
{  
	const int size_s = s.size();
	int max_s = 0, max_l = 0;
	for (int i = 0; i < size_s;)
	{
		int start = i, end = i;
		while (end + 1 < size_s && s[end] == s[end+1]) 
			end++;
		i = end + 1;
		while (start - 1 >= 0 && end + 1 < size_s && s[start-1] == s[end+1]) 
		{
			start--;
			end++;
		}
		if (end - start + 1 > max_l) 
		{
			max_l = end - start + 1;
			max_s = start;
		}
	}
return s.substr(max_s, max_l);
}

int longestValidParentheses(string s)
{
	const int size = s.size();
	int sum = 0;
	int max = 0;
	for(int i = 0; i < size; i++)
	{
		if(s[i] == ')')
			sum -= 1;
		if(s[i] == '(')
			sum +=1;
		if(sum > -1)
	}

	return 1;
}