#include "Calculators.hpp"

Type::Path&& AbstractPathCalculator::initOutput() const {
    Type::Path out;
    out.reserve(_pathSpec.size()+1);
    out.emplace_back(_data.p0);

    return std::move(out);
}

Type::Path FlatEarthPathCalculator::eval() const {
    Type::Path out{this->initOutput()};

    return out;
}

Type::Path SphericalEarthPathCalculator::eval() const {
    Type::Path out{this->initOutput()};

    return out;
}

Type::Path WGS84PathCalculator::eval() const {
    Type::Path out{this->initOutput()};

    return out;
}