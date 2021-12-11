/* duck typing
 *
 * duck typing, type erasure, templates, concepts, static polymorphism, dynamic polymorphism, design patterns
 *
 * motivator: Clean C++
 *
 * A technique that allows polymorphic use of classes that implement a common
 * interface but don't share a common base. The inheritance relation allowing
 * for polymorphic behaviour is encapsulated in a wrapper class. The code is
 * more intricated compared to classical dynamic polymorphism, but the
 * resulting use later on is cleaner. (Compare with
 * TypeErasure_DynamicPolymorphism.cpp) */
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;


template <typename T>
concept TypeAsStringRetrievable = requires (T const& obj) {
    { obj.typeAsString() } -> std::same_as<std::string>;
};


struct PolymorphicWrapper {
    template <TypeAsStringRetrievable T>
    PolymorphicWrapper(T const & obj) : wrapped_{make_shared<Model<T>>(obj)} {}

    string typeAsString() const { return wrapped_->typeAsString(); }

private:
    struct Concept {
        virtual ~Concept() = default;
        virtual string typeAsString() const = 0;
    };

    template <TypeAsStringRetrievable T>
    struct Model : Concept {
        Model(T const & obj) : object_{obj} {}
        string typeAsString() const override { return object_.typeAsString(); }
    private:
        T object_;
    };

    std::shared_ptr<Concept> wrapped_;
};


struct Circle {
    string typeAsString() const { return "Circle"; }
};

struct Square {
    string typeAsString() const { return "Square"; }
};

struct Banana {
    string typeAsString() const { return "Banana"; }
};


using Shapes = vector<PolymorphicWrapper>;

int main() {
    auto shapes = Shapes{ Circle{}, Square{} };

    for (auto const & shape : shapes)
        cout << shape.typeAsString() << '\n';
}
