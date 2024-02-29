/*
Mutex: Mutual Exclusion

RACE CONDITION:
0. Race condition is a situation where two or more threads/process happens to change a common data at the same time.
1. If there is a race condition then we have to protect it and the protected section is  called critical section/region.

MUTEX:
0. Mutex is used to avoid race condition.
1. We use lock() , unlock() on mutex to avoid race condition.

*/

//mutex_lock() is blocking call, it does not return anything.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int myAmount = 0;
mutex mymutex;

//Mutex lock is required to sync with expected result/behavior
void addMoney()
{
    mymutex.lock();
    for(int i=0; i<100000; i++)
    {
        myAmount+= 10;            //critical region/section
    }
    mymutex.unlock();
}

int main()
{
    std::thread t1(addMoney);
    std::thread t2(addMoney);
    t1.join();
    t2.join();
    cout<<"Amount="<<myAmount<<"\n";
    return 0;
}

//lock_guard: When a lock_guard object is created, it attempts to take ownership of the mutex it is given. 
//When control leaves the scope in which the lock_guard object was created, 
//the lock_guard is destructed and the mutex is released.
//The lock_guard class is non-copyable.
//while applying mutex.lock() and unlock, it might happen code crashes after applying
//mutex lock and then no other thread will get chance to execute critical section.
//solution is lock_guard.
void addMoney()
{
    std::lock_guard<std::mutex> lock(mymutex); //will create lock_guard and initialize mutex variable.
    for(int i=0; i<100000; i++)
    {
        myAmount+= 10;            //critical region/section
    }
    
}
int main()
{
    std::thread t1(addMoney);
    std::thread t2(addMoney);
    t1.join();
    t2.join();
    cout<<"Amount="<<myAmount<<"\n";
    return 0;
}

/*try_lock(): unblocking call, if it fails to acquire lock, will return false.
0. try_lock() Tries to lock the mutex. Returns immediately. On successful lock 
   acquisition returns true otherwise returns false.
1. If try_lock() is not able to lock mutex, then it doesn't get blocked that's why
   it is called non-blocking.
2. If try_lock is called again by the same thread which owns the mutex, the behavior 
   is undefined. It is a dead lock situation with undefined behavior. 
   (if you want to be able to lock the same mutex by same thread more than one 
   time the go for recursive_mutex)
*/
void addMoney()
{
   
    for(int i=0; i<100000; i++)
    {
		if(mymutex.try_lock(){
			myAmount+= 10; 			//critical region/section
		}
		mymutex.unlck();
    }
    
}
int main()
{
    std::thread t1(addMoney);
    std::thread t2(addMoney);
    t1.join();
    t2.join();
    cout<<"Amount="<<myAmount<<"\n";
    return 0;
}
