std::async: runs a function asynchronously (potentially on a separate thread) and returns a std::future to retrieve
the result.

#include <iostream>
#include <future>


    1. std::launch::async(Asynchronous Launch)
       Behavior: The function you pass to std::async is executed immediately in a separate thread.

        std::future::get() :  Calling.get() will block until the asynchronous operation(running on a separate thread)
        finishes and provides a result.

        The thread that executes the function is created and managed automatically by the C++ runtime, 
        and get() waits for the result from that thread.

    2. std::launch::deferred(Deferred Launch)
        Behavior: The function you pass to std::async does not execute immediately.Instead, it is deferredand will only
        be executed when you call.get() or .wait() on the std::future.

        std::future::get() :  Calling.get() will trigger the execution of the deferred task synchronously on the same thread that calls get().
        The computation is not asynchronous in this case — it runs synchronously in the calling thread only when get() is invoked.
    
    3.  std::future: is an object that acts as a placeholder for a result that will be computed asynchronously.

    //.get() retrieves the result and blocks if not ready.
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
