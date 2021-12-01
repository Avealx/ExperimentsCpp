/* copy and move experiments
 *
 * move operators, copy operators
 *
 * motivators:
 *  Clean C++ Chapter 05,
 *  https://pspdfkit.com/blog/2019/when-cpp-doesnt-move/
 * A list of experiments to investigate in which situations the move operators
 * are called or suppressed. */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


// sensory class
struct C {
    C() { cout << "constructor\n"; }
    C(C const &  other)          { cout << "constructor: copy\n"; }
    C(C       && other) noexcept { cout << "constructor: move\n"; }
    C& operator=(C const&  other)          { cout << "assignment: copy\n"; return *this; }
    C &operator=(C      && other) noexcept { cout << "assignment: move\n"; return *this; }
};


int main() {
    cout << "\ntemp. vector with initializer list\n";
    vector<C>{ C{} }; // -> 1x ctor, 1x ctor copy

    cout << "\nvector with initializer list\n";
    auto vec1 = vector<C>{ C{} }; // -> 1x ctor, 1x ctor copy

    cout << "\nvector with initializer list and overambitious move\n";
    auto vec2 = vector<C>{move(C{})}; // -> 1x ctor, 1x ctor copy, 1x ctor move

    cout << "\nvector with push_back\n";
    auto vec3a = vector<C>{};
    auto vec3b = vector<C>{};
    cout << "  push_back a non-temporary\n";
    auto tmp = C{};       // -> 1x ctor
    vec3a.push_back(tmp); // -> 1x ctor copy
    cout << "  push_back a temporary\n";
    vec3b.push_back(C{}); // -> 1x ctor, 1x ctor move

    cout << "\nvector with emplace_back\n";
    auto vec4 = vector<C>{};
    vec4.emplace_back(C{}); // -> 1x ctor, 1x ctor move

    cout << "\nswap\n";
    C c1, c2;
    cout << "  actual swap:\n";
    swap(c1, c2); // 1x ctor move, 2x ass. move

    cout << "\nreverse\n";
    auto vec5 = vector<C>{C{}, C{}};
    cout << "  actual reverse:\n";
    reverse(begin(vec5), end(vec5)); // 1x ctor move, 2x ass. move (=1 swap)
}

