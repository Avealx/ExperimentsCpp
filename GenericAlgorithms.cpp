/* Example implementation of algorithms that work on iterators and ranges
 *
 * generic programming, templates, generic algorithm
 *
 * motivation: C++ High Performance
 *
 * compile using `g++ --std=c++20`
 *
 * We can implement an algorithm to perform on iterators and supply an
 * additional version that accepts a range.
 */

#include <iostream>
#include <list>
#include <ranges>
#include <vector>
using namespace std;

// version that accepts iterators (here we require that both, `begin` and `end`
// are of the same type (or implicitly convertible to the same type?)
template <typename Iterator, typename T>
auto contains(Iterator begin, Iterator end, T const & value) {
    while (begin != end)
        if (*begin++ == value)
            return true;
    return false;
}

// Additional version accepting a range.
// We use the concise `auto` syntax for templates and the concept
// `std::ranges::range`.
auto contains(std::ranges::range auto const & r, auto const & x) {
    return contains(std::begin(r), std::end(r), x);
}


int main() {
    // works for vectors
    vector v{1, 2, 3};
    cout << "vector: " << endl;
    cout << boolalpha << "contains  1: " << contains(v,  1) << endl;
    cout << boolalpha << "contains -1: " << contains(v, -1) << endl;

    // works for lists
    list l{1, 2, 3};
    cout << "\nlist: " << endl;
    cout << boolalpha << "contains  1: " << contains(l,  1) << endl;
    cout << boolalpha << "contains -1: " << contains(l, -1) << endl;

}
