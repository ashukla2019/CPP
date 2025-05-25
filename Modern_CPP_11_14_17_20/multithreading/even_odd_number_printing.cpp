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
