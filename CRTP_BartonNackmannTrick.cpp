/* CRTP - Barton-Nackman Trick
 *
 * static polymorphism, design pattern
 *
 * motivation: https://en.wikipedia.org/wiki/Barton%E2%80%93Nackman_trick
 *
 * We can write isolated functionality F (using class templates), that, during
 * class design, can be added to every class that satisfies F's prerequisites.
 * More formally, we can add F to every class that is a model for the concept
 * of F's template parameter (I think).
 *
 * TODO: add Concept. */
#include <array>
#include <iostream>

struct Tuple {
    Tuple( int v1, int v2, int v3 ) : data_{ v1, v2, v3 } {}
    int      & operator[]( std::size_t index )       { return data_[index]; }
    int const& operator[]( std::size_t index ) const { return data_[index]; }
private:
    std::array<int, 3> data_;
};

std::ostream & operator<<(std::ostream& out, Tuple const & t) {
    return out << t[0] << " " << t[1] << " " << t[2];
}

// ---------------------------------------------------------Barton-Nackman-Trick

template< typename T >
struct Addition {
    friend T operator+( T const & lhs, T const & rhs ) {
        return T{lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]};
    }
};

template< typename T >
struct Multiplication {
    friend T operator*( T const & lhs, T const & rhs ) {
        return T{lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]};
    }
};

// --------------------------------------------------Mix and Match Functionality

struct Vector : Tuple, Addition<Vector>, Multiplication<Vector> {
    Vector( int v1, int v2, int v3 ) : Tuple{ v1, v2, v3 } {}
};

struct Point : Tuple {
    Point( int v1, int v2, int v3 )  : Tuple{ v1, v2, v3 } {}
};


int main () {
    Vector v1{ 1,2,3 };
    Vector v2{ 1,2,3 };
    Point p1{ 1,2,3 };

    std::cout << v1 + v2 << std::endl;
    std::cout << v1 * v2 << std::endl;
    //std::cout << p1 + p1 << std::endl; // compile-time error, point and point cannot be added :D
}
