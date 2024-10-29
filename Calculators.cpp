#include "Calculators.hpp"

// Common output initializer
Type::Path&& AbstractPathCalculator::_initOutput(const Type::PathSpec& pathSpec) const {
    Type::Path out;
    out.reserve(pathSpec.size()+1);
    out.emplace_back(_data.p0);

    return std::move(out);
}

// Flat earth model path calculator implementation
Type::Path FlatEarthPathCalculator::eval(const Type::PathSpec& pathSpec) const {
    Type::Path out{this->_initOutput(pathSpec)};

    return out;
}

// Spherical earth model path calculator implementation
Type::Path SphericalEarthPathCalculator::eval(const Type::PathSpec& pathSpec) const {
    Type::Path out{this->_initOutput(pathSpec)};

    return out;
}

// WGS84 model path calculator implementation
Type::Path WGS84PathCalculator::eval(const Type::PathSpec& pathSpec) const {
    Type::Path out{this->_initOutput(pathSpec)};

    return out;
}