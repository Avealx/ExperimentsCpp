/* dynamic polymorphism
 *
 * dynamic polymorphism, type erasure, design pattern
 *
 * motivator: Clean C++
 *
 * Example for dynamic polymorphism via inheriting a common interface.
 * C++ also offers static type erasure techniques based on templates. */

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;


struct Shape {
    virtual ~Shape() = default;
    virtual string typeString() const = 0;
};

struct Circle : Shape {
    string typeString() const override { return "Circle"; }
};

struct Square : Shape {
    string typeString() const override { return "Square"; }
};

using Shapes = vector<shared_ptr<Shape>>;


int main() {
    auto shapes = Shapes{make_shared<Circle>(), make_shared<Square>()};

    for (auto const & shape : shapes)
        cout << shape->typeString() << '\n';
}
