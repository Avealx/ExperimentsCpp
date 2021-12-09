/* convert a number to string
 *
 * conversion
 *
 * motivator: Clean C++ Chapter04
 * The function std::to_string in the string header does not
 * allow to specify the precision which might cause misleading output. A
 * custom conversion function could make use of the string stream facility.
 */

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
string toString(T value, int const precision=1) {
    stringstream stream{};
    stream << fixed << setprecision(precision) << value;
    return stream.str();
}

int main() {

    // misleading output of to_string:
    cout << "to_string(1 + 1e-9): " << "\n"; // -> 0.000000

    // custom precision
    auto f = float{42.123};
    cout << toString(f) << "\n"; // -> 42.1

    auto d = double{42.123};
    cout << toString(d) << "\n"; // -> 42.1

    auto i = int{42};
    cout << toString(i) << "\n"; // -> 42
}
