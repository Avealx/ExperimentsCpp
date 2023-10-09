/* Providing different implementations for different concepts
 *
 * concepts, templates, compile-time programming, meta-programming
 *
 * motivation: C++ High Performance
 *
 * compile using `g++ --std=c++20 CompileTimeFunctionOverloading.cpp`
 *
 * We can provide different implementations of a function template for
 * different type arguments by either using compile time branching using `if
 * constexpr`, or, arguably cleaner by using concepts, such as
 * `std::floating_point` or `std::integral`.
 */

#include <concepts>
#include <cmath>
#include <iostream>
#include <type_traits>
using namespace std;

// version 1 without constraints, using `if constexpr`
template <typename T>
auto generic_mod_1(T v, T n) -> T {
    if constexpr (is_floating_point_v<T>) return fmod(v, n);
    else                                  return v % n;
}

template <floating_point T>
auto generic_mod_2(T v, T n) -> T { return fmod(v, n); }

template <integral T>
auto generic_mod_2(T v, T n) -> T { return v % n; }


int main() {
    cout << "using `if constexpr`\n";
    cout << "3.5 mod 3.0 = " << generic_mod_1(3.5, 3.0) << '\n';
    cout << "3 mod 2 = "     << generic_mod_1(3, 2)     << '\n' << endl;

    cout << "using concepts\n";
    cout << "3.5 mod 3.0 = " << generic_mod_2(3.5, 3.0) << '\n';
    cout << "3 mod 2 = "     << generic_mod_2(3, 2)     << '\n' << endl;
}
