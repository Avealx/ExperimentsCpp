/* Exploring alignment issues in C++
 *
 * motivation: C++ High Performance
 *
 * In C++ every primitive type has an alignment requirement, which can be
 * inspected with `alignof(type)`. This has implication for the data layout in
 * a user defined type. We define an aligned class, in which we took care to
 * place primitive types with similar alignment requirements next to each
 * other, and an unaligned class, in which data members with different
 * alignment requirements alternate. The result is a substantial size
 * difference of the otherwise identical classes.
 */
#include <iostream>
#include <memory>
using namespace std;

struct AlginedClass {
 int i1;
 int i2;
 byte b1;
 byte b2;
};


struct UnalginedClass {
 byte b1;
 int i1;
 byte b2;
 int i2;
};

struct Bytes {
    byte b1, b2, b3;
};

struct Ints {
    int i1, i2, i3;
};

struct ByteAndInt {
    byte b;
    int i;
};


int main() {
    cout << "byte: "        << alignof(byte)        << '\n';    //  1
    cout << "short: "       << alignof(short)       << '\n';    //  2
    cout << "int: "         << alignof(int)         << '\n';    //  4
    cout << "long long: "   << alignof(long long)   << '\n';    //  8
    cout << "float: "       << alignof(float)       << '\n';    //  4
    cout << "double: "      << alignof(double)      << '\n';    //  8
    cout << "max_align_t: " << alignof(max_align_t) << '\n';    // 16
    cout << "Bytes: "       << alignof(Bytes)       << '\n';    //  1
    cout << "Ints: "        << alignof(Ints)        << '\n';    //  4
    cout << "ByteAndInt: "  << alignof(ByteAndInt)  << "\n\n";  //  4

    cout << "AlginedClass: "   << sizeof(AlginedClass)   << '\n';  // 12
    cout << "UnalginedClass: " << sizeof(UnalginedClass) << '\n';  // 16
}
