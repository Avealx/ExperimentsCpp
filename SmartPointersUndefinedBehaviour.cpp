/* undefined behaviour in smart pointers
 *
 * undefined behaviour, resource management
 *
 * motivator: Clean C++ Chapter 05
 * Smart pointers call delete per default which leads to undefined behaviour
 * when they manage an array. In this case either pass a custom delete
 */

#include <memory>
#include <string>
using namespace std;

// undefineg behaviour
void wrongDeleter() {
    shared_ptr<string> strings{new string[10]};
}

void correctDeleter() {
    shared_ptr<string> strings{new string[10], default_delete<string[]>()};
}

int main() {
    wrongDeleter(); // undefined behaviour
    correctDeleter(); // ok
}
