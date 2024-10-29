#include "utilities.hpp"

namespace math{
    // Function to convert degrees to radians
    double degreeToRadian(double degrees) {
        return degrees * (M_PI / 180.0);
    }

    // Function to convert radians to degrees
    double radianToDegree(double radians) {
        return radians * (180.0 / M_PI);
    }
}

namespace physics{
    // Mean radius of the Earth, calculated as the radius of the sphere that best approximates the shape of the Earth. 
    // This value is an average that takes into account the variations in radius based on the equator and the poles.
    const double EARTH_RADIUS_NM = 3440.065; // in nautical miles
}
