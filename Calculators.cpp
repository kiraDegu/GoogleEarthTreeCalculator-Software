#include "Calculators.hpp"
#include <cmath>


double degreeToRadiant(double gradi) {
    return gradi * (M_PI / 180.0); 
}

Type::Path FlatEarthPathCalculator::eval() const {
    Type::Path out;
    out.reserve(_path.size()+1);

    out.emplace_back(_data.p0);

    Type::Point  p_current = _data.p0;


    for (int i = 1; i < _path.size(); ++i) {
        Type::Point  p_next  = { p_current[0] + (_data.d*_path[i].first)*cos(degreeToRadiant(_data.th + _path[i].second)) ,  p_current[1] + (_data.d*_path[i].first)*sin(degreeToRadiant(_data.th + _path[i].second)) }; 
        out.emplace_back(p_next);  
        p_current = p_next;
    }

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