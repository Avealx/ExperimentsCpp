/* singleton (Meyer's singleton)
 *
 * design pattern
 *
 * motivator: Clean C++, Effective C++
 *
 * A pattern to "Ensure a class has one instance and provides a global point of
 * access to it." The implementation here follows the one from Scott Meyers
 * Effective C++ presented in Stephan Roth's book.
 * I think it might be okay to move it around, as long as copying is
 * prohibited. */
#include <iostream>
using namespace std;

struct Singleton final {
    static Singleton& getInstance() {
        static Singleton singleton{};
        return singleton;
    }
    int foo() { return 42; }
private:
    Singleton() = default;
    Singleton(Singleton &&) noexcept = delete; // make moveable?
    Singleton(Singleton const &) = delete;
    Singleton& operator=(Singleton &&) noexcept = delete; // make moveable
    Singleton& operator=(Singleton const &) = delete;
};

int main() {
    cout << Singleton::getInstance().foo() << endl;
}
