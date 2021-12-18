/* dependency injection example - logger post
 *
 * motivator: Clean C++
 *
 * To apply the dependency injection, it was necessary to invert the
 * dependency on the Logger by introducing a logger interface `ILogger`. The
 * client now accepts a pointer to some ILogger upon construction. We now have
 * a more loose and more explicit coupling. The `MockLogger` that server as a
 * sensory object relies on this improvement. But, since the Logger was
 * implemented as a Meyer's singleton, it was necessary to 'switch off' the
 * destruction in the shared pointer returned form the `ErrorStreamLogger`
 * class. */
#include <iostream>
#include <memory>
#include <string_view>
using namespace std;


struct ILogger {
    virtual void info(string_view message) = 0;
    virtual void warn(string_view message) = 0;
    virtual void error(string_view message) = 0;

    ~ILogger() = default;
};


struct ErrorStreamLogger : ILogger { // some singleton logging mechanism
    static ErrorStreamLogger& getInstance() {
        static ErrorStreamLogger instance{};
        return instance; }

    static shared_ptr<ErrorStreamLogger> getInstancePtr() {
        return shared_ptr<ErrorStreamLogger>(
                &getInstance(),
                []([[maybe_unused]] auto x){}); } // don't delete the resource

    void info ( string_view message ) override { cerr << "[INFO]  " << message << "\n"; }
    void warn ( string_view message ) override { cerr << "[WARN]  " << message << "\n"; }
    void error( string_view message ) override { cerr << "[ERROR] " << message << "\n"; }

private:
    ErrorStreamLogger () = default;
    ~ErrorStreamLogger() = default;
    ErrorStreamLogger( ErrorStreamLogger && ) noexcept = delete;
    ErrorStreamLogger( ErrorStreamLogger const & )     = delete;
    ErrorStreamLogger& operator=( ErrorStreamLogger && ) noexcept = delete;
    ErrorStreamLogger& operator=( ErrorStreamLogger const & )     = delete;
};


struct MockLogger : ILogger {
    void info ( [[maybe_unused]] string_view message ) override { infoCalled  = true ;}
    void warn ( [[maybe_unused]] string_view message ) override { warnCalled  = true ;}
    void error( [[maybe_unused]] string_view message ) override { errorCalled = true ;}
    bool infoCalled  = false;
    bool warnCalled  = false;
    bool errorCalled = false;
};


struct Client { // implicitly depending on Logger
    explicit Client(std::shared_ptr<ILogger> logger) : logger{logger} {}
    void doTheThing() {
        logger->info ( "Client started" );
        logger->warn ( "Client about to do something.." );
        logger->error( "Client: 'oh no.. Something went awfully wrong.'" ); }

private:
    shared_ptr<ILogger> logger;
};


int main() {
    Client client{ ErrorStreamLogger::getInstancePtr() };
    client.doTheThing();

    cout << "test setting: \n";

    MockLogger sensor;
    Client clientUnderTest{ shared_ptr<MockLogger>{ &sensor } };
    clientUnderTest.doTheThing();
    cout << boolalpha;
    cout << "Client called info: "  << sensor.infoCalled  << "\n";
    cout << "Client called warn: "  << sensor.warnCalled  << "\n";
    cout << "Client called error: " << sensor.errorCalled << "\n";
}
