//Two threads printing even and odd number
#include <iostream>
#include <thread>

int count = 1;

void PrintOdd()
{
    for(; count < 50;)
    {
        std::cout << "From Odd:    " << count << std::endl;
        count++;
    }
}

void PrintEven()
{
    for(; count < 50;)
    {
        std::cout << "From Even: " << count << std::endl;
        count++;
    }
}

int main()
{
    std::thread t1(PrintOdd);
    std::thread t2(PrintEven);
    t1.join();
    t2.join();
    return 0;
}
Output:
From Odd:    From Even: 11

From Odd:    2
From Odd:    3
From Odd:    4
From Odd:    5
From Odd:    6
From Odd:    7
From Odd:    8
From Odd:    9
From Odd:    From Even: 11
From Even: 12
From Even: 13
From Even: 14
10From Even: 
From Odd:    16
From Odd:    17
From Odd:    18
From Odd:    19
15From Odd:    
From Even: 21
From Even: 22
From Even: 23
From Even: 24
From Even: 25
From Even: 26
From Even: 27
20From Even: 
From Odd:    29
From Odd:    30
From Odd:    31
From Odd:    32
From Odd:    33
28From Odd:    34
From Odd:    35
From Odd:    36
From Odd:    37
From Odd:    38

From Odd:    39
From Odd:    40
From Odd:    41
From Odd:    42
From Odd:    43
From Odd:    44
From Odd:    46
From Odd:    47
From Odd:    48
From Odd:    49
From Even: 50

//There is no sycnchronization and we can use mutex lock for synchronization    
//Using mutex:
    #include <iostream>
#include <thread>
#include <mutex>

std::mutex mu;

int count = 1;

void PrintOdd()
{
    for(; count < 50;)
    {
        std::unique_lock<std::mutex> locker(mu);
        std::cout << "From Odd:    " << count << std::endl;
        count++;
        locker.unlock();
    }

}

void PrintEven()
{
    for(; count < 50;)
    {
        std::unique_lock<std::mutex> locker(mu);
        std::cout << "From Even: " << count << std::endl;
        count++;
        locker.unlock();
    }
}

int main()
{
    std::thread t1(PrintOdd);
    std::thread t2(PrintEven);
    t1.join();
    t2.join();
    return 0;
}
Output:
From Odd:    1
From Odd:    2
From Odd:    3
From Odd:    4
From Odd:    5
From Odd:    6
From Odd:    7
From Odd:    8
From Odd:    9
From Odd:    10
From Odd:    11
From Odd:    12
From Odd:    13
From Odd:    14
From Odd:    15
From Odd:    16
From Odd:    17
From Odd:    18
From Odd:    19
From Odd:    20
From Odd:    21
From Odd:    22
From Odd:    23
From Odd:    24
From Odd:    25
From Odd:    26
From Odd:    27
From Odd:    28
From Odd:    29
From Odd:    30
From Odd:    31
From Odd:    32
From Odd:    33
From Odd:    34
From Odd:    35
From Odd:    36
From Odd:    37
From Odd:    38
From Odd:    39
From Odd:    40
From Odd:    41
From Odd:    42
From Odd:    43
From Odd:    44
From Odd:    45
From Odd:    46
From Odd:    47
From Odd:    48
From Odd:    49
------------------------------------------------------------------------------
//We want parallel execution of two threads: odd thread should print odd and even should print
//even number in order:

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mu;
std::condition_variable cond;
int count = 1;

void PrintOdd()
{
    for(; count < 100;)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker,[](){ return (count%2 == 1); });
        std::cout << "From Odd:    " << count << std::endl;
        count++;
        locker.unlock();
        cond.notify_all();
    }

}

void PrintEven()
{
    for(; count < 100;)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker,[](){ return (count%2 == 0); });
        std::cout << "From Even: " << count << std::endl;
        count++;
        locker.unlock();
        cond.notify_all();
    }
}

int main()
{
    std::thread t1(PrintOdd);
    std::thread t2(PrintEven);
    t1.join();
    t2.join();
    return 0;
}
