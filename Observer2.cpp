/* Observer pattern for multiple interface inheritance
 *
 * design pattern, observer, one-to-many
 *
 * The way we have implemented the observer pattern (see Observer.cpp) makes it
 * simple for one class to inherit multiple versions of the `SubjectI`
 * interface for different `States`. This requires a bit care for functions
 * that are now inherited multiple times but do not allow for overload
 * resolution due to missing arguments in their signature.
 * We can introduce a dummy type `Tag` in the `SubjectI` interface and use it
 * to add an argument to any function that lacks a suitable argument for
 * overload resolution.
 * We can also add this tag to functions that don't necessaryly need it,
 * because they already have a signature that is rich enough to support
 * overloading (via casting the pointer in the example below, see `main`).
 * This gives us an alternative to selecting the correct overload. If we don't
 * want to introduce a static_cast, we can pass the correct Tag as second
 * argument (again, see `main`).
 * For convenience, we can also provide a version without this dummy argument
 * that calls the version with argument, so that in cases where we have single
 * inheritance, callers don't have to use this dummy argument.
 */

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------------------------------------------Interfaces

template <typename State>
struct ObserverI {
    virtual void notify(State const &) = 0;
};

template <typename State>
struct SubjectI {
    struct Tag{};  // for overloading `notifyObservers` when inheriting from multiple `SubjectI` instances

    virtual void doregister(ObserverI<State>*, Tag) = 0;  // Tag not necessary, but enables overload selection without pointer cast
    virtual void unregister(ObserverI<State>*, Tag) = 0;  // same as above
    virtual void notifyObservers(Tag) const = 0;
};

//-------------------------------------------------------------------------------------------Example

using StateInt = int;
using StateString = string;

// Subject implements two different instantiations of the SubjectI interface.
// Each function name is now present twice and we use the Tag parameters to
// distinguish the signatures, thus enabling overloads.
class Subject : public SubjectI<StateInt>,
                public SubjectI<StateString> {
public:
    using IntTag = typename SubjectI<StateInt>::Tag;
    using StringTag = typename SubjectI<StateString>::Tag;

    void setStateInt(StateInt newState) noexcept { stateInt_ = newState; }
    void setStateString(StateString newState) noexcept { stateString_ = newState; }

    // SubjectI<StateInt>
    void doregister(ObserverI<StateInt>* newObserver, IntTag tag = IntTag{}) override {
        observers_.push_back(newObserver); }

    void unregister(ObserverI<StateInt>* observer, IntTag tag = IntTag{}) override {
        observers_.erase(remove(begin(observers_), end(observers_), observer),
                         cend(observers_)); }

    void notifyObservers(IntTag) const override {
        for (auto & observer : observers_) observer->notify(stateInt_); }

    // SubjectI<StateString>
    void doregister(ObserverI<StateString>* newObserver, StringTag tag = StringTag{}) override {
        observersString_.push_back(newObserver); }

    void unregister(ObserverI<StateString>* observer, StringTag tag = StringTag{}) override {
        observersString_.erase(remove(begin(observersString_), end(observersString_), observer),
                         cend(observersString_)); }

    void notifyObservers(StringTag) const override {
        for (auto & observer : observersString_) observer->notify(stateString_); }

private:
    StateInt stateInt_{-1};
    vector<ObserverI<StateInt>*> observers_;

    StateString stateString_{"None"};
    vector<ObserverI<StateString>*> observersString_;
};

struct IntObserver : ObserverI<StateInt> {
    // ObserverI<StateInt>
    void notify(StateInt const & state) override {
        cout << "int observer observed state: " << state << endl; }
};

struct StringObserver : ObserverI<StateString> {
    // ObserverI<StateString>
    void notify(StateString const & state) override {
        cout << "string observer observed state: " << state << endl; }
};

// `AllObserver` observer both interfaces of `Subject`. We have to either
// explicitly cast to the right ObserverI, then (un-)registering it to (from)
// `Subject`, or use one of `Subject`'s `Tag`s to select the right overload.
// (see main)
struct AllObserver : ObserverI<StateInt>,
                     ObserverI<StateString> {
    // ObserverI<StateString>
    void notify(StateString const & state) override {
        cout << "all observer observed state: " << state << endl; }
    // ObserverI<StateAll>
    void notify(StateInt const & state) override {
        cout << "all observer observed state: " << state << endl; }
};

//--------------------------------------------------------------------------------------------Try It

int main() {
    Subject subject;
    IntObserver    intObserver;
    StringObserver stringObserver;
    AllObserver    allObserver;

    subject.doregister(&intObserver);
    subject.doregister(&stringObserver);
    subject.doregister(static_cast<ObserverI<StateInt>*>(&allObserver));  // select overload via cast
    subject.doregister(&allObserver, Subject::StringTag{});               // select overload via tag

    subject.notifyObservers(SubjectI<StateInt>::Tag{});
    subject.setStateInt(42);
    subject.notifyObservers(SubjectI<StateInt>::Tag{});

    subject.notifyObservers(SubjectI<StateString>::Tag{});
    subject.setStateString("Hello World");
    subject.notifyObservers(SubjectI<StateString>::Tag{});
}
