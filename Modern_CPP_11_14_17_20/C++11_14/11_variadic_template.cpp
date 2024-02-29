Variadic template: are class or function templates, that can take any variable(zero or more)
	number of arguments. In C++, templates can have a fixed number of parameters only that have to be specified
	at the time of declaration. However, variadic templates help to overcome this issue.
	/* Syntax
	template(typename arg, typename... args)
	return_type function_name(arg var1, args... var2)
	*/
	#include <iostream>
	using namespace std;

	// To handle base case of below recursive
	// Variadic function Template
	template <typename T>
	T add(T var1)
	{
		return var1;
	}

	// Variadic function Template that takes
	// variable number of arguments 
	template <typename T, typename... Types>
	T add(T var1, Types... var2)
	{
		return var1 + add(var2...);
	}

	// Driver code
	int main()
	{
		cout<<add(1, 2, 3, 4)<<endl;
		return 0;
	}

Internal working:
/* First instantiated from: insights.cpp:17 */
#ifdef INSIGHTS_USE_TEMPLATE
	template<>
	int add<int>(int var1)
	{
	  return var1;
	}
#endif

/* First instantiated from: insights.cpp:23 */
	#ifdef INSIGHTS_USE_TEMPLATE
	template<>
	int add<int, int, int, int>(int var1, int __var21, int __var22, int __var23)
	{
	  return var1 + add(__var21, __var22, __var23);
	}
	#endif
	
	
	/* First instantiated from: insights.cpp:17 */
	#ifdef INSIGHTS_USE_TEMPLATE
	template<>
	int add<int, int, int>(int var1, int __var21, int __var22)
	{
	  return var1 + add(__var21, __var22);
	}
	#endif
	
	
	/* First instantiated from: insights.cpp:17 */
	#ifdef INSIGHTS_USE_TEMPLATE
	template<>
	int add<int, int>(int var1, int __var21)
	{
	  return var1 + add(__var21);
	}
	#endif
	

	// Driver code
int main()
 {
   std::cout.operator<<(add(1, 2, 3, 4)).operator<<(std::endl);
   return 0;
 }
 
