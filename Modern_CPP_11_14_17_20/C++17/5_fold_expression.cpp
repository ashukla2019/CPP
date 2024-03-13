#include <iostream>
template<typename ... T>
auto sum(T ... t) 
{
	return (t + ...);
}
int main() 
{
  std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}

Internal working:
template<>
int sum<int, int, int, int, int, int, int, int, int, int>(int __t0, int __t1, int __t2, int __t3, int __t4, int __t5, int __t6, int __t7, int __t8, int __t9)
{
  return __t0 + (__t1 + (__t2 + (__t3 + (__t4 + (__t5 + (__t6 + (__t7 + (__t8 + __t9))))))));
}
#endif

int main()
{
  std::cout.operator<<(sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)).operator<<(std::endl);
  return 0;
}
----------------------------------------------------------------------------
auto sum(T ... t) 
{
	return (...+t);
}
int main() 
{
std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
}

template<>
int sum<int, int, int, int, int, int, int, int, int, int>(int __t0, int __t1, int __t2, int __t3, int __t4, int __t5, int __t6, int __t7, int __t8, int __t9)
{
  return ((((((((__t0 + __t1) + __t2) + __t3) + __t4) + __t5) + __t6) + __t7) + __t8) + __t9;
}
#endif

int main()
{
  std::cout.operator<<(sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)).operator<<(std::endl);
  return 0;
}
