//lvalue and rvalue:
	//void printMe(int arg) { cout << "printMe(int arg): arg= " << arg; }
	void printMe(int & arg) { 
		cout << "[lvalue] :printMe(int & arg): arg= " << arg <<", &arg= "<<&arg<<"\n"; 
		arg = 500;
	}
	void printMe(int && arg) {
		cout << "[rvalue] :printMe(int && arg): arg= " << arg <<", &arg= " << &arg << "\n"; 
		arg = 600;
	}

	int main() {
		int i = 10; // i is l-value
		//int & i = 10; // error
		//int && i = 10; // i is a r-value reference

		//printMe(i); // l-value
		//printMe(i + 5); // r-value
		//printMe( std::move(i) ); // r-value reference overloaded
		printMe(200); // r-value

		cout << " Main: i= " << i << ", &i= " << &i << "\n";
	}


