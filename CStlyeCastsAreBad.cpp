/* c style casts are bad
 *
 * c style casts
 *
 * motivator: Clean C++ Chapter04
 * In some cases, C style casts prevents the compiler to warn us when we do
 * ill advised conversions. C++ style casts lead to compile time errors.
 */


#include <iostream>
using namespace std;

int main() {
    auto i32 = int32_t{42};
    auto i64p = (int64_t*) &i32;
    cout << *i64p << "\n"; // prints rubbish

    // compile time error
    //auto i64pSave = static_cast<int64_t*>(&i32);
}
