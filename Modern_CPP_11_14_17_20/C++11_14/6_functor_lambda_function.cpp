/*Functors: Calling object using parenthesis like function call. 
One advantage of functors over function pointers is that they can hold state. 
Since this state is held by the instance of the object it can be thread safe 
(unlike static variables inside functions used with function pointers). 
The state of a functor can be initialized at construction.

function pointer can not have additional value/state:
*/
void print(int val)
{
    cout << "val:" << val << endl;
}

class printVal
{
    int val;
public:
    printVal() = default;
    printVal(int val):val(val){}
    void operator()(int x) {
        if (x > val)
            cout << "value greater than default set value" << x << endl;
    }
};


int main()
{
    vector<int>vec{ 10, 20, 30, 40 };
    //using function pointer
    void (*func_ptr)(int) = &print;
    for_each(vec.begin(), vec.end(), func_ptr);
    //Using normal function
    for_each(vec.begin(), vec.end(), print);
    //We can not pass additional variable or state using function or function pointer
    //we should functor:
    printVal p(10);
    for_each(vec.begin(), vec.end(), p);
    return 0;
}

--------------------------------------------------------------
Lambda function: C++ Lambda expression allows us to define anonymous function objects (functors) which can 
either be used inline or passed as an argument.	
syntax: []()<mutable> <exception> <constexpr> <return_type>
	{
	
	}
	If mutable/exception/constexpr specification used, Parameter list () becomes mandatory.

Capture Clause (Lambda Introducer)
Lambdas can capture (copy) local variable of surrounding space. We can capture local variables by value or by reference.

Capturing a variable by value

int variable = 10;
[variable] () {
      /* we can read(use) 'variable' value but can't change it. Read full article to know how we can change 'variable' value. 
      */
} 
Capturing all variable present in local scope by value

int variable1 = 10;
int variable2 = 20;
[=] () {
      /* we can read(use) 'variable1' and 'variable2' values but can't change it. Read full article to know how we can change 'variable1' and 'variable2' value. 
      */
}
We can use global/static variables inside lambda without capturing them. Capturing of global/static variables is an error.

Capturing a variable by reference

int variable = 10;
[&variable] () {
      /* we can read/modify 'variable' value. Any change in 'variable' value will be reflected outside of lambdas scope. 
      */
}
Capturing all variable by reference

int variable1 = 10;
int variable2 = 20;
[&] () {
       /* we can read/modify 'variable1' and 'variable2' values. Any    change in 'variable1' and 'variable2' values will be reflected   outside of lambda scope. 
       */
}
2. Parameter List (Lambda Declarator) (Optional*)

Parameter list is a simple list which we write while declaring a normal function

Like function

fun(int variable1, int variable2)
we can write parameter list with lambda

[] (int variable1, int variable2) {
     /* we can use variable1, variable2 in similar manner like we do in a normal function. 
     */
}
*If mutable/exception/constexpr specification used, Parameter list ( ) becomes mandatory.

3.mutable specification (Optional)

By default we can not change variable captured by value 
(because internally lambda is implemented through function object having const function call operator 
overloaded, and we can not change class variable in const functions) but with mutable keyword we can 
change variables which are captured by value. Please note any change in captured by value variable will 
not be reflected outside of lambda in contrary any change in captured by reference variable will be 
reflected outside of lambda.
 // function object implementation using Overloaded const function call operator
    void operator()(int value) const {
        std::cout << value << " ";
    }

int variable = 10;
[variable] () mutable { 
     variable++;
     // 'variable' value is 11 inside lambda
} ();
// 'variable' value is still 10 outside of lambda 
Notice a () after lambda, It is used to call lambda function like in case of normal function. It should take argument if your lambda function is taking some argument in parameter list.

4.exception specification (Optional)

We can specify exception specification like ‘noexcept’ with lambda.

5.constexpr specification (C++17 feature) (Optional)

In C++ 17 , constexpr specification is added with lambda. In general compiler detect that lambda function is qualified to be a constexpr and evaluate it at compile time.

[] () noexcept { 
   // Code which doesn't throw exception 
}
6.Return type (->return_type) (Optional)

We can also specify return with lambda , This is called trailing return type syntax. It is not mandatory in general by when you have multiple return statement inside lambda and they are returning different data types, it become mandatory as compiler can not deduce actual return type from lambda body.

int i = [] () -> int { 
    if (some_condition()) 
        return 1;
    else 
        return 3.4;
}
7. Lambda body

Lambda body is same as normal function body, It is a description what lambda function does.

Usage of lambda
Be more expressive
Conditional initialization of a const variable

Old code : (Will not compile)

bool gSomeCondition(int x) 
{
    if (x==0)
        return true;
    else
        return false;
}
int main () 
{
    const std::string lStr = "foo";
    if (gSomeCondition(0))
        lStr = "bar"; // Error we can not change const variable.
        /* code */
}
Code with lambda :

bool gSomeCondition(int x) 
{
    if (x==0)
        return true;
    else
        return false;
}

int main () 
{
    const std::string lStr = [] () {
        if (gSomeCondition(0))
            return "bar";
        else 
            return "foo";
    } ();
}
Improved Locality/Readability
Old code : Reverse Sort

class Compare
{
    public: 
    bool operator() (const int &x, const int &y) const 
    {
        return x > y;
    }
} CompareObj;
/* 
 Code...
*/
void reverse_sort() 
{
    std::vector<int> lVec = {3,6,1,10,31,54,22,37};
    std::sort(lVec.begin(), lVec.end(), CompareObj);
}
New Code with lambda:

void reverse_sort_with_lambda() 
{
 std::vector<int> lVec = {3,6,1,10,31,54,22,37};
 std::sort(lVec.begin(), lVec.end(), [] (const int &x, const int &y)
                                            { return  x > y;});
}
Reducing boilerplate code
class Compare
{
    public: 
    bool operator() (const int &x, const int &y) const 
    {
        return x > y;
    }
} CompareObj;
In above code only following code is useful for us and describe our complete intention.

(const int &x, const int &y) const 
{
        return x > y;
}
So in a way lambda is reducing boilerplate code which is not useful/relevant for us.

Reducing global namespace pollution
In general when we use function object with any std algorithm, we write struct/class in a global namespace. It increases global namespace pollution inside the code and lambda help us in reducing this pollution as we don’t need to write anything in global namespace while using lambda.

Storing Lambda
We don’t know actual type of lambda but we can use ‘auto’ keyword to store lambdas.

auto lambda = [] () {
// Code
};
lambda();
Passing lambda as a parameter
We can use std::function (#include <functional>) to store and pass lambda as a function parameter. Lambda can also deduce to a function pointer if NO capture clause is specified.

std::function<void(void)> fun = [] () { 
// Code
};
void(*fn)(void) = [] () {
// Code
};
Copy a lambda
We can copy a lambda if it doesn’t contains any non-copyable object inside capture clause.

Generalize capture
In C++14, a new concept of generalize capture is introduced. Now we can initialize a variable in capture clause

int main () 
{
    int x = 0;
    int y = 10;
    // auto z = x + y;
    [z=x+y] () {
        std::cout<<z<<std::endl;
    } ();
}
In above code z will be available inside lambda only.

This is important when we want to restrict usage of some variable inside lambda only and it make our code less error prone.

Mutable Lambda
Capture by value variables are not allowed to change inside lambda.Mutable lambda can change value of variable even if it was captured by value but this value change will not be reflected outside of lambda. mutable keyword is just removing ‘constness’ of function call operator internally implemented by compiler.

int main () 
{
    int x = 0;
    auto f = [x] () mutable {
        x++;
        std::cout<<x<<std::endl;
    };
    f();
    std::cout<<x<<std::endl;
}
Output 
1
0
Capturing this pointer
Even if we capture this pointer by value , we can change class member variable.

class foo
{
    int x = 0;
    public: 
    void fun() 
    {
        [this] () {
            x++;  // class variable x has changed 
        } ();
    }
};
Capturing *this (C++17)
Problem with capturing this pointer is described by following code —

class foo
{
    int x = 0;
    public: 
    void fun() 
    {
        [=] () {
            x++;   // By mistake I can modify class variable  
        } ();
    }
};
Capturing ‘this’ by default with default value capture [=] is dangerous and error prone so above syntax is deprecated in C++17 and a new concept capturing *this is provided.

Now

class foo
{
    int x = 0;
    public: 
    void fun() 
    {
        [*this] () {
            x++; // ERROR , Because its a non mutable lambda  
        } ();
    }
};
We need to write ‘mutable’ to make non-const lambda

class foo
{
    int x = 0;
    public: 
    void fun() 
    {
        [*this] () mutable {
            x++; // OK    
        } ();
    }
};
Now we need to be more explicit while changing class variable value inside lambda and this makes lambda less error prone.

Generic Lambda (C++14 …)
We can use ‘auto’ as parameter argument while writing lambda. Its like template parameter with lambda.

auto f = [] (auto var) {
std::cout<<var;
};
f(1);
f("String");
Variadic template is supported with lambda.(C++20)

int main () 
{
    auto f = [] (auto... args)
    {
        fun(args...);
    };

    auto ft = [] <typename ... param> (param... args)
    {
        fun(args...);
    };
}
With template lambda has all type of braces available in c++.

Lambda Journey
C++11
[]() specifiers exception attr -> ret { /*code; */ }
C++14
High level syntax hasn’t changed but capture clause allows you to perform capture with initializer
const auto foo = [z = x + y]() { std::cout << z << ‘\n’; };
Compiler now can creates member variable from closure type from expression.
Generic lambda support (glambda)
auto foo = [] (auto x, auto y) {/*…*/};
C++17
constexpr specifier is allowed
Capture of *this
C++20
Support for variadic template
