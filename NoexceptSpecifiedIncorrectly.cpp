/* noexcept specified incorrectly
 *
 * noexcept specification, optimization, best practices
 *
 * motivator: Effective Modern C++ item 14
 * An exception leaving a function specified as noexcept
 * causes program termination. */

#include <stdexcept>
#include <iostream>
using namespace std;


void throwing()  {
    throw runtime_error("Err");
}


void oops() noexcept {
    throwing();
}


int main() {
    // everything fine
    try { throwing(); }
    catch (...) { cout << "Successfully caught\n"; }

     // exception from noexcept function terminates the program
    try { oops(); }
    catch (...) { cout << "Successfully caught\n"; }
}
