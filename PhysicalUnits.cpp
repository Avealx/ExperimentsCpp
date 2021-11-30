/* physical unit handling at compile time.
 *
 * compile time computation, physical units
 *
 * motivator: Clean C++ Chapter 05
 * Physical units can be expressed as classes so that the compiler
 * can assist in checking the computations and value assignments.
 */

#include <iostream>
#include <string>

template <int M, int K, int S>
struct MKS {
    enum {meter = M, kilogram = K, second = S};
};


template <typename MKS>
class Value {
    long double magnitude_{0.0};
public:
    constexpr explicit Value (long double const magnitude) noexcept :magnitude_(magnitude) {}
    constexpr long double magnitude() const noexcept { return magnitude_; }
};


using Dimensionless = Value<MKS< 0, 0,  0>>;
using Length        = Value<MKS< 1, 0,  0>>;
using Mass          = Value<MKS< 0, 1,  0>>;
using Time          = Value<MKS< 0, 0,  1>>;
using Area          = Value<MKS< 2, 0,  0>>;
using Volume        = Value<MKS< 3, 0,  0>>;
using Speed         = Value<MKS< 1, 0, -1>>;
using Acceleration  = Value<MKS< 1, 0, -2>>;
using Frequency     = Value<MKS< 0, 0, -1>>;
using Force         = Value<MKS< 1, 1, -2>>;
using Pressure      = Value<MKS<-1, 1, -2>>;


constexpr Acceleration gravitaionalAccelerationOnEarth{9.80665};
constexpr Pressure standardPressureOnSeaLevel{1013.25};
constexpr Speed speedOfLight{299792458.0};
constexpr Frequency concestPitchA{440.0};
constexpr Mass neutronMass{1.6749286e-27};


template <int M, int K, int S>
constexpr Value<MKS<M,K,S>>
operator+(Value<MKS<M,K,S>> const & lhs,
          Value<MKS<M,K,S>> const & rhs) {
    return Value<MKS<M,K,S>>{lhs.magnitude() + rhs.magnitude()};
}

template <int M, int K, int S>
constexpr Value<MKS<M,K,S>>
operator-(Value<MKS<M,K,S>> const & lhs,
          Value<MKS<M,K,S>> const & rhs) {
    return Value<MKS<M,K,S>>{lhs.magnitude() - rhs.magnitude()};
}

template <int ML, int KL, int SL, int MR, int KR, int SR>
constexpr Value<MKS<ML+MR,KL+KR,SL+SR>>
operator*(Value<MKS<ML,KL,SL>> const & lhs,
          Value<MKS<MR,KR,SR>> const & rhs) {
    return Value<MKS<ML+MR,KL+KR,SL+SR>>{lhs.magnitude() * rhs.magnitude()};
}

template <int ML, int KL, int SL, int MR, int KR, int SR>
constexpr Value<MKS<ML-MR,KL-KR,SL-SR>>
operator/(Value<MKS<ML,KL,SL>> const & lhs,
          Value<MKS<MR,KR,SR>> const & rhs) {
    return Value<MKS<ML-MR,KL-KR,SL-SR>>{lhs.magnitude() / rhs.magnitude()};
}

int main() {
    auto length = Length{2};
}
