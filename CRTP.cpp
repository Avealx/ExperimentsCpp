/* CRTP (curiously recurring template pattern)
 *
 * static polymorphism
 *
 * motivator://www.grimm-jaud.de/index.php/blog/c-ist-doch-lazy
 *
 * Inject functionality through a base class template whose template parameter
 * is the derived class (thus, recurring).
 * The base class implements the functionality by applying methods that
 * the derived class must implement. The base class uses static polymorphism to
 * dispatch the impl() call. */
#include <iostream>
using namespace std;


template <typename Derived>
struct Base {
    void interface() { static_cast<Derived*>(this)->impl(); }
    void impl() { cout << "Base!\n"; }
};


struct Derived1 : Base<Derived1> { void impl() { cout << "Derived1!\n"; } };
struct Derived2 : Base<Derived2> { void impl() { cout << "Derived2!\n"; } };
struct Derived3 : Base<Derived3> {};

template <typename T>
void execute(T&& base) { base.interface(); }


int main() {
    execute(Derived1{}); // Derived1!
    execute(Derived2{}); // Derived2!
    execute(Derived3{}); // Base!
}
