#include<iostream>
#include <string>

std::string checkTypeOfString(std::string s)
{
	bool isdigit = false;
	bool isAlphabet = false;
	for (auto ch : s)
	{   
		if (ch == '.')
			return "float";
		else if ((ch > 'A' && ch < 'Z') || (ch > 'a' && ch < 'z') )
		{
			isAlphabet = true;
		}
		else if (ch > '0' && ch < '9')
		{
			isdigit = true;
		}
	}
	if(isAlphabet && isdigit)
		return "Alphanumeric";
	else if(isAlphabet)
		return "Alphabet";
	else
		return "Numeric";
}

int main()
{
	std::string str("ABC12");
		
	std::string ret = checkTypeOfString(str);
	std::cout << "Type is:" << ret << std::endl;
		
	return 0;
}
