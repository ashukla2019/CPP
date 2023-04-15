#include <iostream>
#include <thread>
using namespace std;

//Since x is shared variable b/w parent and child thread. We need to protect it using 
//mutex and condition variable: First x should be set in child context and should be read in parent
//context.

void func(int y, int& x)
{
    cout<<"y="<<y<<"\n";
    x = 20;
}

int main()
{
    int x;  
    thread t(func, 10, ref(x));
    t.join();
    cout<<"Main Thread\n";
    return 0;
}

//we can use standard library function async instead of thread.
//future represent objects where you can get something later. 
//can not call get more than once.

#include <iostream>
#include <thread>
#include <future>
using namespace std;

int func(int y)
{
    cout<<"Child Thread\n";
    return y*2;
}

int main()
{
    int x;  
    
    future<int> fu = async(launch::deferred, func, 10); //function will be executed in same thread.
	//future<int> fu = async(launch::async, func, 10); function will be executed in other thread.
	//future<int> fu = async(launch::async | launch::deferred, func, 10); function will be executed in other thread.
    x= fu.get(); //will wait until child thread finishes.
    cout<<"Main Thread\n";
    
    return 0;
}


//Use of Promise: pass value from parent thread to child thread, not at the time of
//creation of thread but later in future.

#include <iostream>
#include <thread>
#include <future>
using namespace std;

//since x is shared variable b/w parent and child thread. We need to protect it using 
//mutex and condition variable: First x should be set in child context and should be read in parent
//context.

int func(future<int>& f)
{
    int n = f.get();
    cout<<"Child Thread\n";
    return n;
}

int main()
{
    int x;  
    promise<int>p;
    future<int> f = p.get_future();
    future<int> fu = async(launch::async, func, ref(f)); 
    cout<<"Main Thread\n";
    p.set_value(24);
    x= fu.get(); 
    cout<<"value"<<x<<endl;
    return 0;
}