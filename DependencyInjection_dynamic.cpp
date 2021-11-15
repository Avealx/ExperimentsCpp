/* dynamic dependency injection
 *
 * test doubles / mock objects / fake objects
 *
 * motivator: Clean C++ Chapter 01
 * To exchange a dependency (component that is depended on)
 * durin run-time. Useful to replace a real object by a mock
 * for testing.
 */

#include <iostream>
#include <memory>
using namespace std;


struct IService {
    virtual ~IService() {};
    virtual void interface() = 0;
};

class Service {
    std::unique_ptr<IService> s_;
public:
    explicit Service(std::unique_ptr<IService> sp) : s_{move(sp)}{}
    void interface() { s_->interface(); }
};

struct RealService : IService {
    void interface() override { cout << "Real Service\n"; }
};

struct MockService : IService {
    void interface() override { cout << "Mock Service\n"; }
};


int main() {
    Service rs (make_unique<RealService>());
    rs.interface();

    Service ms (make_unique<MockService>());
    ms.interface();
}
