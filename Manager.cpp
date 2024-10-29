#include <iostream>
#include <fstream>
#include "Manager.hpp"

// Generate output path in kml format
bool PathCalculatorManager::genPath(
    const Type::Scalar& lat0, const Type::Scalar& long0,
    const Type::Scalar& d, const Type::Scalar& theta0,
    const Type::Scalar& msl, const Type::Model& model
) const {
    Data data{Type::Point{lat0,long0,msl}, d, theta0, msl};

    auto calcPtr = _createPathCalculator(data, model);
    if (!calcPtr) // From GUI this will never be activated
        std::cerr << "In 'genPath': something went wrong when selecting calculation model." << std::endl;
    Type::Path path = calcPtr->eval(_pathSpec);

    // Print to kml file
    std::ofstream os(_fileName);
    if (os) {
        KMLI::printPath(os, path);
        os.close();
        return true;
    } else {
        os.close();
        return false;
    }
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