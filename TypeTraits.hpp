#ifndef _ACADEMY_TYPETRAITS_HPP
#define _ACADEMY_TYPETRAITS_HPP

#include <array>
#include <vector>
#include <string>

enum CalcModel { FlatEarth=1, Spherical=2, WGS84=3 };

struct Type {
    using String   = std::string;
    using Scalar   = double;
    using Point    = std::array<Scalar, 2>;
    using PathSpec = std::vector<std::pair<Scalar, Scalar>>;
    using Path     = std::vector<Point>;
};

#endif // _ACADEMY_TYPETRAITS_HPP