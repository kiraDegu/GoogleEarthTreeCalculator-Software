#ifndef _ACADEMY_UTILITIES_HPP
#define _ACADEMY_UTILITIES_HPP

#include <cmath>

namespace math {
    // Function to convert degrees to radians
    double degreeToRadian(double degrees);

    // Function to convert radians to degrees
    double radianToDegree(double radians);
}

namespace physics {
    // Constant for the Earth's radius in nautical miles (mean radius)
    extern const double EARTH_RADIUS_NM; // in nautical miles
}

#endif // _ACDEMY_UTILITIES_H
