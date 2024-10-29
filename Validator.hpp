#ifndef _ACADEMY_DATAVALIDATOR_HPP
#define _ACADEMY_DATAVALIDATOR_HPP

#include "TypeTraits.hpp"

class DataValidator {
private:
    // Constants for validation limits
    static const Type::Scalar distanceMax;
    static const Type::Scalar distanceMin;
    static const Type::Scalar longitudeMax;
    static const Type::Scalar longitudeMin;
    static const Type::Scalar latitudeMax;
    static const Type::Scalar latitudeMin;
    static const Type::Scalar headingMax;
    static const Type::Scalar headingMin;
    static const Type::Scalar heightMax; // Example maximum height in meters
    static const Type::Scalar heightMin;

public:
    // Validates distance (distanceMin to distanceMax)
    static bool isValidDistance(Type::Scalar distance);

    // Validates longitude in degrees (longitudeMin to longitudeMax)
    static bool isValidLongitude(Type::Scalar longitude);

    // Validates latitude in degrees (latitudeMin to latitudeMax)
    static bool isValidLatitude(Type::Scalar latitude);

    // Validates heading (0 to 360)
    static bool isValidHeading(Type::Scalar heading);

    // Validates height above sea level in meters (non-negative)
    static bool isValidHeightMSL(Type::Scalar heightMSL);
};

#endif // _ACADEMY_DATAVALIDATOR_HPP
