#include "Utilities.hpp"

namespace math{
    Type::Scalar degreeToRadian(Type::Scalar degrees) {
        return degrees * (M_PI / 180.0);
    }

    Type::Scalar radianToDegree(Type::Scalar radians) {
        return radians * (180.0 / M_PI);
    }

    void correctLongitude(Type::Point& point) {
        if (std::abs(point.longi) > 180.0) {
            const Type::Scalar delta = std::fmod(point.longi, 180.0);
            if (point.longi>0.0)
                point.longi = -180.0 + delta;
            else
                point.longi = 180.0 + delta;
        } 
    }

}
