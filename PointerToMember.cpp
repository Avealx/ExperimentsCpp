/* pointer to member
 *
 * C++ object module, C++ insights
 *
 * motivator: Inside the C++ Object Model
 *
 * Taking the address of a static member function gives the address of the
 * actual function. It can be called.
 * Taking the address of a non-static member function also gives the address of
 * the actual function. To be called, though, requires a binding to an actual
 * instance of the class which provides the value for the implicit 'this'
 * pointer.
 * Taking the address of a non-static data member gives the byte value of
 * the member with respect to the class layout. It also needs to be bound to the
 * address of an actual object to give access to a member. */

#include <iostream>
#include <iostream>
#include <cstdio>
using namespace std;


struct MyClass {
    static void static_mf1() { cout << "static member function 1\n"; }
    static void static_mf2() { cout << "static member function 2\n"; }

    void nonstatic_mf1() { cout << "non-static member function 1\n"; }
    void nonstatic_mf2() { cout << "non-static member function 2\n"; }

    int x = 1, y = 2, z = 3;
};

int main() {

    void (*psf1)() = &MyClass::static_mf1;
    printf("Static member function 1 at: %p\n", psf1);
    void (*psf2)() = &MyClass::static_mf2;
    printf("Static member function 2 at: %p\n", psf2);
    printf("difference: %d\n\n", (char*)psf2 - (char*)psf1);

    void (MyClass::* pmf1)() = &MyClass::nonstatic_mf1;
    printf("Non-static member function 1 at: %p\n", pmf1);
    void (MyClass::* pmf2)() = &MyClass::nonstatic_mf2;
    printf("Non-static member function 2 at: %p\n", pmf2);

    int MyClass::* pmx = &MyClass::x;
    printf("Non-static data member x at %p\n", pmx);
    int MyClass::* pmy = &MyClass::y;
    printf("Non-static data member y at %p\n", pmy);
    int MyClass::* pmz = &MyClass::z;
    printf("Non-static data member z at %p\n", pmz);

    cout << "\nusing pointer to members:\n";
    psf1();
    psf2();

    auto mc = MyClass{};

    (mc.*pmf1)();
    ((&mc)->*pmf2)();

    cout << "x: " << mc.*pmx << ", y: " << mc.*pmy << ", z: " << mc.*pmz << "\n"; 
}
