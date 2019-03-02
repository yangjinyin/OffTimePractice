#include <iostream>
#include <map>
#include <string>

using namespace std;
int father[100];
int find(int x)
{
	if(father[x]!=x)
		father[x] = find(father[x]);
	return father[x];
}
void union_set()
{
	int A[6] = {1,1,5,2,3,4};
	int B[6] = {5,7,9,8,2,6};

	for(int i= 1;i<=9;i++)
	{
		father[i] = i;
	}//为每一个元素建立一个集合
	int a,b;
	for(int j = 1;j<=6;j++)
	{
		a = A[j-1];b = B[j-1];			//读入他们的关系；
		a = find(a);
		b = find(b);
		father[a] = b;
	}
	cin>>a>>b;
	if(find(a) == find(b))
		cout<<"Yes";
	else
		cout<<"No";

}

//hihocoder 1066
string find(map<string,string>&father,string s)
{
	if(father[s]!=s)
		father[s] = find(father,father[s]);
	return father[s];
}
void UnionMap()
{
	int n;
	cin>>n;
	int op;
	map<string,string>set;
	string name1,name2;
	for(int i = 0;i<n;i++)
	{
		cin>>op>>name1>>name2;
		if(set.find(name1)== set.end())
			set.insert(make_pair(name1,name1));
		if(set.find(name2)== set.end())
			set.insert(make_pair(name2,name2));
		if(op == 0)
		{	
			name1 = find(set,name1);
			name2 = find(set,name2);
			if(name1!=name2)
				set[name1] = name2; 
		}
		else
		{
			if(find(set,name1) == find(set,name2))
				cout<<"yes"<<endl;
			else
				cout<<"no"<<endl;
		}
	}

}