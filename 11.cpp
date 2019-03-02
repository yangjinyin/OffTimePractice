#include<iostream>

using namespace std;
#define pi 3.14

class Circle
{
	int number;
	double x,y,R;
	static int count,Max_num;
public:
	Circle(double x,double y,double R);   //构造函数
	Circle(const Circle &circle);         //拷贝构造函数
	static int get_num()
	{
		return count;
	}
	Circle &operator++();
	Circle operator++(int);
	friend Circle operator+(Circle &a,Circle &b);   //友元，得到一个新圆
	friend ostream &operator<<(ostream &os, Circle &circle);  //友元，流输出运算
	 double area() const;
	double length();
	~Circle()
	{
		Circle::count--;
	}
};

Circle::Circle(double m_x,double m_y,double m_R)
{
	x=m_x;
	y=m_y;
	R=m_R;
	count++;
	number=++Max_num;
}

Circle::Circle(const Circle& circle)
{
	x=circle.x;
	y=circle.y;
	R=circle.R;
	count++;
	number=++Max_num;
}

Circle &Circle::operator++()
{
	R+=1;
	return *this;
}

Circle Circle::operator++(int)
{
	Circle temp(*this);
	++*this;
	return temp;
}

Circle operator+(Circle &a,Circle &b)
{
	double new_x=(a.x+b.x)/2,new_y=(a.y+b.y)/2;
	double new_radius=sqrt((a.area()+b.area())/pi);
	Circle s(new_x,new_y,new_radius);
	Circle::Max_num--;
	return s;
}

ostream &operator<<(ostream &os, Circle &circle)
{
	os<<"圆形的编号:"<<circle.number<<" 圆心坐标:"<<circle.x<<','<<circle.y<<" 半径:"<<circle.R<<"area"<<circle.area()<<endl;
	return os;
}

 double  Circle::area()const
{
	return pi*this->R*this->R;
}

double Circle::length()
{
	return 2*pi*this->R;
}

int Circle::count=0;
int Circle::Max_num=0;

int main()
{
	Circle c1(1.12, 2.23, 3.34), c2(c1);

	cout << c1 << c2;
	cout << "Number of circles = " << Circle::get_num() << endl;

	Circle c3 = c1 + c2;
	cout << c3;
	cout << "Number of circles = " << Circle::get_num() << endl;

	cout << c1++;
	cout << ++c2;
	cout << c1;

	return 0;
}