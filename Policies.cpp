/* policy-based class design
 *
 * design pattern, stategy pattern, static binding, static dependency injection
 *
 * motivator: Modern C++ Design - Generic Programming and Design Patterns Applied
 *
 * Like a compile time strategy pattern. Combiles (multiple) inheritance and
 * generic programming to enable writing library code that allows to user to
 * specify and extend behaviour withouth incurring runtime costs. */
#include <iostream>
using namespace std;


template<typename T>
struct Policy1 {
    void interface() { cout << "policy 1: " << T{42} << "\n"; }
protected:                   // protected destructor to prevent deleting the
    ~Policy1() = default;    // Host class ("is-A" Policy?) through pointer to Policy
};

template<typename T>
struct Policy2 {
    void interface() { cout << "policy 2: " << T{42} << " \n"; }
    void extendedInterface() { cout << "policy 2 - extended interface\n"; } // enriched interface
protected:
    ~Policy2() = default;
};

template<template <class T> class Policy>
struct Host : Policy<int> {
    /* orchestrate policies here */
};


using Host1 = Host<Policy1>;
using Host2 = Host<Policy2>;

int main() {
    Host1 h1;
    h1.interface();
    //h1.extendedInterface(); // <- compile error, Policy1 does not implement enriched interface

    Host2 h2;
    h2.interface();
    h2.extendedInterface(); // <- legal, Policy2 implements enriched enriched interface
}
