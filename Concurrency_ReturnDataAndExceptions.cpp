/* Concurrently execute a task, retrieve the return value and possible errors.
 *
 * concurrency, parallel, task, packaged_task, async, promise, future
 *
 * motivation: taken from `C++ High Performance`
 *
 * We have a task that should compute a value concurrently and that might throw
 * an exception.  We show three alternatives that progress in their level of
 * abstraction:
 * 1. Using std::promises explicitly, this is the most verbose alternative
 *    and requires us to make the promise explicit in the task
 *    implementation and the spawning of the thread explicit when setting up
 *    the execution.
 * 2. Using std::packaged_task which hides away the promise and enables us to
 *    ignore the concurrency issue in the implementation of the task.
 * 3. Using std::async which additionally hides away the explicit creation of
 *    the thread.
 */

#include <iostream>
#include <future>
#include <thread>

// alternative 1: use promises explicitly.
// Requires making the promise explicit in the function that is to be computed
// concurrently.
auto divide_1(int a, int b, std::promise<int> & p) {
    if (b == 0) p.set_exception(std::make_exception_ptr(std::runtime_error{"divide by 0"}));
    else        p.set_value(a / b);
}

// alternative 2: use std::packaged_task.
// alternative 3: use std::async.
// Hides the explicit use of promises. The function that is to be computed
// concurrently can be implemented as for the single-threaded case.
auto divide_2(int a, int b) {
    if (b == 0)
        throw std::runtime_error{"dived by 0"};
    return a / b;
}


int main() {
    // alternative 1: use explicit std::promise
    {
        auto p = std::promise<int>{};
        // std::thread(divide_1, 45, 0, std::ref(p)).detach();  // exceptional case
        std::thread(divide_1, 45, 5, std::ref(p)).detach();
        auto f = p.get_future();

        try {
            const auto & result = f.get();  // blocking
            std::cout << "alternative 1 result: " << result << '\n';
        }
        catch (std::exception const & e) {
            std::cout << "exception: " << e.what() << '\n';
        }
    }

    // alternative 2: use std::packaged_task
    {
        auto task = std::packaged_task<decltype(divide_2)>{divide_2};
        auto f = task.get_future();
        // std::thread(std::move(task), 45, 0).detach();  // exceptional case
        std::thread(std::move(task), 45, 5).detach();

        try {
            const auto & result = f.get();  // blocking
            std::cout << "alternative 2 result: " << result << '\n';
        }
        catch (std::exception const & e) {
            std::cout << "exception: " << e.what() << '\n';
        }
    }

    // alternative 3: use std::async
    {
        auto f = std::async(divide_2, 45, 5);  // exceptional case
        // auto f = std::async(divide_2, 45, 0);

        try {
            const auto & result = f.get();  // blocking
            std::cout << "alternative 3 result: " << result << '\n';
        }
        catch (std::exception const & e) {
            std::cout << "exception: " << e.what() << '\n';
        }
    }

}
