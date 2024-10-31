#include "Utilities.hpp"

namespace math{
    Type::Scalar degreeToRadian(Type::Scalar degrees) {
        return degrees * (M_PI / 180.0);
    }

    Type::Scalar radianToDegree(Type::Scalar radians) {
        return radians * (180.0 / M_PI);
    }
}
