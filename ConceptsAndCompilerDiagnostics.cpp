/* concepts simplify compiler diagnostics
 *
 * concepts, templates, compiler diagnostics
 *
 * motivator: https://en.cppreference.com/w/cpp/language/constraints
 *
 * In principal, the introduction of concepts in C++20 should be able to
 * simplify the compiler diagnostics when an error occurs during template
 * instantiation. I was, however, not able to reproduce this. Using g++ 10.3,
 * the following snippet produces a significantly more verbose and similarly
 * imprecise error message when compiled with -std=c++2a as without this flag.
 */

#include <algorithm>
#include <list>
using namespace std;

int main() {
    auto theList = list<int>{1, 2, 3};
    sort(begin(theList), end(theList)); // list is not random-accessible
}
