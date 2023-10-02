/* Reference members can be altered in const member funcions (like pointer members)
 *
 * motivator: C++ High Performance
 *
 * It makes sense, having in mind that this is already the case for member
 * pointers. It also explains, why lambdas need the `mutable` keyword when they
 * change any local variables but not if the local variables are captures by
 * reference. This is something to keep in mind when striving for semantic
 * constness, instead of syntactical constness.
 */


#include <iostream>
using namespace std;

struct MyClass{
    MyClass(int& x) : x{x} {}
    void increment() const { ++x; }  // it's okay to alter a reference in a const member function
    int& x;
};

int main() {
    int x = 0;
    cout << "x pre: " << x << endl;

    MyClass const c{x};
    c.increment();
    cout << "x post: " << x << endl;
}
