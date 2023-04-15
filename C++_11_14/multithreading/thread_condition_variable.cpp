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
mutex mutex_balance;
condition_variable cv;

void withdrawMoney(int money)
{
    unique_lock<mutex>ul(mutex_balance);
    cv.wait(ul, []{return (balance !=0) ? true: false;});
    if(balance >= money)
    {
        balance-=money;
        cout<<"Amount deducted and current balance"<<balance;
    }
    else
    {
        cout<<"Amount is not sufficient\n";
    }
}

void addMoney(int money)
{
    lock_guard<mutex>lg(mutex_balance);
    balance+= money;
    cout<<"Current balance:"<<balance;
    cv.notify_one();
}

int main()
{
    thread t1(withdrawMoney, 500);
    thread t2(addMoney, 500);
    t1.join();
    t2.join();
    return 0;
}