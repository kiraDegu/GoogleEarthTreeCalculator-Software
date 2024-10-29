#include "TypeTraits.hpp"


class DataValidator {

    private:

    // Constants for validation limits
    static const Type::Scalar distanceMax = 0.5; 
    static const Type::Scalar distanceMin = 0.0; 
    static const Type::Scalar longitudeMax = 180.0;
    static const Type::Scalar longitudeMin = -180.0;
    static const Type::Scalar latitudeMax = 90.0; 
    static const Type::Scalar latitudeMin = -90.0; 
    static const Type::Scalar headingMax = 360.0; 
    static const Type::Scalar headingMin = 0.0; 
    static const Type::Scalar heightMax = 1500.0; // Example maximum height in meters
    static const Type::Scalar heightMin = 0.0; 

    public:

    // Validates distance (distanceMin to distanceMax)
    static bool isValidDistance(Type::Scalar distance) {
        return distance <= distanceMax && distance >= distanceMin;
    }

    // Validates longitude in degrees (longitudeMin to longitudeMax)
    static bool isValidLongitude(Type::Scalar longitude) {
        return longitude <= longitudeMax && longitude >= longitudeMin;
    }

    // Validates latitude in degrees (latitudeMin to latitudeMax)
    static bool isValidLatitude(Type::Scalar latitude) {
        return latitude <= latitudeMax && latitude >= latitudeMin;
    }

    // Validates heading (0 to 360)
    static bool isValidHeading(Type::Scalar heading) {
        return heading >= headingMin && heading < headingMax;
    }

    // Validates height above sea level in meters (non-negative)
    static bool isValidHeightMSL(Type::Scalar heightMSL) {
        return heightMSL >= heightMin && heightMSL <= heightMax;
    }

};
