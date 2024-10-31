#ifndef _ACADEMY_TYPETRAITS_HPP_
#define _ACADEMY_TYPETRAITS_HPP_

#include <vector>
#include <string>
#include <utility>

/*! @struct Type
    @brief Type alias aggregate containing shortcuts used for path calculations
*/ 
struct Type {

    //! @brief String type alias
    using String = std::string;

    //! @brief Scalar type alias
    using Scalar = double;

    /*! @struct Point
        @brief Data aggregate representing a point lying on the earth atmosphere
    */
    struct Point {
        //! @brief Latitude in deg, acceptable values ranges from -90° to 90° 
        Scalar lati;
        //! @brief Longitude in deg, acceptable values ranges from -180° to 180°
        Scalar longi;
        //! @brief Altitude in meters evaluated from the Mean Sea Level (MSL)
        Scalar alti;
    };

    /*! @brief Single segment specifier

        Together with an origin point, it can be used to calculate a point location.
        It consist of an angle and a magnitude:
            (segment magnitude, segment direction w.r.t north)
    */
    using Spec = std::pair<Scalar, Scalar>;

    /*! @brief Path specifier type alias for a trajectory with a fixed altitude
        
        The definition of a trajectory path at fixed altitude requires a pair
        of data for each path segment
    */
    using PathSpec = std::vector<Spec>;

    //! @brief Trajectory path type alias
    using Path = std::vector<Point>;

    /*! @brief Calculation model type alias

        (0, 1, 2) <-> (Flat Earth, Spherical Earth, WGS84) model
    */
    using Model = short unsigned int;

    /*! @brief Calculation methods employed type alias

        Path can be calculated point by point (PbP) or from origin (FO),
        the program prints kml files for each of the method selected
        (0, 1, 2) <-> (PbP, FO, both)
    */
    using Methods = short unsigned int;
};

#endif // _ACADEMY_TYPETRAITS_HPP_
