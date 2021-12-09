/* pointer to member
 *
 * C++ object module, C++ insights
 *
 * motivator: Inside the C++ Object Model
 *
 * Taking the address of a static member function gives the address of the
 * actual function. It can be called.
 *
 * Taking the address of a non-static member function also gives the address of
 * the actual function. To be called, though, requires binding it to an actual
 * instance of the class which provides the value for the implicit 'this'
 * pointer.
 *
 * Taking the address of a non-static virtual member function gives the address of
 * the function's entry in the virtual table (+1 to allow distinguishing the
 * first entry from the nullptr?). Calling it, requires binding it to
 * an actual instance of the class, as for non-static non-virtual member functions.
 *
 * Taking the address of a non-static data member gives the byte value of
 * the member with respect to the class layout. It starts at zero for classes
 * w/o a virtual table and 0x8 for classes w/ virtual table, due to the
 * inserted pointer to the virtual function table. It needs to be
 * bound to the address of an actual object to give access to a member.
 * */

#include <iostream>
#include <iostream>
#include <cstdio>
using namespace std;


struct MyClass {
    static void static_mf1() { cout << "static member function 1\n"; }
    static void static_mf2() { cout << "static member function 2\n"; }

    void nonstatic_mf1() { cout << "non-static member function 1\n"; }
    void nonstatic_mf2() { cout << "non-static member function 2\n"; }

    virtual void virtual_mf1() { cout << "virtual member function 1\n"; }
    virtual void virtual_mf2() { cout << "virtual member function 2\n"; }

    int x = 1, y = 2, z = 3;
};

int main() {

    void (*psf1)() = &MyClass::static_mf1;
    printf("Static member function 1 at: %p\n", psf1); // actual location
    void (*psf2)() = &MyClass::static_mf2;
    printf("Static member function 2 at: %p\n", psf2); // actual location
    printf("difference: %d\n\n", (char*)psf2 - (char*)psf1);

    void (MyClass::* pmf1)() = &MyClass::nonstatic_mf1;
    printf("Non-static member function 1 at: %p\n", pmf1); // actual location
    void (MyClass::* pmf2)() = &MyClass::nonstatic_mf2;
    printf("Non-static member function 2 at: %p\n\n", pmf2); // actual location

    void (MyClass::* pvmf1)() = &MyClass::virtual_mf1;
    printf("Virtual member function 1 at: %p\n", pvmf1); // 0x1
    void (MyClass::* pvmf2)() = &MyClass::virtual_mf2;
    printf("Virtual member function 2 at: %p\n\n", pvmf2); // 0x9

    int MyClass::* pmx = &MyClass::x;
    printf("Non-static data member x at %p\n", pmx);  // 0x8 (due to vtable pointer)
    int MyClass::* pmy = &MyClass::y;
    printf("Non-static data member y at %p\n", pmy); // 0xc
    int MyClass::* pmz = &MyClass::z;
    printf("Non-static data member z at %p\n", pmz); // 0x10


    cout << "\nusing pointer to members:\n";
    psf1();
    psf2();

    auto mc = MyClass{};
    (mc.*pmf1)();
    ((&mc)->*pmf2)();

    (mc.*pvmf1)();
    ((&mc)->*pvmf2)();

    cout << "x: " << mc.*pmx << ", y: " << mc.*pmy << ", z: " << mc.*pmz << "\n"; 
}
