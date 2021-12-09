/* custom exceptions
 *
 * exception handling, best practices
 *
 * motivator: Clean C++ Chapter 05
 * It is recommended to throw custom exceptions, that is, objects that derive
 * from std::exception. */
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;


struct BasicException : public std::exception {
    char const * what() const noexcept override {
        return "This is a custom exception!";
    }
};


struct InformativeException : public std::exception {
    InformativeException() = delete;
    explicit InformativeException(int const someNumber) { buildErrorMessage(someNumber); }
    char const * what() const noexcept override { return errorMessage_.c_str(); }
private:
    void buildErrorMessage(int const someNumber) {
        errorMessage_ = "This is a custom exception: " + to_string(someNumber) + ".";
    }
    string errorMessage_;
};


int main () {
    try{ throw BasicException{}; }
    catch(BasicException const & e) { cout << "Caught basic exception: " << e.what() << "\n"; }

    try{ throw InformativeException{42}; }
    catch(InformativeException const & e) { cout << "Caught informative exception: " << e.what() << "\n"; }
}
