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

------------------------------------------------------------------------------------------------  
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

class SharedBuffer {
public:
    SharedBuffer(size_t size) : buffer(size), write_pos(0), read_pos(0), count(0) {}

    void write(char c) {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout<<"count="<<count<<" "<<"buffer.size()" <<buffer.size()<<"\n";
        // Wait until buffer has space
        cv.wait(lock, [this]() { return count < buffer.size(); });

        buffer[write_pos] = c;
        write_pos = (write_pos + 1) % buffer.size();
        ++count;

        // Notify reader
        cv.notify_all();
    }

    char read() {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait until buffer has data
        std::cout<<"count="<<count<<"\n";
        cv.wait(lock, [this]() { return count > 0; });

        char c = buffer[read_pos];
        read_pos = (read_pos + 1) % buffer.size();
        --count;

        // Notify writer
        cv.notify_all();

        return c;
    }

private:
    std::vector<char> buffer;
    size_t write_pos;
    size_t read_pos;
    size_t count;

    std::mutex mtx;
    std::condition_variable cv;
};

void writer(SharedBuffer& buf) {
    std::string data = "Hello from writer!";
    for (char c : data) {
        buf.write(c);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void reader(SharedBuffer& buf) {
    for (int i = 0; i < 18; ++i) {  // 18 chars in "Hello from writer!"
        char c = buf.read();
        std::cout << c;
        std::cout.flush();
    }
    std::cout << std::endl;
}

int main() {
    SharedBuffer buffer(5);  // buffer size 5

    std::thread writer_thread(writer, std::ref(buffer));
    std::thread reader_thread(reader, std::ref(buffer));

    writer_thread.join();
    reader_thread.join();

    return 0;
}
-------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void waitForSignal() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Waiting for signal...\n";
    cv.wait(lock, [] { return ready; });  // Wait until ready becomes true
    std::cout << "Received signal! Proceeding...\n";
}

void sendSignal() {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "Sending signal.\n";
    }
    cv.notify_one();  // Wake up one waiting thread
}

int main() {
    std::thread t1(waitForSignal);
    std::thread t2(sendSignal);

    t1.join();
    t2.join();

    return 0;
}
