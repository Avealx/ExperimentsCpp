/* compile time assertions
 *
 * C++98
 *
 * motivator: Modern C++ Programming (A. Alexandrescu)
 *
 * A C++98 technique to realize compile time assertions that allow to pass a
 * custom 'message' (in form of a custom class name) to the user.
 *
 * How it works:
 * The CompileTimeChecker<True> constructor accepts any arguments.
 * The CompileTimeChecker<False> constructor does not accept any argument.
 * The STATIC_CHECK macro defines a class that contains a custom message passed
 * by the user. The subsequent construction of a CompileTimeChecker either
 * succeeds (if the template parameter, expression != 0, evaluates to true) or
 * fails (if the template parameter evaluates to false). In the latter case the
 * error message contains the wrongfully passed argument to the constructor
 * which, conveniently, comprises the error message. */

template<bool>
struct CompileTimeChecker {
    CompileTimeChecker(...){}
};

template<>
struct CompileTimeChecker<false> {};

#define STATIC_CHECK(expr, msg) \
{\
    class ERROR_##msg {};\
    (void)sizeof(CompileTimeChecker<(expr) != 0>((ERROR_##msg{})));\
}

template <class To, class From>
To safe_reinterpret_cast(From from) {
    STATIC_CHECK(sizeof(From) <= sizeof(To), Destination_Type_Too_Narrow);
    return reinterpret_cast<To>(from);
}

int main() {
    void* somePointer{ nullptr };
    //[[maybe_unused]] char c = safe_reinterpret_cast<char>(somePointer); // CT error
    [[maybe_unused]] void* c = safe_reinterpret_cast<void*>(somePointer); // okay
}
