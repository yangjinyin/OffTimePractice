#include <iostream>
#include <string>
#include <xstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

class student
{
	int ID;
	string name;

	student(int id,string s){ID =id;name = s;};
	student(){ID = 0;name = "";};
};
void TestMap()
{
	map<int ,string> student;
	//插入
	student.insert(pair<int,string>(4,"d"));
	student.insert(make_pair(5,"f"));
	student.insert(map<int,string>::value_type(6,"e"));
	student[1] = "a";
	student[2] = "c";
	student[3] = "b";
	//map大小
	int num = student.size();
	//遍历
	for(map<int,string>::iterator it = student.begin();it!=student.end();++it)
		cout<<it->first<<it->second<<endl;
	//查找
	map<int,string>::iterator it;
	it = student.find(2);
	 cout<<"Find, the value is "<<it->second<<endl;
	 //如果要删除1，用关键字删除
	 int n = student.erase(1);//如果删除了会返回1，否则返回0
	
}
void TestHash_map()
{

}
void TestOrder_map()
{
	unordered_map<int,int> map;
	map.insert(make_pair(2,1));
}