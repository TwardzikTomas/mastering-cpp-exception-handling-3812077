#include <iostream>
#include <thread>
#include <vector>
#include <stdexcept>
#include <typeinfo>
#include <cerrno>
#include <cstring>

void threadFunction(int id)
{
    // Simulate a task that might throw an exception
    if (id % 2 == 0)
    { // Threads with even IDs throw an exception
        throw std::runtime_error("Exception from thread " + std::to_string(id));
    }
}

int main()
{
    std::set_terminate([]() -> void
                       {
        std::cerr << "Unhandled exception caught: ";

        try{
            std::rethrow_exception(std::current_exception());
        }
        catch (const std::exception & e){
            std::cerr << "Exception type: " << typeid(e).name() << ", description: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unknown or non-standard exception caught." << std::endl;
        }
        std::cerr << "System errno: " << errno << " (" << std::strerror(errno) << ")." << std::endl;
        std::abort(); });
    const int numThreads = 4;
    std::vector<std::thread> threads;

    // Spawn threads
    for (int i = 0; i < numThreads; ++i)
    {
        threads.emplace_back(threadFunction, i);
    }

    // Join threads
    for (auto &th : threads)
    {
        th.join();
    }

    std::cout << "All threads have completed." << std::endl;

    return 0;
}