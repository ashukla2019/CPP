std::async: runs a function asynchronously (potentially on a separate thread) and returns a std::future to retrieve
the result.

#include <iostream>
#include <future>

//With std::launch::async:

//The function runs asynchronously in a separate thread.

//get() will block until the function completes.

//With std::launch::deferred:

//The function runs synchronously(on the calling thread) when get() is called.

//No separate thread is created.

//get() will block until the function finishes, but since it runs on the same thread, the blocking is just 
//waiting for the function to complete.

//std::future: is an object that acts as a placeholder for a result that will be computed asynchronously.

//.get() retrieves the resultand blocks if not ready.
//.wait() just blocks until ready(without retrieving the value).
//.valid() checks if the future still holds a result.

int compute() {
    return 42;
}

int main() {
    //launch::async forces it to run on a new thread.
    //std::future<int> result = std::async(std::launch::async, compute);
    //No force it to run on a new thread.
    //std::future<int> result = std::async(compute);
    //std::launch::deferred: delays execution until get() or wait() is called
    std::future<int> result = std::async(std::launch::deferred, compute);
    std::cout << "Result: " << result.get() << std::endl;
}


//std::promise is used to communicate data between threads.It allows one thread(the producer) to send a value or
//an exception to another thread(the consumer) through a std::future
