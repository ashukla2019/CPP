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

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker_thread() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Worker: Waiting for signal...\n";

    // Wait until "ready" becomes true
    cv.wait(lock, [] { return ready; });

    std::cout << "Worker: Received signal, proceeding...\n";
}

void signal_thread() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "Signal: Setting ready = true and notifying.\n";
    }
    cv.notify_one();
}

int main() {
    std::thread t1(worker_thread);
    std::thread t2(signal_thread);

    t1.join();
    t2.join();

    return 0;
}
