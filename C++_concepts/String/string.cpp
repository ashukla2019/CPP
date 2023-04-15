typedef basic_string<char> string;

Member functions
(constructor)			Construct string object (public member function)
(destructor)			String destructor (public member function)
operator=				String assignment (public member function)

Iterators:
begin					Return iterator to beginning (public member function)
end						Return iterator to end (public member function)
rbegin					Return reverse iterator to reverse beginning (public member function)
rend					Return reverse iterator to reverse end (public member function)
cbegin					Return const_iterator to beginning (public member function)
cend					Return const_iterator to end (public member function)
crbegin					Return const_reverse_iterator to reverse beginning (public member function)
crend					Return const_reverse_iterator to reverse end (public member function)

Capacity:
size					Return length of string (public member function)
length					Return length of string (public member function)
max_size				Return maximum size of string (public member function)
resize					Resize string (public member function)
capacity				Return size of allocated storage (public member function)
reserve					Request a change in capacity (public member function)
clear					Clear string (public member function)
empty					Test if string is empty (public member function)
shrink_to_fit			Shrink to fit (public member function)

Element access:
operator[]				Get character of string (public member function)
at						Get character in string (public member function)
back					Access last character (public member function)
front					Access first character (public member function)

Modifiers:
operator+=				Append to string (public member function)
append					Append to string (public member function)
push_back				Append character to string (public member function)
assign					Assign content to string (public member function)
insert					Insert into string (public member function)
erase					Erase characters from string (public member function)
replace					Replace portion of string (public member function)
swap					Swap string values (public member function)
pop_back				Delete last character (public member function)

String operations:
c_str					Get C string equivalent (public member function)
data					Get string data (public member function)
get_allocator			Get allocator (public member function)
copy					Copy sequence of characters from string (public member function)
find					Find content in string (public member function)
rfind					Find last occurrence of content in string (public member function)
find_first_of			Find character in string (public member function)
find_last_of			Find character in string from the end (public member function)
find_first_not_of		Find absence of character in string (public member function)
find_last_not_of		Find non-matching character in string from the end (public member function)
substr					Generate substring (public member function)
compare					Compare strings (public member function)

Member constants
npos					Maximum value for size_t (public static member constant)

Non-member function overloads
operator+				Concatenate strings (function)
relational operators	Relational operators for string (function)
swap					Exchanges the values of two strings (function)
operator>>				Extract string from stream (function)
operator<<				Insert string into stream (function)
getline					Get line from stream into string (function)

int main()
{
	//String initialization:
	char text[21] = "goodbye";
	string s1;               // Create an empty C++ string of length 0, equal to "" (default constructor)
	string s2("hello");      // Initialize string with C string literal
    string s3 = "hello";     // Initialize string with C string literal
	string s4(text);         // Initialize string with char array that contains a C string
	string s5 = text;        // Initialize string with char array that contains a C string
	string s6(s2);           // Initialize string with another C++ string (copy constructor)
	string s7 = s2;          // Initialize string with another C++ string (copy constructor)
	
	//Subscripting:The subscript operator may be used to access the individual characters of a C++ string:
	cout << s3[1] << endl;  // Prints the character 'e', the second character in the string "Hello"
	
	//String Length:You can obtain the length of a C++ string using the string class member functions length() or size().
	//Both of the methods return the data type size_t
	string s = "Some text";
	cout << "String length is " << s.length() << endl;     // Length is 9
	
	//String Comparisons:
	if (s1 > s2)         // Compare two C++ strings
	{
		...
	}

	if ("cat" == s2)     // Compare C string literal and C++ string
	{
		...
	}

	if (s3 != cstr)      // Compare C++ string and array that contains a C string
	{
		...
	}
	//Assignment:
	string s1 = "original string";
	string s2 = "new string";
	char s3[20] = "another string";
	s1 = s2;                       // s1 changed to "new string"
	s1 = s3;                       // s1 changed to "another string"
	s1 = "yet another string";     // s1 changed to "yet another string"
	
	//Concatenation:
	string s1 = "Hello";
	string s2 = " good ";
	char s3[10] = "friend";

	s1 = s1 + ", my " + s2 + s3;     // s1 now contains "Hello, my good friend"
	return 0;
}