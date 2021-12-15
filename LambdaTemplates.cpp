/* lambda templates
 *
 * lambda expressions, templates, C++20
 *
 * motivator: Clean C++
 *
 * Generic lambda, that use auto in their parameter list, cannot be prevented
 * to deduce different types for different parameters of the same function.
 * This can be prohibited with lambda templates. Additionally, concepts can be
 * used to perform additional checks on the type. */
#include <concepts>
#include <iostream>

// generic lambda
auto mult1 = [](auto const& f1, auto const &f2) { return f1 * f2; };

// lambda template
auto mult2 = []<typename T>(T const& f1, T const &f2) { return f1 * f2; };

// lambda template using concepts
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

auto mult3 = []<Number T>(T const& f1, T const &f2) { return f1 * f2; };


int main() {

auto result1 = mult1(10, 20);
auto result2 = mult2(10, 20);
auto result3 = mult3(10, 20);

std::cout << result1 << std::endl;
std::cout << result2 << std::endl;
std::cout << result3 << std::endl;

}
