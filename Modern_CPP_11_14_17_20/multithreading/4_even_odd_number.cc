#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // Mutex to ensure thread-safe access

// Function to print even numbers
void printEven(int& current) {
    while (current <= 20) {
        mtx.lock();  // Lock to ensure mutual exclusion
        if (current % 2 == 0) {
            std::cout << "even"<<current << " ";
            current++;
        }
        mtx.unlock();  // Unlock after printing
    }
}

// Function to print odd numbers
void printOdd(int& current) {
    while (current <= 20) {
        mtx.lock();  // Lock to ensure mutual exclusion
        if (current % 2 != 0) {
            std::cout << "odd" <<current << " ";
            current++;
        }
        mtx.unlock();  // Unlock after printing
    }
}

int main() {
    int current = 1;  // Start from 1
    std::thread t1(printEven, std::ref(current));  // Thread for even numbers
    std::thread t2(printOdd, std::ref(current));   // Thread for odd numbers

    t1.join();  // Wait for the even number thread to finish
    t2.join();  // Wait for the odd number thread to finish

    std::cout << std::endl;
    return 0;
}

What is does:
Both threads constantly run and acquire the mutex.
If it's not their turn (e.g., even thread sees an odd number), they just skip and loop again.
This leads to busy-waiting: CPU cycles are wasted checking conditions rapidly.
It can also lead to thread starvation or contention, especially under high CPU load.
--------------------------------------------------------------------------------------------------------------------------------------  
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mt;
condition_variable cv;

bool isOddTurn = true;  // Start with odd number

void printOdd(int& x)
{
    while (x < 50)
    {
        unique_lock<mutex> lock(mt);
        cv.wait(lock, [&]() { return x % 2 != 0; });  // Wait for odd turn

        if (x >= 50) break;  // Re-check condition after wakeup

        cout << "Number printed by odd thread: " << x << endl;
        x++;
        cv.notify_all();  // Notify other thread
    }
}

void printEven(int& x)
{
    while (x < 50)
    {
        unique_lock<mutex> lock(mt);
        cv.wait(lock, [&]() { return x % 2 == 0; });  // Wait for even turn

        if (x >= 50) break;  // Re-check condition after wakeup

        cout << "Number printed by even thread: " << x << endl;
        x++;
        cv.notify_all();  // Notify other thread
    }
}

int main()
{
    int var = 1;
    thread odd(printOdd, std::ref(var));
    thread even(printEven, std::ref(var));

    odd.join();
    even.join();

    return 0;
}
❌ Without condition variable: Both are yelling "Is it my turn?!" repeatedly, wasting energy.
✅ With condition variable: One person speaks, then says "Now it's your turn", and waits quietly.
