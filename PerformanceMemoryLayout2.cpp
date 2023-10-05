/* Performance differences due to different sizes
 *
 * motivation: example from C++ High Performance
 *
 * We create two different types with different sizes, Small and Big. Iterating
 * over vectors of these shows dramatic performance degradation of the Big
 * object due to less effective cache usage.
 */
#include <array>
#include <numeric>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

//----------------------------------------------------------------------------Misc
// Small class for crude benchmarking, see ScopedTimer.cpp
class ScopedTimer {
public:
    using ClockType = chrono::steady_clock;
    explicit ScopedTimer(string const function_name)
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
    string const function_name_;
    ClockType::time_point const start_;
};

//--------------------------------------------------------------------------------

struct Small {
    array<char,4> data{};
    int score{rand()};
};

struct Big {
    array<char,256> data{};
    int score{rand()};
};

//--------------------retrieve names of the types `Small`, `Big`
template <class T> struct Name;

template <> struct Name<Small>{ static string const value; };
string const Name<Small>::value{"Small"};

template <> struct Name<Big>{ static string const value; };
string const Name<Big>::value{"Big"};


template <typename T>
auto sum_scores(vector<T> const & arr) {
    ScopedTimer t{"summing " + Name<T>::value};
    long long sum = 0;
    for (auto const & element : arr)
        sum += element.score;
    return sum;
}

int main() {
    cout << "size of Small: " << sizeof(Small) << endl;
    cout << "size of Big  : " << sizeof(Big  ) << endl;
    auto const small_objects = vector<Small>(1'000'000);
    auto const big_objects   = vector<Big>  (1'000'000);

    cout << sum_scores(small_objects) << endl;  // 4778us, -O3: 528us
    cout << sum_scores(big_objects) << endl;    // 7823us, -O3: 4385us
}
