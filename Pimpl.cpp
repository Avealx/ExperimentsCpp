/* The pimpl-idiom to hide implementations and divide compilation units.
 *
 * pimpl, compilation firewall, gotw
 *
 * motivatiors: Guru of the week 100
 *
 * The idiom is nice to hide implementation details away from the header file.
 * The implementation is straigthforward with one caveat to watch out for when
 * using a std::unique_ptr to the implementation class: the Destructor of the
 * main class has to be implemented *after* the full class definition of the
 * implementation class is known to the compiler. This means that we cannot
 * rely on the implicitly defined default constructor, as it will be generated
 * too early.
 */

#include <iostream>
#include <memory>
using namespace std;

// in header
struct MyClass {
    MyClass();
    ~MyClass();

    void foo();
private:
    class MyImpl;
    unique_ptr<MyImpl> impl_;
};


// in source
struct MyClass::MyImpl {
    void foo() { cout << "Hello world!" << endl; }
};

MyClass::MyClass(): impl_{make_unique<MyImpl>()} {}
MyClass::~MyClass() = default;
void MyClass::foo() { impl_->foo(); }


// test it
int main () {
    MyClass{}.foo();
}
