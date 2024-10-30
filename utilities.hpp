#ifndef _ACADEMY_UTILITIES_HPP_
#define _ACADEMY_UTILITIES_HPP_

#include <cmath>
#include "TypeTraits.hpp"

namespace math {
    /*! @brief Function to convert degrees to radians
        @param degrees The angle in deg
        @return The conversion in rad
    */
    Type::Scalar degreeToRadian(Type::Scalar degrees);


    /*! @brief Function to convert radians to degrees
        @param radians The angle in rad
        @return The conversion in deg
    */    
    Type::Scalar radianToDegree(Type::Scalar radians);
}

namespace physics {
    /*! @brief Constant for the Earth's radius in nautical miles (mean radius)

        This value is an average that takes into account the variations in radius based on the equator and the poles.
    */
    constexpr Type::Scalar EARTH_RADIUS_NM = 3440.065; 

}

#endif // _ACDEMY_UTILITIES_HPP_
