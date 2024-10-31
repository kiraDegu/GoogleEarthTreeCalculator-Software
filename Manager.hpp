#ifndef _ACADEMY_MANAGER_HPP_
#define _ACADEMY_MANAGER_HPP_

#include <memory>
#include "Calculators.hpp"
#include "DataValidator.hpp"
#include "KmlInterface.hpp"

/*! @class PathCalculatorManager
    @brief Manager class for path calculation, it is responsible of path calculations object selection
*/
class PathCalculatorManager {
    public:
        //! @brief Type alias for the KML interface class 
        using KMLI = KmlInterface;
        //! @brief Type alias for data validator
        using DV = DataValidator;

        //! @brief Delete default constructor
        PathCalculatorManager()=delete;

        //! @brief Construct from path specifier and output filename
        PathCalculatorManager(
            const Type::PathSpec& pathSpec,
            const Type::String& fileName = "out",
            bool fromOrigin = false
        ): _pathSpec{pathSpec}, _fileName{fileName}, _fromOrigin{fromOrigin} {}

        /*! @brief Generate output path in kml format
            @param lat0 Latitude of the origin point in deg, from -90° to 90°
            @param long0 Longitude of the origin point in deg, from -180° to 180°
            @param d Path distance parameter in nautical miles
            @param theta0 Heading angle in deg, from 0° to 360°
            @param msl Altitude in meters evaluated from the Mean Sea Level 
            @param model Computational model identifier (0,1,2) <-> (FE,SE,WGS84)
        */
        bool genPath(
            const Type::Scalar& lat0, const Type::Scalar& long0,
            const Type::Scalar& d, const Type::Scalar& theta0,
            const Type::Scalar& msl, const Type::Model& model
        ) const;

    private:
        //! @brief Save path specifier privately
        Type::PathSpec _pathSpec;
        //! @brief Save output file name privately
        Type::String _fileName;
        //! @brief Save calculation method
        bool _fromOrigin;

        /*! @brief Private path calculator factory method
            @param data Input data aggregate
            @param model Computational model (0,1,2) <-> (FE,SE,WGS84)
            @return A unique pointer to an abstract calculator overrided by the concrete calculator selected by the method
        */
        std::unique_ptr<AbstractPathCalculator>
        _createPathCalculator(const Data& data, const Type::Model& model) const;
};

#endif // _ACADEMY_MANAGER_HPP_
