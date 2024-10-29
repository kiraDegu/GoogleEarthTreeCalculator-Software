#ifndef _ACADEMY_TYPETRAITS_HPP_
#define _ACADEMY_TYPETRAITS_HPP_

#include <array>
#include <vector>
#include <string>
#include <utility>

// Type alias aggregate
struct Type {

    // String type alias
    using String = std::string;

    // Scalar type alias
    using Scalar = double;

    // Point type alias
    struct Point {
        Scalar longi; // longitude [deg]
        Scalar lati;  // latitude  [deg]
        Scalar alti;  // altitude  [m]
    };

    /* Path specifier type alias
       the definition of a path at fixed altitude requires a pair
       of data for each path jump segment: 
                    (jump magnitude, jump direction)
    */
    using PathSpec = std::vector<std::pair<Scalar, Scalar>>;

    // Path type alias
    using Path = std::vector<Point>;

    /* Calculation model type alias
       Flat Earth      = 0
       Spherical Earth = 1
       WGS84           = 2 */
    using Model = short unsigned int;
};

#endif // _ACADEMY_TYPETRAITS_HPP_