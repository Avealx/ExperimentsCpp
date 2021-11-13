// CRTP (curiously recurring template pattern)
// static polymorphism
// see https://www.grimm-jaud.de/index.php/blog/c-ist-doch-lazy

#include <iostream>
using namespace std;

template <typename Derived>
struct Base {
    void interface() { static_cast<Derived*>(this)->impl(); }
    void impl() { cout << "Base!\n"; }
};

struct Derived1 : public Base<Derived1> {
    void impl() { cout << "Derived1!\n"; }
};

struct Derived2 : public Base<Derived2> {
    void impl() { cout << "Derived2!\n"; }
};
 
struct Derived3 : public Base<Derived3> {};
 
template <typename T>
void execute(T&& base) { base.interface(); }

int main() {
    execute(Derived1{}); // Derived1
    execute(Derived2{}); // Derived2
    execute(Derived3{}); // Base
}
