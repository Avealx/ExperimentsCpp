/* Cache Thrashing by iteratind a matrix in column-first order
 *
 * motivation: example from C++ High Performance
 *
 * The idea is that if we have square matrix with a dimension as large as the
 * L1 data cache, this should lead to noticable performance differences when
 * traversing in row-first order, compared to column-first order. We did not
 * witness as dramatic differences as reported in the book and after
 * optimization the differences vanished completely. Nevertheless, it is
 * something to keep in mind.
 */
#include <array>
#include <chrono>
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------Misc
// Small class for crude benchmarking, see ScopedTimer.cpp
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

//--------------------------------------------------------------------------------

constexpr auto l1DataCacheSizeBytes = 32768; // Ubuntu: `getconf -a | gprep CACHE`
constexpr auto numElements = l1DataCacheSizeBytes / sizeof(int);
using Matrix = array<array<int, numElements>, numElements>;
static Matrix m;



auto fast(Matrix const & m) {
    ScopedTimer s{"fast"};
    int result = 0;
    for (auto row = 0; row < numElements; ++row)
        for (auto col = 0; col < numElements; ++col)
            result += m[row][col];
    return result;
}


auto slow(Matrix const & m) {
    ScopedTimer s{"slow"};
    int result = 0;
    for (auto col = 0; col < numElements; ++col)
        for (auto row = 0; row < numElements; ++row)
            result += m[row][col];
    return result;
}

int main() {
    for (auto col = 0; col < numElements; ++col)
        std::fill(begin(m[col]), end(m[col]), 1);

    fast(m);  // 268ms, -O3: 12ms
    slow(m);  // 341ms, -O3: 11ms
}
