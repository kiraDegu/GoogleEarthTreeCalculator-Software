#ifndef _ACADEMY_DATA_HPP_
#define _ACADEMY_DATA_HPP_

#include "TypeTraits.hpp"

struct Data {
    Type::Point  p0  = {0.0, 0.0}; // [deg, deg]
    Type::Scalar d   = {0.0};      // [NM]
    Type::Scalar th  = {0.0};      // [deg]
    Type::Scalar msl = 5000.0;     // [m]
};

#endif // _ACADEMY_DATA_HPP_