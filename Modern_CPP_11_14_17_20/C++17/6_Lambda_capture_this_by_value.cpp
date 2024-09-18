Lambda capture this by value
Capturing this in a lambda's environment was previously reference-only. An example of where this is problematic is asynchronous code using callbacks that require an object to be available, potentially past its lifetime. *this (C++17) will now make a copy of the current object, while this (C++11) continues to capture by reference.

// C++ Program to illustrate by value capture of *this 
// in lambda expressions 
#include <iostream> 
using namespace std;

class Counter {
public:
	Counter()
		: count(0)
	{
	}

	void Increment()
	{
		// Define a lambda that captures *this by value 
		auto incrementLambda = [this]() mutable {
			// Access the count member variable and 
			// increment it 
			count++;
		};

		// Call the lambda to perform the increment 
		incrementLambda();
	}

	int GetCount() const { return count; }

private:
	int count;
};

int main()
{
	// Create an instance of the Counter class 
	Counter counter;

	// Call the Increment method, which uses a lambda to 
	// increment the count 
	counter.Increment();
	counter.Increment();

	// Retrieve and print the updated count 
	cout << "Count: " << counter.GetCount() << endl;

	return 0;
}
