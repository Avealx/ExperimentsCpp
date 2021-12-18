/* dependency injection example - logger pre
 *
 * motivator: Clean C++
 *
 * The client implicitly depends on the `Logger` singleton. We want to remove
 * this implicit and strict dependency in favor of a more loose and flexible
 * design. We can do this with dependency injection (see ...Post.cpp file) */
#include <iostream>
#include <string_view>
using namespace std;


struct Logger { // some singleton logging mechanism
    static Logger& getInstance() {
        static Logger instance{};
        return instance; }

    void info ( string_view message ) { cerr << "[INFO]  " << message << "\n"; }
    void warn ( string_view message ) { cerr << "[WARN]  " << message << "\n"; }
    void error( string_view message ) { cerr << "[ERROR] " << message << "\n"; }

private:
    Logger() = default;
    Logger( Logger && ) noexcept = delete;
    Logger( Logger const & )     = delete;
    Logger& operator=( Logger && ) noexcept = delete;
    Logger& operator=( Logger const & )     = delete;
};


struct Client { // implicitly depending on Logger
    void doTheThing() {
        Logger::getInstance().info ("Client started");
        Logger::getInstance().warn ("Client about to do something..");
        Logger::getInstance().error("Client: 'oh no.. Something went awfully wrong.'"); }
};


int main() {
    Client c{};
    c.doTheThing();
}
