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

    /*! @brief Function to correct latitude to maintain values between -180 and 180
        @param point A point
    */
    void correctLongitude(Type::Point& point);

}

namespace physics {
    /*! @brief Constant for the Earth's radius in nautical miles (mean radius)

        This value is an average that takes into account the variations in radius based on the equator and the poles.
    */
    constexpr Type::Scalar EARTH_RADIUS_NM = 6371.0 * 0.5399568; 

}

#endif // _ACDEMY_UTILITIES_HPP_
