#include<iostream>
using namespace std;
class A
{
private:	
	int x;
public:
	A():x(10){}
	friend ostream& operator<<(ostream& out, const A& a)
	{
		out<<a.x;
		out<<"my operator << is called";
		return out;
	}
	friend istream& operator>>(istream& is, A& a)
	{
		is >> a.x;
		return is;
	}
	void operator+(int y)
	{
		x+= y;
	}
	void printvalue()
	{
		cout<<"data value="<<x<<"\n";
	}
	A& operator=(const A& a)
	{
		return *this;
	}

	
};
int main()
{
	A a,a1;
	cout<<a; //will overload operator << from my class.
	cin >> a; //will overload operator >> from my class.
	a+5; //will overload + operator(a1.operator+(int))
	a.printvalue();
	a1 = a;
	a1.printvalue();
	return 0;
}
