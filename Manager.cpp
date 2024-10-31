#include <iostream>
#include <fstream>
#include "Manager.hpp"

bool PathCalculatorManager::genPath(
    const Type::Scalar& lat0, const Type::Scalar& long0,
    const Type::Scalar& d, const Type::Scalar& theta0,
    const Type::Scalar& msl, const Type::Model& model,
    const Type::Methods& methods
) const {

    // Select computational model
    auto calcPtr = _createPathCalculator(Data{Type::Point{lat0,long0,msl}, d, theta0, msl}, model);
    if (!calcPtr) // From GUI this will never be activated
        std::cerr << "In 'genPath': something went wrong when selecting calculation model." << std::endl;

    std::ofstream os(_fileName), osOrigin;
    switch (methods) {
    case 0u: {
        if (os) {
            KMLI::printPath(os, calcPtr->eval(_pathSpec, false));
            os.close();
        } else {
            os.close();
            return false;
        }
        break;
    }
    
    case 1u: {
        if (os) {
            KMLI::printPath(os, calcPtr->eval(_pathSpec, true));
            os.close();
        } else {
            os.close();
            return false;
        }
        break;
    }

    case 2u: {
        osOrigin.open(_fileName+"_FO");
        if (os) {
            KMLI::printPath(os, calcPtr->eval(_pathSpec, false));
            os.close();
        } else {
            os.close();
            return false;
        }
        if (osOrigin) {
            KMLI::printPath(osOrigin, calcPtr->eval(_pathSpec, true));
            osOrigin.close();
        } else {
            osOrigin.close();
            return false;
        }
        break;
    }

    default: {
        return false;
        break;
    }

    }

    return true;
}


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
