/*
If constexpr statement:  C++17 introduces the constexpr keyword into the if statement,
allowing you to declare the condition of a constant expression in your code. Consider the following code:

#include <iostream>
template<typename T>
auto print_type_info(const T& t) 
{
  if constexpr (std::is_integral<T>::value) 
  {
    return t + 1;
  } 
  else 
  {
    return t + 0.001;
  }
}
int main() {
std::cout << print_type_info(5) << std::endl;
std::cout << print_type_info(3.14) << std::endl;
}

At compile time, the actual code will behave as follows:
int print_type_info(const int& t) 
{
return t + 1;
}
double print_type_info(const double& t) 
{
return t + 0.001;
}
int main() {
std::cout << print_type_info(5) << std::endl;
25
2.5 Templates CHAPTER 02: LANGUAGE USABILITY ENHANCEMENTS
std::cout << print_type_info(3.14) << std::endl;
}
*/
