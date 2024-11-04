#include <cmath>
#include "Utilities.hpp"

namespace math{
    constexpr Type::Scalar pi = 2*std::acos(0.);

    Type::Scalar degreeToRadian(Type::Scalar degrees) {
        return degrees * (pi / 180.0);
    }

    Type::Scalar radianToDegree(Type::Scalar radians) {
        return radians * (180.0 / pi);
    }
}
