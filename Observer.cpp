/* Observer pattern following the description in 'Head First
 * Design Pattern'.
 *
 * design pattern, observer, one-to-many
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

//----------------------------------------------------------------------------------------Interfaces

template <typename State>
struct ObserverI {
    virtual void notify(State const &) = 0;
};

template <typename State>
struct SubjectI {
    virtual void doregister(ObserverI<State>*) = 0;
    virtual void unregister(ObserverI<State>*) = 0;
    virtual void notifyObservers() const = 0;
};

//-------------------------------------------------------------------------------------------Example

using State = int;

class Subject : public SubjectI<State> {
public:
    void setState(State newState) noexcept { state_ = newState; }

    // SubjectI
    void doregister(ObserverI<State>* newObserver) override {
        observers_.push_back(newObserver);
    }

    void unregister(ObserverI<State>* observer) override {
        observers_.erase(std::remove(std::begin(observers_), std::end(observers_), observer),
                        std::cend(observers_));
    }

    void notifyObservers() const override {
        for (auto & observer : observers_) observer->notify(state_);
    }

private:
    State state_{-1};
    std::vector<ObserverI<State>*> observers_;
};

class Observer : public ObserverI<State> {
public:
    Observer() : observerID_{nextObserverID()} {}

    // ObserverI
    void notify(State const & state) override {
        std::cout << "observer " << observerID_ << " observed state: " << state << std::endl;
    }
private:
    static std::size_t nextObserverID() {
        static std::size_t nextID = 0;
        return nextID++;
    }
    std::size_t const observerID_;
};

struct VerboseObserver : ObserverI<State> {
    // ObserverI
    void notify(State const & state) override {
        std::cout << "Hi there, I just got notified of the state: " << state
                  << ". Well have a nice day!" << std::endl;
    }
};

//--------------------------------------------------------------------------------------------Try It

int main() {
    Subject subject;
    Observer observer1, observer2;
    subject.doregister(&observer1);
    subject.doregister(&observer2);
    VerboseObserver verboseObserver;
    subject.doregister(&verboseObserver);

    subject.notifyObservers();
    subject.unregister(&verboseObserver);
    subject.setState(42);
    subject.notifyObservers();
}
