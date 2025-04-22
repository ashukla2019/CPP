/*
NOTES:
1. Condition variables allow us to synchronize threads via notifications.
   a. notify_one();
   b. notify_all();
2. You need mutex to use condition variable
3. Condition variable is used to synchronize two or more threads.
4. Best use case of condition variable is Producer/Consumer problem.
5. Condition variables can be used for two purposes:
    a. Notify other threads
    b. Wait for some condition
*/
	
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

int balance = 0;
mutex mt;
condition_variable cv;

void increment()
{
	//lock_guard<mutex>lg(mt);
	unique_lock<mutex>ul(mt);
	for (int i = 1; i < 50; i++)
	{
		balance = balance + i;
		cout << "balance after increment is=" << balance << endl;
	}
	cv.notify_one();
}

void decrement()
{
	//lock_guard<mutex>lg(mt);
	unique_lock<mutex>ul(mt);
	cv.wait(ul, [] { return balance > 0; });
	for (int i = 1; i < 50; i++)
	{
		balance = balance - i;
		cout << "balance after decrement is=" << balance << endl;
	}
}

int main()
{
	thread t1(decrement);
	thread t2(increment);
	t1.join();
	t2.join();

	return 0;

}
