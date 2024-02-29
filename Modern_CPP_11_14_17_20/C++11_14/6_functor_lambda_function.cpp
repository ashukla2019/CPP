/*Functors: Calling object using parenthesis like function call. 
One advantage of functors over function pointers is that they can hold state. 
Since this state is held by the instance of the object it can be thread safe 
(unlike static variables inside functions used with function pointers). 
The state of a functor can be initialized at construction.

function pointer can not have additional value/state:
*/
class fun
{
	int value;
	public:
		fun(int value):value(value){}
		void operator ()(int x)
		{
			if(value < x)
			cout<<"value ="<<x<<endl;
		}
};

int main()
{
	fun f(10); //passing additional value and will be stored into data member
    f(20);
    return 0;
}

void print(int val)
{
    cout<<"val="<<val<<"\n";
}

int main()
{
    vector<int>vec{10, 20, 30, 40};
    for_each(vec.begin(), vec.end(), print); //we can pass only parameter but not additional value.
    return 0;
}

#include<iostream>
#include <vector>
#include<algorithm>	
using namespace std;

//Implemented functor using struct multiply

struct multiply
{
	private:
	int factor;
	public:
	multiply(){}
	multiply(int x):factor(x){}
	void operator()(int y)
	{
		cout<<"Multiplied vector values:"<<factor*y<<endl;
	}
	
};

//Implemented functor using class multiply

class multiply
{
	private:
		int factor;
	public:
	multiply(){}
	multiply(int x):factor(x){}
	void operator()(int y)
	{
		cout<<"Multiplied vector values:"<<factor*y<<endl;
	}
	
};

------------------------------------Lambda Function--------------------------------------
int main()
{
	vector<int>vec = {1,2,3,4};
	int factor = 2;
	//for_each(vec.begin(), vec.end(), multiply(2)); //calling functor(multiply(x)--> value will be passed to constructor)
	//using lambda function
	for_each(vec.begin(), vec.end(), [factor](int y){ //[] will take local variable and () will take vector values
	cout<<"Multiplied vector values:"<<factor*y<<endl;});
	return 0;
}
//A 'Lambda' function: A lambda is an unnamed function that is useful (in actual programming, not theory) 
//for short snippets of code that are impossible to reuse and are not worth naming.

syntax: [ capture clause ] (parameters) -> return-type //return type is evaluated by compiler 
		{   
			definition of method   
		} 

int main()
  {
      auto sum = [](int x, int y) { return x + y; };
      cout << sum(5, 2) << endl;
      cout << sum(10, 5) << endl;
  }

//C++ 14 provided generic lambda, suppose you want to have sum function for integer/float etc.
[](auto a, auto b) { return a + b; }

int main() 
{ 
  
    // Declare a generalized lambda and store it in sum 
    auto sum = [](auto a, auto b) { 
        return a + b; 
    }; 
  
    // Find sum of two integers 
    cout << sum(1, 6) << endl; 
  
    // Find sum of two floating numbers 
    cout << sum(1.0, 5.6) << endl; 
  
    // Find sum of two strings 
    cout << sum(string("Geeks"), string("ForGeeks")) << endl; 
  
    return 0; 
} 

/*
	  A lambda expression can have more power than an ordinary function by having 
	  access to variables from the enclosing scope. We can capture external variables
	  from enclosing scope by three ways : 
      Capture by reference 
      Capture by value 
      Capture by both (mixed capture)
	  Syntax used for capturing variables : 
      [&] : capture all external variable by reference--->
			
			int main()
			{
   			   int i = 3;
			   int j = 5;

			   // The following lambda expression captures i by value and
			   // j by reference.
			   function<int (void)> f = [&i, &j] { return i + j; };

			   // Change the values of i and j.
			   i = 22;
			   j = 44;

			   // Call f and print its result.
			   cout << f() << endl;
			} O/P: 66
		
      [=] : capture all external variable by value--->
			
			int main()
			{
				int i = 3;
				int j = 5;

				// The following lambda expression captures all external values
				auto f = [=] { return i + j; };

				// Call f and print its result.
				cout << f() << endl;
}
			
      [a, &b] : capture a by value and b by reference--->
				int main()
				{
					int i = 3;
					int j = 5;

					// The following lambda expression captures i by value and
					// j by reference.
					function<int (void)> f = [i, &j] { return i + j; };
					// Change the values of i and j.
					i = 22;
					j = 44;
					// Call f and print its result.
					cout << f() << endl;
				}
				O/P: 47
				
	  An empty capture clause, [ ] , indicates that the body of the lambda expression 
	  accesses no variables in the enclosing scope 
*/


