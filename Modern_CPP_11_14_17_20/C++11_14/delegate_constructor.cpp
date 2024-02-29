Delegate constructors: 
C++11 introduces the concept of a delegate construct, which allows a constructor to call another
constructor in a constructor in the same class, thus simplifying the code:

#include <iostream>
class Base {
public:
int value1;
int value2;
Base() {
value1 = 1;
}

Base(int value) : Base() { // delegate Base() constructor
value2 = value;
}
};

int main()
{
Base b(2);
std::cout << b.value1 << std::endl;
std::cout << b.value2 << std::endl;
}
