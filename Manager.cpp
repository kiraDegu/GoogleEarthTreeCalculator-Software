#include "Manager.hpp"

// Generate output path in kml format
void PathCalculatorManager::genPath(
    const Type::Scalar& lat0, const Type::Scalar& long0,
    const Type::Scalar& d, const Type::Scalar& theta0,
    const Type::Scalar& msl, const Type::Model& model
) const {
    auto calcPtr = _createPathCalculator(Data{Type::Point{lat0,long0,msl}, d, theta0, msl}, model);
    Type::Path path = calcPtr->eval(_pathSpec);
    // TODO: printare in kml
}

// Path calculator factory method
std::unique_ptr<AbstractPathCalculator>
PathCalculatorManager::_createPathCalculator(const Data& data, const Type::Model& model) const {
    switch (model) {
    case 0u:
        return std::make_unique<FlatEarthPathCalculator>(data);
        break;

    case 1u:
        return std::make_unique<SphericalEarthPathCalculator>(data);
        break;

    case 2u:
        return std::make_unique<WGS84PathCalculator>(data);
        break;

    default:
        return nullptr;
        break;
    }
}