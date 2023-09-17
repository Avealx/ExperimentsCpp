/* Don't forget to copy inherited base classes when writing custom copy functions.
 *
 * effective cpp, inheritance, copy constructor, copy assignment, copy move
 *
 * motivator: Effective C++ (3rd Edition) - Item 12
 *
 * Whenever we declare an explicit copy function, we have to make sure to copy
 * all non-static data members. While this sounds trivial, it can easily be
 * forgotten in the presence of inheritance. A derived class has to explicitly
 * copy any members of it's bases when a custom copy function is written.
 */

#include <iostream>
using namespace std;

struct Base {
    int baseMember;

    Base(int data = -1)      : baseMember{data}             {}

    Base(Base const & other): baseMember{other.baseMember} {}
    Base& operator=(Base const &  other) { baseMember = other.baseMember; return *this; }
    Base& operator=(Base       && other) { baseMember = other.baseMember; return *this; }
};

ostream& operator<<(ostream& out, Base const & base) {
    return cout << base.baseMember << endl;
}

// here we forget to explicitly copy the base class
struct DerivedBad : Base {
    DerivedBad(int data): Base{data}     {}

    DerivedBad(DerivedBad const & other) {}
    DerivedBad& operator=(DerivedBad const &  other) { return *this; }
    DerivedBad& operator=(DerivedBad       && other) { return *this; }
};

// here we correctly copy the base class members
struct DerivedGood : Base {
    DerivedGood(int data): Base{data}     {}

    DerivedGood(DerivedGood const & other): Base{other} {}
    DerivedGood& operator=(DerivedGood const &  other) { Base::operator=(other); return *this; }
    DerivedGood& operator=(DerivedGood       && other) { Base::operator=(other); return *this; }
};

int main() {

    // whoops
    DerivedBad dBad{42};        cout << dBad;      // 42 (original)
    auto dBadCopy = dBad;       cout << dBadCopy;  // -1, as we forgot to explicitly copy the base members
    dBadCopy = dBad;            cout << dBadCopy;  // -1, as we forgot to explicitly copy the base members
    dBadCopy = std::move(dBad); cout << dBadCopy;  // -1, as we forgot to explicitly copy the base members

    // all good
    DerivedGood dGood{42};                                       cout << dGood;        // 42 (original)
    auto dGoodCopy = dGood;                                      cout << dGoodCopy;    // 42
    { DerivedGood dGoodCopy2{-1}; dGoodCopy2 = dGood;            cout << dGoodCopy2; } // 42
    { DerivedGood dGoodCopy2{-1}; dGoodCopy2 = std::move(dGood); cout << dGoodCopy2; } // 42
}
