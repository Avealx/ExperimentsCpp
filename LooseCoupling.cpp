/* loose coupling via interface
 *
 * program to an interface, dependency inversion.
 *
 * motivator: Clean C++ Chapter03
 * Enables re-use and allows to apply test doubles.
 * Dependency inversion:
 * Before: Switch -> Lamp
 * After: Switch -> Switchable <- Lamp
 */

#include <iostream>
using namespace std;

// Tight coupling
// --------------
struct Lamp {
    void turnOn() { cout << "Lamp is on.\n"; }
};

class Switch {
    Lamp& lamp_;
public:
    Switch(Lamp& lamp) : lamp_{lamp} { }
    void on() { lamp_.turnOn(); }
};


// Loose coupling by introducing a shared abstraction,
// the interface 'Switchable'.
// ---------------------------------------------------
struct Switchable {
    virtual void on() = 0;
};

struct LampLC : Switchable {
    void on() override { cout << "LampLC is on.\n"; }
};

class SwitchLC {
    Switchable& switchable_;
public:
    SwitchLC(Switchable& switchable) : switchable_{switchable} { }
    void on() { switchable_.on(); }
};


int main () {
    Lamp l;
    Switch s{l};
    s.on();

    LampLC llc;
    SwitchLC slc{llc};
    slc.on();
}
