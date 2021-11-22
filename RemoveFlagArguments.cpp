/* remove flag arguments
 *
 * refactoring, program to an interface
 *
 * motivator: Clean C++ Chapter04
 * Reducing the number of arguments relieves the cognitive load during code
 * reading and understanding. The idea is to lift the different computational
 * branches distinguished by the flag arguments into their own methods/classes
 * that self-document the behaviour.
 */

#include <iostream>

using namespace std;

// Version 1: use of flag argument 'world' (bad practice)

struct Greeter {
    void greet(bool world=false) const {
        cout << "Hello";
        if (world)
            cout << " world\n";
    }
};

// Version 2: split the computation branches into separate methods

struct GreeterSeparated {
    void greet() const { cout << "Hello"; }

    void greetWorld() const {
        greet();
        cout << " world\n";
    }
};

// Version 3: split the computation branches into separate classes

struct IGreeter {
    virtual void greet() const = 0;
    virtual ~IGreeter() {}
};

struct SimpleGreeter : IGreeter{
    virtual void greet() const override { cout << "Hello"; }
};

struct WorldGreeter : IGreeter{
    virtual void greet() const override {
        simpleGreeter.greet();
        greetWorld();
    }
    private:
    void greetWorld() const { cout << " world\n"; }
    SimpleGreeter simpleGreeter;
};


int main() {
    cout << "---------------\n";
    cout << "basic greeting:\n";
    cout << "---------------\n";
    auto g = Greeter{};
    g.greet();
    cout << "\n";
    bool world = true;
    g.greet(world);

    cout << "-------------------\n";
    cout << "greeting separated:\n";
    cout << "-------------------\n";
    auto gS = GreeterSeparated{};
    gS.greet();
    cout << "\n";
    gS.greetWorld();

    cout << "---------------------\n";
    cout << "greeting Inheritance:\n";
    cout << "---------------------\n";
    SimpleGreeter{}.greet();
    cout << "\n";
    WorldGreeter{}.greet();
}


