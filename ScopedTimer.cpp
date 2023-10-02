/* A simple timer that can be used to measure the duration of a function.
 *
 * benchmarking, performance test
 *
 * motivation: C++ High Performance (taken from there)
 *
 * Compile using `g++ -DUSE_TIMER ScopedTimer.cpp`. One interesting aspect is
 * the use of `std::chrono::steady_clock` which guarantees incrementing values
 * on successive invocations of `now()`. Apparently the system cloch does not
 * guarantee such a thing, as it might be reset anytime.
 */
#include <iostream>
#include <chrono>
using namespace std;


#if USE_TIMER
#define MEASURE_FUNCTION() ScopedTimer timer{__func__}
#else
#define MEASURE_FUNCTION()
#endif


class ScopedTimer {
public:
    using ClockType = chrono::steady_clock;
    explicit ScopedTimer(char const * function_name)
        : function_name_{function_name}
        , start_{ClockType::now()} {}

    ScopedTimer(ScopedTimer const & ) = delete;
    ScopedTimer(ScopedTimer       &&) = delete;
    ScopedTimer& operator=(ScopedTimer const & ) = delete;
    ScopedTimer& operator=(ScopedTimer       &&) = delete;

    ~ScopedTimer() {
        using namespace std::chrono;
        auto const stop = ClockType::now();
        auto const duration = stop - start_;
        auto const us = duration_cast<microseconds>(duration).count();
        std::cout << us << "us " << function_name_ << '\n';
    }

private:
    char const * const function_name_;
    ClockType::time_point const start_;
};


void foo() {
    MEASURE_FUNCTION();
    cout << "Hello World!" << endl;
}


int main() {
    foo();
}
