/*
Aggregate can have public base classes
Initialization with nested {} possible

sample code:
template <typename T>
strcut S: std::string, std::complex<T> //publicly inheriting string and complex class
{
	std::string data;
}
int main()
{
	S<float>s{{"hello"}, {1.2, 3.2}, "world"}; //string and complex class is initialized with {}
	return 0;
}


*/

//C++11 introduced uniform initialization:
//uniform initilaization will do aggregate initialization
//Aggregate initialization supports only if class/structure does not have 
//private members, no base class, virtual function etc. if we introduce base class for
//struct s, it will not work with C++14

struct s 
{
	int i;
	float f;
};

int main()
{
	s s1{10. 2.3}; //aggregate initialization
	return 0;
}

//problem: Aggregate initialization will fail due to base class. It will look for 
//constructor of base class to initialize members.
struct B
{
	int a;
};
struct s : B
{
	int i;
	float f;
};

int main()
{
	s s1{10. 2.3}; //aggregate initialization
	return 0;
}

//Solution:
struct B
{
	int a;
};
struct s : B
{
	int i;
	float f;
};

int main()
{
	s s1{{1},10. 2.3}; //extended aggregate initialization {1} to initialize B::a
	return 0;
}

//Example:

template<typename T>
struct D: std::string, std::complex<T>
{
	std::string data;
}

int main()
{
	D<float>s{"Hello", {1.2, 3.2}, "Bye"};	
	return 0;
}
