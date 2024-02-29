//If we create object of class, constructor is called
class A 
{
public:
	A() //first memory will be allocated to object and then data member is initialized with
	    //default value zero and then value 10 is assigned.
	{
		x = 10;
	}
	
	//if we use initializer list, first memory will be allocated to object and actual value is assigned.
};

/*Prefer in-class member initializer over constant initializations OR over
//default constructor.
class A 
{
	string s = "def"; //in class member initialization
	int i = 10; // in class member initialization
public:
	A(string val):s{val}{}
	A()=default; //use compiler generated default constructor
};

Benefits: 
No overhead of taking care of initializing constants separately in each constructor.
Performance gain by using standard default constructors.

*/


//initializer list and uniform initialization: 
  //uniform initialization: assignment operator is overhead: first resolve right hand side then
 //allocate memory. So need uniform way of initialization.

	//Uniform initialization syntax:
	std::vector<int> v { 1, 2, 3 };
    std::map<int, std::string> m { {1, "one"}, { 2, "two" }};
	int* arr2 = new int[3]{ 1, 2, 3 };  //dynamic allocated array.
	int arr1[3] { 1, 2, 3 }; //array 
	int i { 42 }; //Built-in types
	//user defined types....
	class foo
        {
          int a_;
          double b_;
        public:
          foo():a_(0), b_(0) {}
          foo(int a, double b = 0.0):a_(a), b_(b) {}
        };

        foo f1{}; 
        foo f2{ 42, 1.2 }; 
        foo f3{ 42 };
         
//uniform initialization search order:
	//initializer_list constructor: myclass(const initializer_list<int>&v){}. all stl containers support it.
	//regular constructor that takes appropriate parameters myclass(int x, int y, int z): follows member by member copy
	//Aggregate initializer => myclass m ={1, 2, 3}; it does byte by byte copy
	
	class A
	{
	public:
		int mx;
		double my;
	};

	class B
	{
	public:
		B(int x, double y) : mx{ x }, my{ y } {}

		int mx;
		double my;
	};

	class C
	{
	public:
		C(int x, double y) : mx{ x }, my{ y } {}
		C(const std::initializer_list<int>& v) {
			mx = *(v.begin());
			my = *(v.begin() + 1);
		}

		int mx;
		double my;
	};

	int main()
	{
		// Aggregate initialization
		A a{ 1, 3.7 };

		// Regular constructor
		B b{ 2, 9.8 };

		// Initializer_list
		C c{ 3, 7 };

		std::cout << a.mx << " " << a.my << std::endl;
		std::cout << b.mx << " " << b.my << std::endl;
		std::cout << c.mx << " " << c.my << std::endl;

		return 0;
	}
		
	Ex: int *pi = new int[5]{1, 2, 3, 4, 5};
	std::vector v1{1, 2};
	
	//Test code: 
	
	
	// vector<int> vec{10,20,20}; //calling initializer list constructor. 
	//Need not to store data using vec.push_back().
	//we can create our own initializer list constructor
	class myclass
	//{
	vector<int>m_vec;
	public:
		myclass(const initializer_list<int>&v)
		{
			for(initializer_list<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr)
			{
				m_vec.push_back(*itr);
			}
		}

	};
	int main()
	{
		myclass v {1,2,3,4};
	}
	Use of initializer list: It is used when:
	1)	To initialize reference variable
	2)	To initialize const variable
	3)	When object of one class is created in other class (required, otherwise default constructor of that class is called and if that is not implemented then there will be an error). 
	Ex: 
	class A 
	{ 
		int i,j; 
	public: 
		A(int, int ); 
	}; 

	A::A(int arg1, int arg2) { 
		i = arg1; 
		j = arg2;
		cout << "A's Constructor called: Value of i: " << i << endl; 
	} 

	// Class B contains object of A 
	class B { 
		A a; 
	public: 
		B(int, int ); 
	}; 

	B::B(int x, int y): a(x, y){ //Initializer list must be used, otherwise it will try to call default constructor of class A.
		cout << "B's Constructor called"; 
	} 

	int main() { 
		B obj(10,20); 
		return 0; 
	}
	4)	To initialize the members of Base class.
	Ex:
	#include <iostream> 
	using namespace std; 

	class A { 
		int i; 
	public: 
		A(int ); 
	}; 

	A::A(int arg) { 
		i = arg; 
		cout << "A's Constructor called: Value of i: " << i << endl; 
	} 

	// Class B is derived from A 
	class B: A { 
	public: 
		B(int ); 
	}; 

	B::B(int x):A(x) { //Initializer list must be used 
		cout << "B's Constructor called"; 
	} 

	int main() { 
		B obj(10); 
		return 0; 
	}
	5)	To initialize base class data members if function parameter and data member are using same name.

	
	//Initialize member variables in initializer list in same order used in class.
