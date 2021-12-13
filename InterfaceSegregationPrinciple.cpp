/* interface segregation principle (ISP)
 *
 * design pattern, OOP
 * 
 * motivator: Clean C++
 *
 * When an interface becomes too broad, it might become less applicable, as
 * this might limit the amount of classes that implement the full interface.
 * The interface segregation principle dictates to split this broad interface
 * into smaller more coherent ones. */
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// using a single interface that might be too broad

struct IBird {
    virtual ~IBird() = default;
    virtual void fly() = 0;
    virtual void tweet() = 0;
};

struct Sparrow : IBird {
    void fly() override { cout << "Sparrow: flap flap\n"; }
    void tweet() override { cout << "Sparrow: chirp\n"; }
};

struct Penguin : IBird {
    void fly() override { cout << "Penguin: NOT IMPLEMENTED\n"; }
    void tweet() override { cout << "Penguin: gakker\n"; }
};


// segregating the interface into more coherent ones

struct IFlyable {
    virtual ~IFlyable() = default;
    virtual void fly() = 0;
};

struct IAudible {
    virtual ~IAudible() = default;
    virtual void makeSound() = 0;
};


struct SparrowISP : IFlyable, IAudible {
    void fly() override { cout << "SparrowISP: flap flap\n"; }
    void makeSound() override { cout << "SparrowISP: chirp\n"; }
};

struct PenguinISP : IAudible {
    void makeSound() override { cout << "SparrowISP: gakker\n"; }
};



int main () {
    cout << "\nWith single interface:\n";

    using Birds = vector<shared_ptr<IBird>>;

    auto birds = Birds{make_shared<Sparrow>(), make_shared<Penguin>()};

    for (auto bird : birds)
        bird->fly();

    for (auto bird : birds)
        bird->tweet();


    cout << "\nAfter applying ISP:\n";

    using FlyingAnimals = vector<shared_ptr<IFlyable>>;
    using AudibleAnimals = vector<shared_ptr<IAudible>>;

    auto sparrowISP = make_shared<SparrowISP>();
    auto penguinISP = make_shared<PenguinISP>();
    auto flyingAnimals = FlyingAnimals{sparrowISP};
    auto audibleAnimals = AudibleAnimals{sparrowISP, penguinISP};

    for (auto flyable : flyingAnimals)
        flyable->fly();

    for (auto audible : audibleAnimals)
        audible->makeSound();
}
