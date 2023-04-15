//Constexpr: By specifying constexpr, we suggest compiler to evaluate value at compile time. 
int gfun() { return 4;}

int main()
{
	int arr[gfun()]; //error: function call must have constant value....
	return 0;
}
solution is constexpr:
constexpr int gfun() { return 4;}

int main()
{
	int arr[gfun()]; //error: function call must have constant value....
	return 0;
}
	
1)constexpr variables: The primary difference between const and constexpr variables is that the 
initialization of a const variable can be deferred until run time. A constexpr variable must 
be initialized at compile time.
constexpr float x = 42.0;
constexpr float y{108};
constexpr float z = exp(5, 3);
2)constexpr functions:A constexpr function is one whose return value is computable at compile time 
when consuming code requires it.
constexpr int product(int x, int y) 
{ 
	return (x * y); 
} 
int main() 
{ 
	const int x = product(10, 20); 
	cout << x; 
	return 0; 
} 

