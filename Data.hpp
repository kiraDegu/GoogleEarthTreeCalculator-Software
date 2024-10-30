#ifndef _ACADEMY_DATA_HPP_
#define _ACADEMY_DATA_HPP_

#include "TypeTraits.hpp"

//! @struct Data @brief Path computation input data aggregate
struct Data {
    //! @brief Origin point for path computation
    Type::Point p0{0.0, 0.0, 5000.0};

    //! @brief Distance parameter for path computation in nautical miles
    Type::Scalar d{0.0};

    //! @brief Heading angle for path computation in deg
    Type::Scalar th{0.0};

    //! @brief Path altitude measured from Mean Sea Level in meters
    Type::Scalar msl{5000.0};
};

#endif // _ACADEMY_DATA_HPP_