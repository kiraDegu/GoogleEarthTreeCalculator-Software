#include "Calculators.hpp"


Type::Path FlatEarthPathCalculator::eval() const {
    Type::Path out;
    out.reserve(_path.size()+1);

    out.emplace_back(_data.p0);

    return out;
}

Type::Path SphericalEarthPathCalculator::eval() const {
    Type::Path out;
    out.reserve(_path.size()+1);

    out.emplace_back(_data.p0);

    return out;
}

Type::Path WGS84PathCalculator::eval() const {
    Type::Path out;
    out.reserve(_path.size()+1);

    out.emplace_back(_data.p0);

    return out;
}