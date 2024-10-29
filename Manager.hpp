#ifndef _ACADEMY_MANAGER_HPP_
#define _ACADEMY_MANAGER_HPP_

#include <memory>
#include "Calculators.hpp"
#include "DataValidator.hpp"
#include "KmlInterface.hpp"

class PathCalculatorManager {
    public:
        using KMLI = KmlInterface;
        using DV   = DataValidator;

        PathCalculatorManager()=delete;
        PathCalculatorManager(const Type::PathSpec& pathSpec, const Type::String& fileName = "out.kml")
        : _pathSpec{pathSpec}, _fileName{fileName} {}

        bool genPath(
            const Type::Scalar& lat0, const Type::Scalar& long0,
            const Type::Scalar& d, const Type::Scalar& theta0,
            const Type::Scalar& msl, const Type::Model& model
        ) const;

    private:
        Type::PathSpec _pathSpec;
        Type::String   _fileName;

        // Private path calculator factory
        std::unique_ptr<AbstractPathCalculator>
        _createPathCalculator(const Data&, const Type::Model&) const;
};

#endif // _ACADEMY_MANAGER_HPP_