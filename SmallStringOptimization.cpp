/* Some tests to explore the standard libraries small string optimization
 *
 * motivation: C++ High Performance
 *
 * These experiments show that on my implementation, a string initially
 * provides space on the stack for 15 characters. Adding the 16th character
 * requires allocating memory on the free storage.
 */
#include <iostream>
#include <memory>
#include <string>
using namespace std;

auto allocated = size_t{0};

// overload operator new to keep track of how much space on the free storage
// was occupied
void* operator new(size_t size) {
    void* p = std::malloc(size);
    allocated += size;
    return p;
}

void operator delete(void* p) noexcept {
    return std::free(p);
}

int main() {
    allocated = 0;
    auto s = string{};

    cout << "stack space used = " << sizeof(s)      << '\n'           // 32
         << "heap  space used = " << allocated      << '\n'           //  0
         << "capacity of string = " << s.capacity() << '\n' << endl;  // 15

    s = "123456789012345";
    cout << "stack space used = " << sizeof(s)      << '\n'           // 32
         << "heap  space used = " << allocated      << '\n'           //  0
         << "capacity of string = " << s.capacity() << '\n' << endl;  // 15

    s += "1";
    cout << "stack space used = " << sizeof(s)      << '\n'           // 32
         << "heap  space used = " << allocated      << '\n'           // 31
         << "capacity of string = " << s.capacity() << '\n' << endl;  // 30
}
