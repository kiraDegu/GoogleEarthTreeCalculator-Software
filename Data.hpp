#ifndef _ACADEMY_DATA_HPP_
#define _ACADEMY_DATA_HPP_

#include "TypeTraits.hpp"

// Input data aggregate
struct Data {
    // Origin point
    Type::Point  p0  = {0.0, 0.0, 5000.0}; // [deg, deg, m]

    // Distance parameter
    Type::Scalar d   = {0.0};              // [NM]

    // Heading angle
    Type::Scalar th  = {0.0};              // [deg]

    // Altitude measured from Mean Sea Level
    Type::Scalar msl = 5000.0;             // [m]
};

#endif // _ACADEMY_DATA_HPP_